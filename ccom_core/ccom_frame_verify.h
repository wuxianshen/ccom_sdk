/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_frame_verify.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#ifndef CCOM_SDK_CCOM_FRAME_VERIFY_H
#define CCOM_SDK_CCOM_FRAME_VERIFY_H

#include <stdint.h>

uint8_t get_checksum_u8(int8_t* buf, uint32_t len);

uint16_t get_checksum_u16(int8_t* buf, uint32_t len);

#endif //CCOM_SDK_CCOM_FRAME_VERIFY_H
