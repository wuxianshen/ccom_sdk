/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : uw_device.h
   Author : tao.jing
   Date   : 19-7-22
   Brief  : 
**************************************************************************/
#ifndef SUB_PERCEPTION_UW_DEVICE_H
#define SUB_PERCEPTION_UW_DEVICE_H

//Read serial port label is this port -1
//Param (Real)
//5(4) - Used by 618 for GPS
#define UW_DEVICE_GPS_PORT 1
#define UW_DEVICE_DVL_PORT 2
#define UW_DEVICE_DAM_PORT 8
#define UW_DEVICE_DECK_PORT 7

#define SERIAL_POWER_ON  1
#define SERIAL_POWER_OFF 2

#define SERIAL_RS232_MODE 2
#define SERIAL_RS422_MODE 1

#define SERIAL_BAUD_115200 1
#define SERIAL_BAUD_9600   2

//UW Power Port
#define UW_RELAY_PORT_ON  1
#define UW_RELAY_PORT_OFF 2

//IMX6 Relay Port
#define UW_PROPELLER_POWER_PORT 1
#define UW_JOINT1_POWER_PORT    5
#define UW_JOINT2_POWER_PORT    2
#define UW_IMU_POWER_PORT       0
#define UW_GPS_POWER_PORT       5
#define UW_DVL_POWER_PORT       6
#define UW_DAM_POWER_PORT       4
#define UW_DEPTH_POWER_PORT     8
#define UW_HUMIDITY_POWER_PORT  9
#define UW_RADIO_COMM_POWER_PORT    3
#define UW_IRIDIUM_COMM_POWER_PORT  11
#define UW_ACOUSTIC_COMM_POWER_PORT 12

enum serial_list
{
    e_gps_serial  = 0,
    e_dvl_serial  = 1,
    e_dam_serial  = 2,
    e_deck_serial = 3,
    e_serial_num,
};
#endif //SUB_PERCEPTION_UW_DEVICE_H
