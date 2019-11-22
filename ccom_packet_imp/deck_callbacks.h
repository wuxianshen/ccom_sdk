/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : deck_callbacks.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_DECK_CALLBACKS_H
#define CCOM_SDK_DECK_CALLBACKS_H

#include <stdint.h>

//Deck packet type callbacks
void deck_print_packet(uint32_t param_len, int8_t* param);

void deck_echo_packet(uint32_t param_len, int8_t* param);

#endif //CCOM_SDK_DECK_CALLBACKS_H
