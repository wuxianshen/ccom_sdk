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
#include "ccom_recv.h"
#include "ccom_config.h"
#include "serial_api.h"
#include "uw_device.h"
#include "ccom_frame_verify.h"
#include "ccom_protocol.h"
#include "elog.h"

pthread_t recv_thread;

int8_t g_receiving = 0;
int8_t g_ccom_recv_buf[CCOM_RECV_BUF_LEN] = { 0 };
uint32_t g_ccom_buf_cursor = 0;
uint16_t g_frame_length = 0;    //only for data length, not including frame header and checksum

void* receive_loop(void* arg);

int8_t frame_header_verify();

int8_t frame_verify();

void try_to_print_content();

int8_t start_receive()
{
    g_receiving = 1;
    int32_t ret = pthread_create(&recv_thread, NULL, receive_loop, NULL);
    if ( ret != 0 )
    {
        log_e("Cannot create receiving process thread, err code %d...", ret);
        return ret;
    }
    return 0;
}

void* receive_loop(void* arg)
{
    log_i("Starting ccom receive processing ...");

    int8_t read_char = 0;
    unsigned char recv_state = ccom_none;
    while( g_receiving != 0 )
    {
        usleep(5);
        int8_t char_read_state = -1;
        read_char = serial_read_one_char(e_deck_serial, &char_read_state);
        //log_i("%c", read_char);

        if ( char_read_state == -1 )
        {
            continue;
        }

        if ( recv_state == ccom_none )
        {
            //wait for frame header1 0x55
            if ( (uint8_t)read_char != CCOM_FRAME_HEADER1 )
            {
                //Invalid char in this state
                continue;
            }
            //log_i("[CCOM] New frame start.");
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;
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
                g_ccom_buf_cursor = 0;
            }
            else
            {
                g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
                g_ccom_buf_cursor ++;
                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_header_2 )
        {
            //receiving frame length
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;

            if ( g_ccom_buf_cursor == 4 )
            {
                //got 2 bytes frame length - not including frame end checksum
                g_frame_length = ((uint8_t)g_ccom_recv_buf[3] << 8) + g_ccom_recv_buf[2];
                //log_i("[CCOM] Frame length %d", g_frame_length);

                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_length )
        {
            //got frame resv
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;
            recv_state ++;
            continue;
        }

        if ( recv_state == ccom_frame_resv )
        {
            //got frame checksum
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;

            if( frame_header_verify() == 0 )
            {
                //log_i("[CCOM] Frame header check ok.");
                recv_state++;
                continue;
            }
            else
            {
                log_e("[CCOM] Frame header check failed.");
                recv_state = ccom_none;
                g_ccom_buf_cursor = 0;
            }
        }

        if ( recv_state == ccom_frame_header_checksum )
        {
            //receiving frame content --- package
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;

            if ( g_ccom_buf_cursor == CCOM_FRAME_HEADER_LEN + g_frame_length )
            {
                //got frame content
                recv_state ++;
                continue;
            }
        }

        if ( recv_state == ccom_frame_content )
        {
            //receiving frame end checksum (not including frame header)
            g_ccom_recv_buf[g_ccom_buf_cursor] = read_char;
            g_ccom_buf_cursor ++;

            if ( g_ccom_buf_cursor == CCOM_FRAME_HEADER_LEN + g_frame_length + CCOM_FRAME_CHECKSUM_LEN )
            {
                //got frame end checksum
                if ( frame_verify() == 0 )
                {
                    //log_i("[CCOM] Frame checksum ok.");
                    //try_to_print_content();
                    ccom_packet_process(&(g_ccom_recv_buf[CCOM_FRAME_CONTENT_CURSOR]), g_frame_length);
                }
                else
                {
                    log_e("[CCOM] Frame checksum failed.");
                }
                recv_state = ccom_none;
                g_ccom_buf_cursor = 0;
                continue;
            }
        }

    }
    return ((void*)0);
}

int8_t frame_header_verify()
{
    if ( get_checksum_u8(g_ccom_recv_buf, CCOM_FRAME_HEADER_LEN - 1) == (uint8_t)g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN - 1] )
    {
        return 0;
    }
    return 1;
}

int8_t frame_verify()
{
    uint16_t checksum = get_checksum_u16(g_ccom_recv_buf + CCOM_FRAME_HEADER_LEN, g_frame_length);

    uint16_t recv_check_sum = (uint8_t)g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN + g_frame_length] +
                             (g_ccom_recv_buf[CCOM_FRAME_HEADER_LEN + g_frame_length + 1] << 8);

    if ( checksum == recv_check_sum )
    {
        return 0;
    }
    log_w("Frame checksum %x, but recv checksum %x.", checksum, recv_check_sum);
    return 1;
}

void try_to_print_content()
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