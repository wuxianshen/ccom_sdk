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
include(${CMAKE_MODULE_PATH}/ccom_sdk.cmake)

message(STATUS " === Use Compiler ${CMAKE_C_COMPILER}")

##################
## Include_Dirs ##
##################
# General Include Dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ccom_packet_imp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/serial_driver)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/uw_defines)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sim_data_generator)

##########################
## Main Target Sources  ##
##########################
# General Source Files
FILE(GLOB SOURCE_FILES *.h *.c

        ${CMAKE_CURRENT_SOURCE_DIR}/ccom_packet_imp/*.c
        )

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/serial_driver/  SOURCE_FILES)

# Elog Source Files
set(SOURCE_FILES "${SOURCE_FILES};${ELOG_SOURCES}")
set(SOURCE_FILES "${SOURCE_FILES};${CCOM_SDK_SOURCES}")

set(SEND_TEST_SOURCE_FILES "${SOURCE_FILES};${CMAKE_CURRENT_SOURCE_DIR}/test/send_test.c")
set(RECV_TEST_SOURCE_FILES "${SOURCE_FILES};${CMAKE_CURRENT_SOURCE_DIR}/test/recv_test.c")

set(SOURCE_SIM_DATA_GENERATOR "${SOURCE_FILES}")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sim_data_generator/  SOURCE_SIM_DATA_GENERATOR)

set(SOURCE_AUV_2_DECK "${SOURCE_SIM_DATA_GENERATOR}")
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sim_data_generator/auv_deck/  SOURCE_AUV_2_DECK)

set(SOURCE_DECK_2_AUV "${SOURCE_SIM_DATA_GENERATOR}")
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/sim_data_generator/deck_auv/  SOURCE_DECK_2_AUV)

add_executable(send_test ${SEND_TEST_SOURCE_FILES})
add_executable(recv_test ${RECV_TEST_SOURCE_FILES})
add_executable(auv_deck_generator ${SOURCE_AUV_2_DECK})
add_executable(deck_auv_generator ${SOURCE_DECK_2_AUV})