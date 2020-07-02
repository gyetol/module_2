cmake_minimum_required(VERSION 3.16)
project(module_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(module_2 socket_con/ftp_client.c ncursesLibrary/clientNcurses.c ncursesLibrary/clientNcurses.h)
