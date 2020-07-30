/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_recv.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "ccom_recv.h"
#include "ccom_config.h"
#include "serial_api.h"
#include "ccom_frame_verify.h"
#include "ccom_protocol.h"
#include "elog.h"
#include "packet_callbacks.h"

#ifdef USE_ARM
    #include "uw_serial_config.h"
#else
    #include "pc_serial_config.h"
#endif


void* ccom_receive_loop(void* arg);

int8_t frame_header_verify(int8_t *g_ccom_recv_buf);

int8_t frame_verify(int8_t *g_ccom_recv_buf, uint16_t g_frame_length );

void try_to_print_content(int8_t *g_ccom_recv_buf, uint16_t g_frame_length);


void ccom_serial_transfer_init(ccom_serial_tran *cur_serial, uint8_t serial_idx)
{
//    printf("ccom_serial_recv_init\n");
    cur_serial->platform_serial = platform_serial[serial_idx];
    cur_serial->serial_idx = serial_idx;
    cur_serial->receiving_start_signal = 0;
    cur_serial->ccom_recv_buf = (int8_t*)malloc(CCOM_RECV_BUF_LEN);
#ifdef USE_ARM
    cur_serial->uw_serial_port = uw_serial_port[serial_idx];
    cur_serial->uw_serial_baud = uw_serial_baud[serial_idx];
#else
    cur_serial->pc_serial_handlers = serial_handlers[serial_idx];
    cur_serial->pc_serial_name = pc_serial_names[serial_idx];
    cur_serial->pc_serial_baud = pc_serial_baud[serial_idx];
#endif
}


void serial_transfer_config(ccom_serial_tran *cur_serial)
{
//    printf("-----serial_config-------\n");
    int32_t ret1 = serial_init(cur_serial->serial_idx);
    log_i("[CCOM] %s Serial init ret %d", cur_serial->platform_serial, ret1);

    int8_t ret2 = start_receive(cur_serial);
    log_i("[CCOM] %s Start receive ret %d", cur_serial->platform_serial, ret2);
}

void start_serial_recv(ccom_serial_tran *cur_serial, uint8_t serial_idx)
{
    ccom_serial_transfer_init(cur_serial, serial_idx);
    serial_transfer_config(cur_serial);
}

int8_t start_receive(ccom_serial_tran *cur_serial)
{
    cur_serial->receiving_start_signal = 1;
    int32_t ret = pthread_create(&(cur_serial->recv_thread), NULL, ccom_receive_loop, (void *) cur_serial);
//    printf("---serial %s thread open---\n",cur_serial->platform_serial);
    if ( ret != 0 )
    {
        log_e("Cannot create receiving process thread, err code %d...", ret);
        return ret;
    }
    return 0;
}

