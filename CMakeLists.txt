cmake_minimum_required(VERSION 3.16)
project(module C)

set(CMAKE_C_STANDARD 99)
add_executable(module Client/dirmanager.c Client/dirmanager.h Client/testmain.c Client/common.h)