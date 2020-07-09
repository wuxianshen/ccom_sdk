/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : sim_telemetry.c
   Author : tao.jing
   Date   : 2020/6/14
   Brief  : 
**************************************************************************/
#include <assert.h>
#include <string.h>
#include <time.h>
#include "sim_telemetry.h"
#include "elog.h"
#include "uw_defines/uw_telemetry_defines.h"

/************************************************************************
 ** 函数名:     get_sys_runtime
 ** 函数描述:   返回系统运行时间
 ** 参数:       [in]  1 - 秒,2 - 毫秒
 ** 返回:       秒/毫秒
 ************************************************************************/
static long get_sys_runtime(int type)
{
    struct timespec times = {0, 0};
    long time;

    clock_gettime(CLOCK_MONOTONIC, &times);
    //printf("CLOCK_MONOTONIC: %lu, %lu\n", times.tv_sec, times.tv_nsec);

    if (1 == type){
        time = times.tv_sec;
    }else{
        time = times.tv_sec * 1000 + times.tv_nsec / 1000000;
    }

    //printf("time = %ld\n", time);
    return time;
}

void generator_telemetry_frame(char* cmd_data, uint16_t cmd_data_len)
{
    log_i("[Sim AUV Data] Send sim telemetry frame...");

    assert(cmd_data_len == sizeof(uw_telemetry_frame_t));
    assert(cmd_data != NULL);

    uw_telemetry_frame_t* p_data = (uw_telemetry_frame_t*)cmd_data;

    // Timestamp
    p_data->timestamp.host_utc_time = (uint32_t)time(NULL);
    p_data->timestamp.ins_utc_time  = (uint32_t)time(NULL);
    p_data->timestamp.internal_sec_time = (uint32_t)get_sys_runtime(1);

    // Relay state
    uint16_t relay_data = 0xAAAA; //0xAAAA 0x5555
    memcpy(&(p_data->relay_state), &relay_data, sizeof(uint16_t));
    //log_i("Relay %d state %d", 0, p_data->relay_state.relay00);

    // Battery state
    p_data->battery_state.voltage = 240;
    p_data->battery_state.current = 20;
    p_data->battery_state.state_of_charge = 70;

    // INS state
    p_data->ins_state.ins_state = 0;
    p_data->ins_state.ins_error_info = 100;
    p_data->ins_state.imu_state = 11;
    p_data->ins_state.imu_error_info = 100;
    p_data->ins_state.navigation_state = 100;
    p_data->ins_state.dvl_state = 1;
    p_data->ins_state.gps_state = 1;

    // GPS state
    p_data->gps_state.longitude = 117098685;
    p_data->gps_state.latitude  = 39063481;
    p_data->gps_state.height = 0;

    // Pose state
    p_data->pose_state.roll  = 100;
    p_data->pose_state.pitch = -50;
    p_data->pose_state.yaw   = 20;

    // Vel state
    p_data->vel_state.east_vel  = 50;
    p_data->vel_state.north_vel = 60;
    p_data->vel_state.up_vel    = -10;

    // Ang Vel state
    p_data->vel_state.east_vel  = 5;
    p_data->vel_state.north_vel = 0;
    p_data->vel_state.up_vel    = 5;
}
