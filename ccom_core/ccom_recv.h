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

int8_t start_receive();

#endif //CCOM_SDK_CCOM_RECV_H
