/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_manage.h
   Author : tao.jing
   Date   : 19-10-13
   Brief  : 
**************************************************************************/
#ifndef UW_ALL_IN_ONE_PACKET_MANAGE_H
#define UW_ALL_IN_ONE_PACKET_MANAGE_H

#include "packet_def.h"

int8_t start_packet_process();

int8_t packet_callback_register();

int8_t start_packet_process_thread();

#endif //UW_ALL_IN_ONE_PACKET_MANAGE_H
