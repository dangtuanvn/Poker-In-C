cmake_minimum_required(VERSION 3.3)
project(COSC2451_A2_s3500286_s3500291)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -D_POSIX_C_SOURCE=199309L")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_BUILD_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(SOURCE_FILES
        src/poker.c
        src/player.c
        src/card.c
        src/deck.c
        src/gameround.c
#        src/poker_game.c
#        src/display.c
        src/demo.c
        )

set(HEADER_FILES
        src/poker.h
        src/player.h
        src/card.h
        src/deck.h
        src/gameround.h
        src/display.h
   )

set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(poker_game src/poker_game.c ${SOURCE_FILES})
add_executable(demo src/demo.c ${SOURCE_FILES})
target_link_libraries(poker_game ncursesw)