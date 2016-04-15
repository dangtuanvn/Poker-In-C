cmake_minimum_required(VERSION 3.3)
project(COSC2451_A2_s3500286_s3500291)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_BUILD_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(SOURCE_FILES test.c
        src/poker.c
        src/demo.c)
set(HEADER_FILES src/poker.h)
set(POKER_SOURCE_FILES src/poker.c)
set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(demo src/demo.c ${POKER_SOURCE_FILES})