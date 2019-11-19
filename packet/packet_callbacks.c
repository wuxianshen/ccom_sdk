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

//General packet type callbacks
void general_print_packet(uint32_t param_len, int8_t* param)
{
    int8_t* str = (int8_t*) malloc(sizeof(int8_t) * param_len + 1);
    memset(str, 0, sizeof(int8_t) * param_len + 1);
    memcpy(str, param, param_len);
    log_i("[Packet] Echo %s.", str);
}



