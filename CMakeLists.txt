cmake_minimum_required(VERSION 3.16)
project(testmodule C)

set(CMAKE_C_STANDARD 99)

add_executable(testmodule Client/console.c sample/set.c ncursesLibrary/commonNucurses.c ncursesLibrary/commonNucurses.h ncursesLibrary/serverNcurses.c ncursesLibrary/serverNcurses.h ncursesLibrary/clientNcurses.c ncursesLibrary/clientNcurses.h)