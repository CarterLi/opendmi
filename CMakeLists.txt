cmake_minimum_required(VERSION 4.1)

project(opendmi VERSION 0.1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)

add_library(libdmi OBJECT src/dmi.c)
target_include_directories(libdmi PUBLIC include)
