/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_manage.c
   Author : tao.jing
   Date   : 19-10-13
   Brief  : 
**************************************************************************/
#include <malloc.h>
#include <unistd.h>
#include <pthread.h>
#include "packet_manage.h"
#include "packet_callbacks.h"
#include "packet_structs.h"
#include "elog.h"
#include "vector.h"

void* packet_process_loop(void* arg);

pthread_t packet_process_thread;

int8_t g_packet_processing_on = 0;

int8_t start_packet_process()
{
    packet_callback_register();
    return start_packet_process_thread();
}

int8_t start_packet_process_thread()
{
    //Packet vector
    vector_setup(&g_packet_vector, 10, sizeof(packet_event_t));

    g_packet_processing_on = 1;
    int32_t ret = pthread_create(&packet_process_thread, NULL, packet_process_loop, NULL);
    if ( ret != 0 )
    {
        log_e("Cannot create deck receive process thread, err code %d...", ret);
        return ret;
    }

    return 0;
}

void* packet_process_loop(void* arg)
{
    log_i("Packet process loop start...");
    while( g_packet_processing_on )
    {
        pthread_mutex_lock(&g_packet_vector_mt);
        if ( !vector_is_empty(&g_packet_vector) )
        {
            packet_event_t* cur_packet = vector_front(&g_packet_vector);
            vector_pop_front(&g_packet_vector);
            pthread_mutex_unlock(&g_packet_vector_mt);

            if ( cur_packet != NULL )
            {
                if (cur_packet->packet_type >= e_packet_type_num
                || cur_packet->packet_event >= g_packet_type_length[cur_packet->packet_type] )
                {
                    log_e("[CCOM] Error packet type %d, event %d", cur_packet->packet_type,
                        cur_packet->packet_event);
                }
                else
                {
                    g_packet_cb_map[cur_packet->packet_type][cur_packet->packet_event](cur_packet->param_len, cur_packet->param);
                }

                if ( cur_packet->param_len > 0 )
                {
                    free(cur_packet->param);
                }
            }
            continue;
        }
        pthread_mutex_unlock(&g_packet_vector_mt);
        usleep(1000 * 20);
    }
    log_i("Packet process loop stop...");
    return (void*)0;
}