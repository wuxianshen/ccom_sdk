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
#define UW_DEVICE_DAM_PORT 8  //Real 7
#define UW_DEVICE_DECK_PORT 7 //Real 6
#define UW_DEVICE_BATTERY_PORT 9 //to be define
#define UW_DEVICE_RADIO_PORT    10
#define UW_DEVICE_IRIDIUM_PORT  11
#define UW_DEVICE_ACOUSTIC_PORT 12

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

enum serial_list_e
{
    e_gps_serial     = 0,
    e_dvl_serial     = 1,
    e_dam_serial     = 2,
    e_battery_serial = 3,
    e_deck_radio_serial    = 4,
    e_deck_iridium_serial  = 5,
    e_deck_acoustic_serial = 6,
    e_virtual_serial1 = 7,
    e_virtual_serial2 = 8,
    e_serial_num,
};

//
enum uw_ccom_device_e
{
    e_default_serial = -1,
	e_deck_radio    = 0,
	e_deck_iridium  = 1,
	e_deck_acoustic = 2,
	e_imx6_radio    = 3,
	e_imx6_iridium  = 4,
	e_imx6_acoustic = 5,
};

enum can_motor_group_e
{
    e_all_motor_group = 0,
    e_joint1_group    = 1,
    e_joint2_group    = 2,
};

enum auv_model_e
{
    e_auv_model_init = 0,
    e_auv_model_deck = 1,
    e_auv_model_surf = 2,
    e_auv_model_sail = 3,
    e_auv_model_dive = 4,
};

#endif //SUB_PERCEPTION_UW_DEVICE_H
