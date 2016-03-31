cmake_minimum_required(VERSION 3.3)
project(COSC2451_A2_s3500286_s3500291)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_BUILD_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(SOURCE_FILES test.c
        poker.c)

set(HEADER_FILES poker.h)
set(POKER_SOURCE_FILES poker.c)

add_executable(testfile test.c)