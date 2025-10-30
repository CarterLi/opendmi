cmake_minimum_required(VERSION 4.1)

project(opendmi
        VERSION 0.1.0
        DESCRIPTION "Cross-platform DMI/SMBIOS framework"
        HOMEPAGE_URL https://github.com/sdnvx/opendmi
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)

set(OPENDMI_VERSION "${CMAKE_PROJECT_VERSION}")

set(OPENDMI_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}")
set(OPENDMI_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}")
set(OPENDMI_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}")

add_subdirectory(libdmi)
add_subdirectory(libdmi++)
add_subdirectory(opendmi)
