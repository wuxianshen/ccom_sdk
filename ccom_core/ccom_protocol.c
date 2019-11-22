/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_protocol.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include <malloc.h>
#include <string.h>
#include "ccom_protocol.h"
#include "packet_api.h"
#include "elog.h"

//Parse ccom packet protocol and push internal packet
//src_id : 1 Byte
//dst_id : 1 Byte
//module_id : 1 Byte
//func_id : 1 Bytes
//content : N Bytes
void ccom_packet_process(int8_t* content, uint16_t len)
{
    if ( len < 4 )
    {
        log_e("[CCOM] Error packet len %d ", len);
    }

    uint8_t src_id = content[0];
    uint8_t dst_id = content[1];
    uint8_t module_id = content[2];
    uint8_t func_id = content[3];

    uint16_t data_len = len - 4;

    //generate internal packet
    int8_t* pakcet_data = (int8_t*) malloc(data_len);
    memcpy(pakcet_data, content + 4, data_len);

    if ( e_ccom_10521 == dst_id )
    {
        //transfor to 1052-1
    }

    packet_event_t packet;
    packet.packet_type  = module_id;
    packet.packet_event = func_id;
    packet.param_len = data_len;
    packet.param = pakcet_data;

    //log_i("Packet type %d, event %d, len %d", module_id, func_id, data_len);

    push_packet(&packet);
}
