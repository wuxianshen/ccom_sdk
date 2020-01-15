/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_frame_verify.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include "ccom_frame_verify.h"
#include "checksum.h"

uint8_t get_checksum_u8(int8_t* buf, uint32_t len)
{
    /*
    uint8_t check_sum = 0;
    for( uint32_t idx = 0; idx < len; idx++ )
    {
        check_sum += (uint8_t)buf[idx];
    }
    return check_sum;
    */
    uint8_t crc8 = 0;
    for (uint32_t idx = 0; idx < len; idx ++)
    {
        crc8 = update_crc_8(crc8, (unsigned char) *(buf+idx));
    }
    return crc8;
}

uint16_t get_checksum_u16(int8_t* buf, uint32_t len)
{
    /*
    uint16_t check_sum = 0;
    for( uint32_t idx = 0; idx < len; idx++ )
    {
        check_sum += (uint8_t)buf[idx];
    }
    return check_sum;
    */
    uint16_t crc16 = 0;
    for (uint32_t idx = 0; idx < len; idx ++)
    {
        crc16 = update_crc_16(crc16, (unsigned char) *(buf+idx));
    }
    return crc16;
}
