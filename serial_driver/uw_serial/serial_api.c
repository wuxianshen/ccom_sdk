/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : deck_api.c
   Author : tao.jing
   Date   : 19-7-12
   Brief  : 
**************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "uw_api.h"
#include "uw_device.h"
#include "elog.h"
#include "uw_serial_config.h"
#include "serial_api.h"

int32_t serial_init(int8_t serial_idx)
{
    int ret = 0;
    ret = rs232_rs422_power_set(uw_serial_port[serial_idx], SERIAL_POWER_ON);
    if (ret)
    {
        log_e("Power set error, serial idx %d, ret %d...", serial_idx, ret);
        return -1;
    }
    ret = rs232_rs422_mode_switch(uw_serial_port[serial_idx], SERIAL_RS232_MODE);
    if (ret)
    {
        log_e("Mode switch error, serial idx %d, ret %d...", serial_idx, ret);
        return -1;
    }
    ret = rs232_rs422_cfg(uw_serial_port[serial_idx], uw_serial_baud[serial_idx], 8, 1, 0);
    if (ret)
    {
        log_e("Config error, serial idx %d, ret %d...", serial_idx, ret);
        return -1;
    }
    return 0;
}


int32_t uw_serial_send(int8_t serial_idx, char *buf, int len)
{
    int ret = rs232_rs422_send(uw_serial_port[serial_idx], buf, (uint32_t*)&len);
    if (ret != 0)
    {
        log_e("Send error...serial idx %d, port %c, ret %d", serial_idx, uw_serial_port[serial_idx], ret);
    }
    return ret;
}

int32_t uw_serial_read(int8_t serial_idx, char *buf, int len)
{
    int ret = rs232_rs422_recv(uw_serial_port[serial_idx], buf, (uint32_t*)&len);

    if (ret == 69651)
    {
        log_e("Recv error...serial idx %d ret %d", serial_idx, ret);
    }

    return ret;
}

int8_t uw_serial_read_char(int8_t serial_idx, char *p_read_char)
{
    int ret = uw_serial_read(serial_idx, p_read_char, sizeof(char));
    if (ret != sizeof(char))
    {
        //printf("Serial read char error...\n");
        return false;
    }

    return true;
}

int8_t uw_serial_read_byte(int8_t serial_idx, int8_t *state)
{
    char read_byte;
    uint32_t len = 1;
    int ret = rs232_rs422_recv(uw_serial_port[serial_idx], &read_byte, &len);

    if (ret == 69651)
    {
        //printf("Recv error...%d\n", ret);
        *state = false;
        return 0xFF;
    }

    *state = true;
    return read_byte;
}

int8_t serial_read_one_char(int8_t serial_idx, int8_t* read_state)
{
    return uw_serial_read_byte(serial_idx, read_state);
}

int32_t serial_send(int8_t serial_idx, char *buf, int len)
{
    return uw_serial_send(serial_idx, buf, len);
}