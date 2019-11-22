/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : pc_serial_config.h
   Author : tao.jing
   Date   : 19-10-3
   Brief  : 
**************************************************************************/
#ifndef UW_ALL_IN_ONE_PC_SERIAL_CONFIG_H
#define UW_ALL_IN_ONE_PC_SERIAL_CONFIG_H

#include "uw_device.h"
#include "serial.h"

static const char* pc_serial_names[e_serial_num] = {
                                                    "/dev/ttyUSB0",
                                                    "/dev/ttyUSB0",
                                                    "/dev/ttyUSB0",
                                                    "/dev/ttyUSB1",
                                                };

static const int pc_serial_baud[e_serial_num] = {
                                                    19200,
                                                    19200,
                                                    19200,
                                                    19200,
                                                };

static serial_t serial_handlers[e_serial_num];

#endif //UW_ALL_IN_ONE_PC_SERIAL_CONFIG_H
