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
#include "uw_defines/auv_deck_protocol.h"

/*
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
*/

typedef void(* PACKET_CALLBACK)(uint32_t, int8_t*);

//Packet callback function pointers
extern PACKET_CALLBACK* g_packet_cb_map[e_packet_type_num];

extern uint8_t* g_packet_serial_map[e_packet_type_num];

//Packet type length
static const uint8_t g_packet_type_length[e_packet_type_num] = {
    e_general_packet_event_num,
    e_deck_packet_event_num,
};

#endif //UW_ALL_IN_ONE_PACKET_DEF_H
