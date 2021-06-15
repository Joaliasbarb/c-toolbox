cmake_minimum_required(VERSION 3.20)

set(LIB_SRCS_C_TOOLBOX
    ./softwareTimer/accurateTimer.c
    ./softwareTimer/timerManager.c
    ./utils/circularBuffer.c
    ./utils/miscUtils.c
    ./utils/quickSort.c)

add_library(cToolboxLib SHARED ${LIB_SRCS_C_TOOLBOX})

target_include_directories(cToolboxLib PUBLIC
    ./softwareTimer
    ./utils)
