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
#include "packet_manage.h"
#include "packet_callbacks.h"
#include "elog.h"

void* packet_process_loop(void* arg);

pthread_t packet_process_thread;

int8_t g_packet_processing_on = 0;

void start_packet_process()
{
    packet_callback_register();
    start_packet_process_thread();
}

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
                g_packet_cb_map[cur_packet->packet_type][cur_packet->packet_event](cur_packet->param_len, cur_packet->param);

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