void* ccom_receive_loop(void* arg)
{
    ccom_serial_tran* cur_serial = (ccom_serial_tran*)arg;
    char* platform_serial = cur_serial->platform_serial;
    int8_t serial_idx = cur_serial->serial_idx;
    int8_t receiving_start_signal = cur_serial->receiving_start_signal;
    int8_t *ccom_recv_buf = cur_serial->ccom_recv_buf;

    uint32_t ccom_buf_cursor = 0;
    uint16_t frame_length = 0;
    log_i("Starting ccom receive processing for serial idx %d ...", serial_idx);

    int8_t read_char = 0;
    unsigned char recv_state = ccom_none;
    while( receiving_start_signal != 0 )
    {
        usleep(5);
        int8_t char_read_state = -1;    //read fail: -1, read ok :0
        read_char = serial_read_one_char(serial_idx, &char_read_state);

        if ( char_read_state == -1 )
        {
            continue;
        }

//        log_i("%s recieve %X", platform_serial , read_char);
        if ( recv_state == ccom_none )
        {
            //wait for frame header1 0x55
            if ( (uint8_t)read_char != CCOM_FRAME_HEADER1 )
            {
                //Invalid char in this state
                continue;
            }
            //log_i("[CCOM] New frame start.");
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor++;

            recv_state ++;
            continue;
        }

        if ( recv_state == ccom_frame_header_1 )
        {
            //wait for frame header2 0xAA
            if ( (uint8_t)read_char != CCOM_FRAME_HEADER2 )
            {
                //invalid char in this state
                recv_state = ccom_none;
                ccom_buf_cursor = 0;
            }
            else
            {
                ccom_recv_buf[ccom_buf_cursor] = read_char;
                ccom_buf_cursor ++;

                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_header_2 )
        {
            //receiving frame length
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor ++;

            if ( ccom_buf_cursor == 4 )
            {
                //got 2 bytes frame length - not including frame end checksum
                frame_length = ((uint8_t)ccom_recv_buf[3] << 8) + ccom_recv_buf[2];

                //log_i("[CCOM] Frame length %d", g_frame_length);

                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_length )
        {
            //got frame resv
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor ++;

            recv_state ++;
            continue;
        }

        if ( recv_state == ccom_frame_resv )
        {
            //got frame checksum
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor ++;

            if( frame_header_verify(ccom_recv_buf) == 0 )
            {
                //log_i("[CCOM] Frame header check ok.");
                recv_state++;
                continue;
            }
            else
            {
                log_e("[CCOM] Frame header check failed.");
                recv_state = ccom_none;
                ccom_buf_cursor = 0;
            }
        }

        if ( recv_state == ccom_frame_header_checksum )
        {
            //receiving frame content --- package
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor ++;

            if ( ccom_buf_cursor == CCOM_FRAME_HEADER_LEN + frame_length )
            {
                //got frame content
                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_content )
        {
            //receiving frame end checksum (not including frame header)
            ccom_recv_buf[ccom_buf_cursor] = read_char;
            ccom_buf_cursor ++;

            if ( ccom_buf_cursor == CCOM_FRAME_HEADER_LEN + frame_length + CCOM_FRAME_CHECKSUM_LEN )
            {
                //got frame end checksum
                if ( frame_verify(ccom_recv_buf,frame_length) == 0 )
                {
                    //log_i("[CCOM] Frame checksum ok.");
                    //try_to_print_content();
                    {
                        extern void ccom_preprocess(int8_t* data, uint32_t data_len);

                        ccom_preprocess(&(ccom_recv_buf[CCOM_FRAME_CONTENT_CURSOR]), frame_length);
                    }
                    ccom_packet_process(&(ccom_recv_buf[CCOM_FRAME_CONTENT_CURSOR]), frame_length);
                    memset(ccom_recv_buf,0,CCOM_RECV_BUF_LEN);
                }
                else
                {
                    log_e("[CCOM] Frame checksum failed.");
                    memset(ccom_recv_buf,0,CCOM_RECV_BUF_LEN);
                }
                recv_state = ccom_none;
                ccom_buf_cursor = 0;
                continue;
            }
        }

    }
    free(ccom_recv_buf);
    return ((void*)0);
}

int8_t frame_header_verify(int8_t *g_ccom_recv_buf)
{
    if ( get_checksum_u8(g_ccom_recv_buf, CCOM_FRAME_HEADER_LEN - 1) == (uint8_t)g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN - 1] )
    {
        return 0;
    }
    return 1;
}

int8_t frame_verify(int8_t *g_ccom_recv_buf, uint16_t g_frame_length )
{
    uint16_t checksum = get_checksum_u16(g_ccom_recv_buf + CCOM_FRAME_HEADER_LEN, g_frame_length);

    uint16_t recv_check_sum = (uint8_t)g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN + g_frame_length] +
                              ((g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN + g_frame_length + 1]) << 8);

    if ( checksum == recv_check_sum )
    {
        return 0;
    }
    log_w("Frame checksum %x, but recv checksum %x.", checksum, recv_check_sum);
    return 1;
}

void try_to_print_content(int8_t *g_ccom_recv_buf, uint16_t g_frame_length)
{
    for(uint16_t idx = 0; idx < g_frame_length; idx++)
    {
        if ( isprint(g_ccom_recv_buf[idx + CCOM_FRAME_HEADER_LEN]) )
        {
            printf("%c", g_ccom_recv_buf[idx + CCOM_FRAME_HEADER_LEN]);
        }
    }
    printf("\n");
}