/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : sim_telemetry.h
   Author : tao.jing
   Date   : 2020/6/14
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_SIM_TELEMETRY_H
#define CCOM_SDK_SIM_TELEMETRY_H

#include <stdint.h>

void generator_telemetry_frame(char* cmd_data, uint16_t cmd_data_len);

#endif //CCOM_SDK_SIM_TELEMETRY_H
