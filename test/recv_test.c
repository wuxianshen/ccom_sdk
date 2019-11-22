/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : main.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : main
**************************************************************************/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "ccom_send.h"
#include "ccom_recv.h"
#include "serial_api.h"
#include "sys_tool.h"
#include "elog.h"
#include "uw_device.h"
#include "packet_manage.h"

int32_t elog_config();

void recv_test();

int main()
{
    elog_config();
    log_i("Hello, World!\n");

    start_packet_process();

    int32_t ret = serial_init(e_deck_serial);
    log_i("[CCOM] Serial init ret %d", ret);

    ret = start_receive(e_deck_serial);
    log_i("[CCOM] Start receive ret %d", ret);

    recv_test();

    return 0;
}

int32_t elog_config()
{
    //Set elog path
    char cur_time[24] = { 0 };
    char cur_date[24] = { 0 };
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(cur_date, 24, "%F", timeinfo);
    strftime(cur_time, 24, "%T", timeinfo);

    char log_file_name[256] = { 0 };
    const char* user_name = get_user_name();
    char log_file_path[128] = { 0 } ;
    strcat(log_file_path, "/home/");
    strcat(log_file_path, user_name);
    strcat(log_file_path, "/uw_log/elog/");
    strcat(log_file_path, cur_date);
    strcat(log_file_path, "/");

    char* log_file_suffix = ".log";
    strcat(log_file_name, log_file_path);
    strcat(log_file_name, cur_time);
    strcat(log_file_name, log_file_suffix);

    if ( dir_exists(log_file_path) != 0 )
    {
        create_dir(log_file_path);
    }

    elog_user_file(log_file_name);

    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_SERVER, ELOG_FMT_LVL);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start elog */
    elog_start();

    return 0;
}

void recv_test()
{
    while(1)
    {
        sleep(1);
    }

    char cmd;
    printf("Press any key to test send, q to quit.\n");
    int32_t ret = scanf(" %c", &cmd);
    while( cmd != 'q' )
    {
        int8_t content[] = {0x30, 0x31, 0x32, 0x33};
        int8_t ret = ccom_send_buffer(0, sizeof(content)/sizeof(content[0]), content);
        log_i("[CCOM] ccom send ret %d", ret);
        printf("Press any key to test send, q to quit.\n");
        ret = scanf(" %c", &cmd);
    }
}