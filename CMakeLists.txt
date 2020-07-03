cmake_minimum_required(VERSION 3.16)
project(module_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(module_2 ncursesLib/commonNucurses.c ncursesLib/commonNucurses.h ncursesLib/clientNcurses.c)
