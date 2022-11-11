cmake_minimum_required(VERSION 3.22)
project(Mineseeper C)

set(CMAKE_C_STANDARD 23)

add_executable(Mineseeper src/slot.h src/slot.c src/game.h src/game.c src/main.c)
