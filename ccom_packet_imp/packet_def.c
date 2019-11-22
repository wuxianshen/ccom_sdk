/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_def.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  :
**************************************************************************/
#include "packet_def.h"

//Packet callback function pointers
PACKET_CALLBACK* g_packet_cb_map[e_packet_type_num] = {0};
