cmake_minimum_required(VERSION 3.16)
project(module_2 C)

set(CMAKE_C_STANDARD 99)
add_executable(module filesystem/dirmanager.h filesystem/dirmanager.c filesystem/testmain.c filesystem/common.h filesystem/filemanager.c filesystem/filemanager.h)