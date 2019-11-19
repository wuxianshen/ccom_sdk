/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : gps_api.c
   Author : tao.jing
   Date   : 19-7-12
   Brief  : 
**************************************************************************/
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "serial_api.h"
#include "elog.h"
#include "pc_serial_config.h"

int32_t serial_init(int8_t serial_idx)
{
    int32_t ret = serial_open_device(&serial_handlers[serial_idx], pc_serial_names[serial_idx], pc_serial_baud[serial_idx]);
    return ret;
}

int32_t serial_open_device(serial_t *p_serial, const char* serial_port, int serial_baud)
{
    if (serial_open(p_serial, serial_port, serial_baud) != 0)
    {
        log_e("Serial device open %s failed...", serial_port);
        return -1;
    }

    log_i("Serial Comm device open %s successfully...", serial_port);
    return 0;
}

int8_t serial_read_char(serial_t *p_serial, int8_t* read_state)
{
    char read_char;
    int ret = serial_read(p_serial, (uint8_t*)&read_char, sizeof(read_char), -1);
    if (ret != sizeof(read_char))
    {
        log_e("Serial read char error...\n");
        *read_state = 1;
    }
    else
    {
        *read_state = 0;
    }

    return read_char;
}

int8_t serial_read_one_char(int8_t serial_idx, int8_t* read_state)
{
    return serial_read_char(&serial_handlers[serial_idx], read_state);
}

int32_t serial_send(int8_t serial_idx, char *buf, int len)
{
    int ret = serial_write(&serial_handlers[serial_idx], (uint8_t*)buf, len);
    if ( ret != len )
    {
        log_e("Send error with idx %d, len %d, ret %d", serial_idx, len, ret);
    }
    return ret;
}