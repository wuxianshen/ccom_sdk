/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : packet_structs.c
   Author : tao.jing
   Date   : 2019/11/22
   Brief  : 
**************************************************************************/
#include "packet_structs.h"

Vector g_packet_vector;

pthread_mutex_t g_packet_vector_mt = PTHREAD_MUTEX_INITIALIZER;
