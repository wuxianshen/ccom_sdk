/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_structs.h
   Author : tao.jing
   Date   : 2019/11/22
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_PACKET_STRUCTS_H
#define CCOM_SDK_PACKET_STRUCTS_H

#include <stdint.h>
#include <pthread.h>
#include "vector.h"

//Packet structs
#pragma pack(1)

typedef struct _packet_event_t
{
    uint8_t packet_type;
    uint8_t packet_event;
    uint32_t param_len;
    int8_t* param;
}packet_event_t;

#pragma pack()

extern Vector g_packet_vector;

extern pthread_mutex_t g_packet_vector_mt;

#endif //CCOM_SDK_PACKET_STRUCTS_H
