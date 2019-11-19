/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_protocol.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_CCOM_PROTOCOL_H
#define CCOM_SDK_CCOM_PROTOCOL_H

#include <stdint.h>

enum ccom_dest_id
{
    e_ccom_imx6  = 0,
    e_ccom_10520 = 1,
    e_ccom_10521 = 2,
    e_ccom_deck  = 3,
};

void ccom_packet_process(int8_t* content, uint16_t len);

#endif //CCOM_SDK_CCOM_PROTOCOL_H
