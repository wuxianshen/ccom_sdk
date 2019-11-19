/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : deck_api.h
   Author : tao.jing
   Date   : 19-7-12
   Brief  : 
**************************************************************************/

#ifndef SUB_PERCEPTION_DECK_COMM_API_H
#define SUB_PERCEPTION_DECK_COMM_API_H

#include <stdint.h>

//General

int32_t serial_init(int8_t serial_idx);

int8_t  serial_read_one_char(int8_t serial_idx, int8_t* read_state);

int32_t serial_send(int8_t serial_idx, char *buf, int len);

//ARCH related - UW

int32_t  uw_serial_read(int8_t serial_idx, char* buf, int len);

int32_t  uw_serial_send(int8_t serial_idx, char* buf, int len);

int8_t uw_serial_read_char(int8_t serial_idx, char* p_read_char);

int8_t uw_serial_read_byte(int8_t serial_idx, int8_t* state);

#endif //SUB_PERCEPTION_DECK_COMM_API_H
