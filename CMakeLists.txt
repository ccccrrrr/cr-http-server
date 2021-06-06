cmake_minimum_required(VERSION 3.19)
project(http_server_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(http_server_2

        server.c)
