cmake_minimum_required(VERSION 3.1)
project(HotelManagement C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    .gitignore
    LICENSE
    README.md)

add_executable(HotelManagement ${SOURCE_FILES} main.c database.c pch.h database.h rooms.h rooms.c bookings.h bookings.c customers.h customers.c)