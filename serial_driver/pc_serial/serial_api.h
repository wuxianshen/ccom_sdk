/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : gps_apt.h
   Author : tao.jing
   Date   : 19-7-12
   Brief  : 
**************************************************************************/

#ifndef SUB_PERCEPTION_DECK_COMM_API_H
#define SUB_PERCEPTION_DECK_COMM_API_H

#include "serial.h"

//General

int32_t serial_init(int8_t serial_idx);

int8_t serial_read_one_char(int8_t serial_idx, int8_t* read_state);

int32_t serial_send(int8_t serial_idx, char *buf, int len);

//ARCH related -  PC Linux

int32_t serial_open_device(serial_t* p_serial, const char* serial_port, int serial_baud);

int8_t serial_read_char(serial_t *p_serial, int8_t* read_state);



#endif //SUB_PERCEPTION_DECK_COMM_API_H
