cmake_minimum_required(VERSION 3.23)
project(Mineseeper C)

set(CMAKE_C_STANDARD 23)

add_executable(Mineseeper src/slot.h src/slot.c src/game.c src/game.h src/main.c)
