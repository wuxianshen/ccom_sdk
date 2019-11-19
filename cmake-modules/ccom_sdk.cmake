
set(CCOM_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ccom_sdk/)

##################
## Include_Dirs ##
##################
#Place OS related header files in front
#OS related header files take effect if there are homonymic header files
include_directories(${CCOM_SDK_PATH}/ccom_core)
include_directories(${CCOM_SDK_PATH}/packet)
include_directories(${CCOM_SDK_PATH}/sys_tools)

##################
## Source_Dirs  ##
##################
aux_source_directory(${CCOM_SDK_PATH}/ccom_core/ CCOM_SDK_SOURCES)
aux_source_directory(${CCOM_SDK_PATH}/packet/ CCOM_SDK_SOURCES)
aux_source_directory(${CCOM_SDK_PATH}/sys_tools/ CCOM_SDK_SOURCES)