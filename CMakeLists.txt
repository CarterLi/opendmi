cmake_minimum_required(VERSION 4.1)

project(opendmi VERSION 0.1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(libdmi)
add_subdirectory(libdmi++)
add_subdirectory(opendmi)
