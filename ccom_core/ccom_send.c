/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_send.c
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/
#include <malloc.h>
#include <string.h>
#include "ccom_send.h"
#include "ccom_config.h"
#include "ccom_frame_verify.h"
#include "serial_api.h"
#include "elog.h"
#include "packet_def.h"
#include "uw_device.h"
//#include "pc_serial_config.h"

int8_t ccom_send_buffer(int8_t serial_idx, uint16_t send_len, int8_t* buf)
{
    int8_t frame_header[CCOM_FRAME_HEADER_LEN] = {0x55, 0xAA, 0x00, 0x00, 0x00, 0x00};
    frame_header[CCOM_FRAME_LENGTH_CURSOR] = (uint8_t)send_len;
    frame_header[CCOM_FRAME_LENGTH_CURSOR + 1] = (uint8_t)(send_len >> 8);
    frame_header[CCOM_FRAME_HEADER_LEN - 1] = get_checksum_u8(frame_header, CCOM_FRAME_HEADER_LEN - 1);
    uint16_t package_checksum = get_checksum_u16(buf, send_len);

    int32_t send_len_header =  serial_send(serial_idx, (char*)frame_header, CCOM_FRAME_HEADER_LEN);
    if ( send_len_header != CCOM_FRAME_HEADER_LEN )
    {
        log_e("Error send frame header, send len %d, serial idx %d", send_len_header, serial_idx);
        return 1;
    }

    int32_t send_len_package =  serial_send(serial_idx, (char*)buf, send_len);
    if ( send_len_package != send_len )
    {
        log_e("Error send frame content, send len %d (%d), serial idx %d", send_len_package, send_len, serial_idx);
        return 2;
    }

    int32_t send_len_checksum =  serial_send(serial_idx, (char*)&package_checksum, sizeof(uint16_t));
    if ( send_len_checksum != sizeof(uint16_t) )
    {
        log_e("Error send frame checksum, send len %d (%d), serial idx %d", send_len_checksum, sizeof(uint16_t), serial_idx);
        return 3;
    }

    return 0;
}

int8_t ccom_send_packet(int8_t serial_idx,
                        uint8_t src_id,
                        uint8_t dst_id,
                        uint8_t module_id,
                        uint8_t func_id,
                        uint16_t data_len, int8_t* data)
{
    if ( serial_idx == e_default_serial )
    {
        //Use default registered serial
        src_id = g_packet_serial_map[module_id][func_id];
        log_i("module %d func %d : src_id %d", module_id, func_id, src_id);
        switch( src_id )
        {
            case e_imx6_radio:
                serial_idx = e_deck_radio_serial;
                dst_id = e_deck_radio;
                break;
            case e_imx6_iridium:
                serial_idx = e_deck_iridium_serial;
                dst_id = e_deck_iridium;
                break;
            case e_imx6_acoustic:
                serial_idx = e_deck_acoustic_serial;
                dst_id = e_deck_acoustic;
                break;
            default:
                break;
        }
    }

    uint16_t send_len = data_len + CCOM_PACKET_HEADER_LEN;
    int8_t* package_buf = (int8_t*) malloc(send_len);
    package_buf[0] = src_id;
    package_buf[1] = dst_id;
    package_buf[2] = module_id;
    package_buf[3] = func_id;
    if (data != NULL)
    {
        memcpy(package_buf+4, data, data_len);
    }

    log_i("[CCOM] Send packet serial idx %d", serial_idx);
    //log_i("[CCOM] Send packet serial name %s", pc_serial_names[serial_idx]);
    ccom_send_buffer(serial_idx, send_len, package_buf);

    free(package_buf);

    return 0;
}
