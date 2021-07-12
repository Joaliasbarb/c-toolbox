cmake_minimum_required(VERSION 3.20)
project(c-toolbox)

include(CMakeDependentOption)
find_package(Git)
include("config/versioning.cmake")

if(${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
    set(BUILD_TEST_DEFAULT ON)
else()
    set(BUILD_TEST_DEFAULT OFF)
endif()
option(BUILD_TESTS "Build the tests" ${BUILD_TEST_DEFAULT})
cmake_dependent_option(CODE_COVERAGE "Enable code coverage" ON "BUILD_TESTS AND CMAKE_COMPILER_IS_GNUCXX" OFF)
message("BUILD_TESTS option is ${BUILD_TESTS}")
message("CODE_COVERAGE option is ${CODE_COVERAGE}")

add_library(cToolbox STATIC
    "src/accurateTimer.c"
    "src/timerManager.c"
    "src/circularBuffer.c"
    "src/miscUtils.c")

target_include_directories(cToolbox PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(BUILD_TESTS)
	enable_testing()
    add_subdirectory("test/gtest")
endif()


