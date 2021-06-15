cmake_minimum_required(VERSION 3.20)
project(c-toolbox)

message("CMAKE_C_COMPILER:" ${CMAKE_C_COMPILER})
message("CMAKE_CXX_COMPILER:" ${CMAKE_CXX_COMPILER})
message("CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN:" ${CMAKE_CXX_COMPILER_EXTERNAL_TOOLCHAIN})
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

find_package(Git)

# Version management
include("${PROJECT_SOURCE_DIR}/config/versioning.cmake")

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
