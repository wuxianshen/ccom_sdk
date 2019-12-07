/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : deck_callbacks.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include "deck_callbacks.h"
#include "ccom_send.h"
#include "elog.h"
#include "uw_device.h"
#include "ccom_protocol.h"
#include "packet_def.h"
#include "pc_serial_config.h"
#include "uw_device.h"

//Deck packet type callbacks
void deck_print_packet(uint32_t param_len, int8_t* param)
{
    int8_t* print_buf = (int8_t*) malloc(param_len + 1);
    memset(print_buf, 0, param_len + 1);

    uint32_t print_cnt = 0;
    for(uint32_t idx = 0; idx < param_len; idx++)
    {
        if ( isprint(param[idx]) )
        {
            print_buf[print_cnt] = param[idx];
            print_cnt++;
        }
    }
    log_w("[PACKET] Deck print: %s", print_buf);
    free(print_buf);
}

void deck_echo_packet(uint32_t param_len, int8_t* param)
{
    uint8_t src_id = e_ccom_deck;
    uint8_t dst_id = e_ccom_imx6;
    uint8_t module_id = e_deck_packet;
    uint8_t func_id = e_deck_print;
    int32_t ret =  ccom_send_packet(e_default_serial,
                        src_id,
                        dst_id,
                        module_id,
                        func_id,
                        param_len, param);
    if ( ret != 0 )
    {
        log_e("[PACKET] Deck echo failed.");
    }
    else
    {
        int8_t* print_buf = (int8_t*) malloc(param_len + 1);
        memset(print_buf, 0, param_len + 1);

        uint32_t print_cnt = 0;
        for(uint32_t idx = 0; idx < param_len; idx++)
        {
            if ( isprint(param[idx]) )
            {
                print_buf[print_cnt] = param[idx];
                print_cnt++;
            }
        }
        log_w("[PACKET] Deck echo: %s", print_buf);
        free(print_buf);
    }
}