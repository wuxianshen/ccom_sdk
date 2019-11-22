/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_callbacks.c
   Author : tao.jing
   Date   : 19-10-13
   Brief  : 
**************************************************************************/
#include <malloc.h>
#include <string.h>
#include "packet_callbacks.h"
#include "elog.h"
#include "packet_structs.h"
#include "packet_def.h"

int8_t packet_callback_register()
{
    for (uint8_t idx_t = 0; idx_t < e_packet_type_num; idx_t ++)
    {
        g_packet_cb_map[idx_t] = (PACKET_CALLBACK*) malloc(g_packet_type_length[idx_t] * sizeof(PACKET_CALLBACK));
    }

    g_packet_cb_map[e_general_packet][e_general_print] = general_print_packet;

    g_packet_cb_map[e_deck_packet][e_deck_print] = deck_print_packet;
    g_packet_cb_map[e_deck_packet][e_deck_echo] = deck_echo_packet;

    return 0;
}

//General packet type callbacks
void general_print_packet(uint32_t param_len, int8_t* param)
{
    int8_t* str = (int8_t*) malloc(sizeof(int8_t) * param_len + 1);
    memset(str, 0, sizeof(int8_t) * param_len + 1);
    memcpy(str, param, param_len);
    log_i("[Packet] Echo %s.", str);
}



