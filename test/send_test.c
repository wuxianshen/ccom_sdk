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
#include "ccom_send.h"
#include "serial_api.h"
#include "sys_tool.h"
#include "uw_device.h"
#include "elog.h"
#include "ccom_protocol.h"
#include "packet_def.h"

int32_t elog_config();

void send_test();

int main()
{
    elog_config();
    log_i("Hello, World!\n");

    int32_t ret = serial_init(e_dvl_serial);
    log_i("[CCOM] Serial init ret %d", ret);

    send_test();

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

void send_test()
{
    char cmd;
    char str[30] = {0};
    printf("Press any key to test send, q to quit.\n");
    int32_t ret = scanf(" %c", &cmd);
    while( cmd != 'q' )
    {
        /*
        int8_t content[] = {0x30, 0x31, 0x32, 0x33};
        int8_t ret = ccom_send_buffer(e_dvl_serial, sizeof(content)/sizeof(content[0]), content);
        log_i("[CCOM] ccom send ret %d", ret);
        printf("Press any key to test send, q to quit.\n");
        ret = scanf(" %c", &cmd);
        */
        memset(str, 0, sizeof(str));
        printf("Input a string: ");
        ret = scanf("%s", str);
        //ret = ccom_send_buffer(e_dvl_serial, strlen(str), (int8_t*)str);
        //log_i("[CCOM] ccom send ret %d", ret);

        uint8_t src_id = e_ccom_deck;
        uint8_t dst_id = e_ccom_imx6;
        uint8_t module_id = e_deck_packet;
        uint8_t func_id = e_deck_print;

        ret =  ccom_send_packet(e_dvl_serial,
                        src_id,
                        dst_id,
                        module_id,
                        func_id,
                        strlen(str), (int8_t*)str);
        log_i("[CCOM] ccom send ret %d", ret);
    }
}