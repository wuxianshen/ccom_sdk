/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : sys_tool.h
   Author : tao.jing
   Date   : 19-10-3
   Brief  : 
**************************************************************************/

#ifndef UW_ALL_IN_ONE_SYS_TOOL_H
#define UW_ALL_IN_ONE_SYS_TOOL_H

#include <sys/time.h>

int dir_exists(const char* dir_path);
int create_dir(const char* dir_path);

const char* get_user_name();


void make_cond_timeout_ms(struct timespec *p_tsp, unsigned int ms);

void make_cond_timeout_s(struct timespec *p_tsp, unsigned int time_s);

#endif //UW_ALL_IN_ONE_SYS_TOOL_H
