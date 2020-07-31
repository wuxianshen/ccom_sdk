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

static char* platform_serial[e_serial_num] = {
        "pc_gps_serial_0",
        "pc_dvl_serial_1",
        "pc_dam_serial_2",
        "pc_battery_serial_3",
        "pc_deck_radio_serial_4",
        "pc_deck_iridium_serial_5",
        "pc_deck_acoustic_serial_6",
        "pc_virtual_serial1_7",
        "pc_virtual_serial2_8"
};

static const char* pc_serial_names[e_serial_num] = {
        "/dev/ttyUSB0",
        "/dev/ttyUSB1",
        "/dev/ttyUSB2",
        "/dev/ttyUSB3",
        "/dev/ttyS1",
        "/dev/ttyS2",
        "/dev/ttyS3",
        "/dev/ttyS1",//"/dev/pts/20",
        "/dev/ttyS2",//"/dev/pts/21"
};

static const int pc_serial_baud[e_serial_num] = {
        19200,
        19200,
        9600,
        19200,
        19200,
        19200,
        19200,
        19200,
        19200
};

static serial_t serial_handlers[e_serial_num];

#endif //UW_ALL_IN_ONE_PC_SERIAL_CONFIG_H