cmake_minimum_required(VERSION 3.17)
project(PRG2_labo2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wconversion -Wpadded -Wsign-conversion -pedantic")

add_executable(PRG2_labo2 main.c Bateaux.c)