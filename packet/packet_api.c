/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_api.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include "packet_api.h"
#include "elog.h"

void push_packet(packet_event_t* packet)
{
    pthread_mutex_lock(&g_packet_vector_mt);
    int ret = vector_push_back(&g_packet_vector, packet);
    if ( ret != 0 )
    {
        log_e("[PACKET] Error push packet.");
    }
    //log_i("[PACKET] Packet vector addr %x.", &g_packet_vector);
    //log_i("[PACKET] Push packet ret %dm, vector size %d.", ret, g_packet_vector.size);
    pthread_mutex_unlock(&g_packet_vector_mt);
}
