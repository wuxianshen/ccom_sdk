/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_def.h
   Author : tao.jing
   Date   : 19-10-13
   Brief  : 
**************************************************************************/

#ifndef UW_ALL_IN_ONE_PACKET_DEF_H
#define UW_ALL_IN_ONE_PACKET_DEF_H

#include <stdint.h>
#include <pthread.h>
#include "vector.h"

enum packet_type_e
{
    e_general_packet = 0,
    e_deck_packet    = 1,
    e_packet_type_num,
};

enum general_packet_event_e
{
    e_general_print = 0,
    e_general_packet_event_num,
};

enum deck_packet_event_e
{
    e_deck_print = 0,
    e_deck_echo  = 1,
    e_deck_packet_event_num,
};

typedef void(* PACKET_CALLBACK)(uint32_t, int8_t*);

//Packet callback function pointers
extern PACKET_CALLBACK* g_packet_cb_map[e_packet_type_num];

//Packet type length
static const uint8_t g_packet_type_length[e_packet_type_num] = {
    e_general_packet_event_num
};

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

#endif //UW_ALL_IN_ONE_PACKET_DEF_H
