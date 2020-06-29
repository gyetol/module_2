cmake_minimum_required(VERSION 3.16)
project(testmodule C)

set(CMAKE_C_STANDARD 99)

add_executable(testmodule Client/console.c)