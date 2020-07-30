/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_recv.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_CCOM_RECV_H
#define CCOM_SDK_CCOM_RECV_H

#include <stdint.h>
#include <pthread.h>
#include "ccom_config.h"
#ifndef USE_ARM
#include "serial.h"
#endif

typedef struct _ccom_serial_tran{
    pthread_t recv_thread;
    char* platform_serial;
    int8_t serial_idx;
    int8_t receiving_start_signal;
    int8_t *ccom_recv_buf;
#ifndef USE_ARM
    const char *pc_serial_name;
    int pc_serial_baud ;
    serial_t pc_serial_handlers;
#else
    uint8_t uw_serial_port;
    uint32_t uw_serial_baud;
#endif
}ccom_serial_tran;

enum ccom_recv_state
{
    ccom_none = 0,
    ccom_frame_header_1 = 1,
    ccom_frame_header_2 = 2,
    ccom_frame_length   = 3,
    ccom_frame_resv     = 4,
    ccom_frame_header_checksum = 5,
    ccom_frame_content  = 6,
    ccom_frame_checksum = 7,
};

void ccom_serial_transfer_init(ccom_serial_tran *cur_serial, uint8_t serial_idx);
void serial_transfer_config(ccom_serial_tran *cur_serial);
void start_serial_recv(ccom_serial_tran *cur_serial, uint8_t serial_idx);
int8_t start_receive(ccom_serial_tran *cur_serial);

#endif //CCOM_SDK_CCOM_RECV_H
