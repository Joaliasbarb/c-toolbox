cmake_minimum_required(VERSION 3.20)
project(c-toolbox)

if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
    set(BUILD_TEST_DEFAULT ON)
else()
    set(BUILD_TEST_DEFAULT OFF)
endif()
option(BUILD_TESTS "Build the tests" ${BUILD_TEST_DEFAULT})

# Version management
find_package(Git)
include("config/versioning.cmake")

add_library(cToolbox STATIC
    "src/accurateTimer.c"
    "src/timerManager.c"
    "src/circularBuffer.c"
    "src/miscUtils.c"
    "src/quickSort.c")

target_include_directories(cToolbox PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test/gtest)
endif()


