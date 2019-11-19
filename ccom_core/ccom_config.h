/**************************************************************************

           Copyright(C), 2016-2026, tao.jing All rights reserved

 **************************************************************************
   File   : ccom_config.h
   Author : tao.jing
   Date   : 2019/11/18
   Brief  : 
**************************************************************************/

#ifndef CCOM_SDK_CCOM_CONFIG_H
#define CCOM_SDK_CCOM_CONFIG_H

#define CCOM_RECV_BUF_LEN 1024

#define CCOM_FRAME_HEADER1 0x55
#define CCOM_FRAME_HEADER2 0xAA

#define CCOM_FRAME_HEADER_LEN 6
#define CCOM_FRAME_CHECKSUM_LEN 2

#define CCOM_FRAME_LENGTH_CURSOR 2
#define CCOM_FRAME_CONTENT_CURSOR CCOM_FRAME_HEADER_LEN

#define CCOM_PACKET_HEADER_LEN 4

#endif //CCOM_SDK_CCOM_CONFIG_H
