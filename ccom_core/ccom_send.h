/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_send.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#ifndef CCOM_SDK_CCOM_SEND_H
#define CCOM_SDK_CCOM_SEND_H

#include <stdint.h>

int8_t ccom_send_buffer(int8_t serial_idx, uint16_t send_len, int8_t* buf);

int8_t ccom_send_packet(int8_t serial_idx,
                        uint8_t src_id,
                        uint8_t dst_id,
                        uint8_t module_id,
                        uint8_t func_id,
                        uint16_t data_len, int8_t* data);

#endif //CCOM_SDK_CCOM_SEND_H
