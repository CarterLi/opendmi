cmake_minimum_required(VERSION 3.31)

project(opendmi
        VERSION 0.1.0
        DESCRIPTION "Cross-platform DMI/SMBIOS framework"
        HOMEPAGE_URL https://github.com/sdnvx/opendmi
        LANGUAGES C CXX)

set(OPENDMI_VERSION "${CMAKE_PROJECT_VERSION}")

set(OPENDMI_VERSION_MAJOR "${CMAKE_PROJECT_VERSION_MAJOR}")
set(OPENDMI_VERSION_MINOR "${CMAKE_PROJECT_VERSION_MINOR}")
set(OPENDMI_VERSION_PATCH "${CMAKE_PROJECT_VERSION_PATCH}")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

if(MSVC)
    add_compile_options(PRIVATE /W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)

    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
       "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        add_compile_options(-Wno-gnu-zero-variadic-macro-arguments -Wno-keyword-macro)
    endif()
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_compile_options(-g -fno-omit-frame-pointer)

#   if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
#      "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
#       add_compile_options(--analyze -Xanalyzer -analyzer-output=text)
#   elseif("${CMALE_CXX_COMPILER_ID}" STREQUAL "GNU")
#       add_compile_options(-fanalyzer)
#   endif()
else()
    add_compile_options(-O2)
    add_compile_definitions(NDEBUG)
endif()

enable_testing()

add_subdirectory(libdmi)
add_subdirectory(libdmi++)
add_subdirectory(opendmi)
