/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_callbacks.h
   Author : tao.jing
   Date   : 19-10-13
   Brief  : 
**************************************************************************/

#ifndef UW_ALL_IN_ONE_PACKET_CALLBACKS_H
#define UW_ALL_IN_ONE_PACKET_CALLBACKS_H

#include <stdint.h>
#include "deck_callbacks.h"

int8_t packet_callback_register();

void ccom_preprocess(int8_t* data, uint32_t data_len);

//General packet type callbacks
void general_print_packet(uint32_t param_len, int8_t* param);

#endif //UW_ALL_IN_ONE_PACKET_CALLBACKS_H
