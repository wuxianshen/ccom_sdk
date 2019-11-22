# *  @Copyright (c) 2019-2029 TJU
# *  Create @ 2019-11-17 by tao.jing
# *  cmake file of main

cmake_minimum_required(VERSION 2.4)
project(ccom_sdk C)

set(CMAKE_C_STANDARD 99)

################
## CMake_Dirs ##
################
# Add module path for <name>.cmake conf files
set(CURRENT_CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
set(CMAKE_MODULE_PATH ${CURRENT_CMAKE_MODULE_PATH})

# Set cmake includes
include(${CMAKE_MODULE_PATH}/compiler_config.cmake)
include(${CMAKE_MODULE_PATH}/elog_config.cmake)

message(STATUS " === Use Compiler ${CMAKE_C_COMPILER}")

##################
## Include_Dirs ##
##################
# General Include Dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sys_tools)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccom_core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/packet)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccom_packet_imp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/serial_driver)

##########################
## Main Target Sources  ##
##########################
# General Source Files
FILE(GLOB SOURCE_FILES *.h *.c

        ${CMAKE_CURRENT_SOURCE_DIR}/sys_tools/*.c

        ${CMAKE_CURRENT_SOURCE_DIR}/ccom_core/*.c

        ${CMAKE_CURRENT_SOURCE_DIR}/packet/*.c

        ${CMAKE_CURRENT_SOURCE_DIR}/ccom_packet_imp/*.c
        )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/serial_driver/  SOURCE_FILES)

# Elog Source Files
set(SOURCE_FILES "${SOURCE_FILES};${ELOG_SOURCES}")

set(SEND_TEST_SOURCE_FILES "${SOURCE_FILES};${CMAKE_CURRENT_SOURCE_DIR}/test/send_test.c")
set(RECV_TEST_SOURCE_FILES "${SOURCE_FILES};${CMAKE_CURRENT_SOURCE_DIR}/test/recv_test.c")

add_executable(send_test ${SEND_TEST_SOURCE_FILES})
add_executable(recv_test ${RECV_TEST_SOURCE_FILES})