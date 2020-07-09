/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : auv_deck_data_generator.c
   Author : tao.jing
   Date   : 2020/6/11
   Brief  : 
**************************************************************************/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "ccom_send.h"
#include "serial_api.h"
#include "sys_tool.h"
#include "elog.h"
#include "uw_defines/auv_deck_protocol.h"
#include "uw_defines/uw_device_defines.h"
#include "uw_defines/uw_telemetry_defines.h"
#include "sim_telemetry.h"

int serial_idx = e_virtual_serial1;

int32_t elog_config();

int main()
{
    elog_config();
    log_i(" === AUV Deck data generator === ");

    int32_t ret = 0;
    //ret = start_packet_process();

    ret = serial_init(serial_idx);
    log_i("[CCOM] Serial init ret %d", ret);

    //ret = start_receive(serial_idx);
    //log_i("[CCOM] Serial init ret %d", ret);

    char cmd;
    char* cmd_data;
    uint16_t cmd_data_len = 0;
    char str[30] = {0};
    printf("Press any key to test send, q to quit.\n");
    ret = scanf(" %c", &cmd);

    uint8_t src_id = e_imx6_radio;
    uint8_t dst_id = e_deck_radio;

    uint8_t module_id = 0;
    uint8_t func_id = 0;

    while( cmd != 'q' )
    {
        cmd_data = NULL;
        module_id = 0xFF;
        memset(str, 0, sizeof(str));
        printf("Input a command: ");
        ret = scanf(" %s", str);

        log_i("[Command] %s", str);

        /**************************************/
        //********      General      **********/
        /**************************************/



        /**************************************/
        //********     Telemetry     **********/
        /**************************************/
        if ( strcmp(str, "telemetry") == 0 ||
            strcmp(str, "t") == 0)
        {
            module_id = e_telemetry_packet;
            func_id   = e_telemetry_data;

            cmd_data_len = sizeof(uw_telemetry_frame_t);
            cmd_data = (char*) malloc(cmd_data_len);

            generator_telemetry_frame(cmd_data, cmd_data_len);
        }

        if (module_id == 0xFF)
        {
            log_i("[CCOM] Wrong command string %s", str);

            if (cmd_data != NULL)
            {
                free(cmd_data);
                cmd_data = NULL;
            }
            continue;
        }

        // send ccom command
        ret =  ccom_send_packet(serial_idx,
                                src_id,
                                dst_id,
                                module_id,
                                func_id,
                                cmd_data_len, (int8_t*)cmd_data);
        log_i("[CCOM] ccom send ret %d", ret);

        if ( cmd_data != NULL )
        {
            free(cmd_data);
            cmd_data = NULL;
        }

    }

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