#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
message(STATUS "Looking for CppCheck (optional)...")

find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)

if(CPPCHECK_EXECUTABLE)
    set(CPPCHECK_FOUND "YES")
    message(STATUS "Found CppCheck: ${CPPCHECK_EXECUTABLE}")
else()
    set(CPPCHECK_FOUND "NO")
    MESSAGE(WARNING "CppCheck not found, static analysis is disabled")
endif()

if(CPPCHECK_FOUND)
    list(APPEND CPPCHECK_FLAGS
        --language=c
        --library=posix
        --inconclusive
        --enable=all
        --disable=missingInclude,unusedFunction,information
        --suppress=constParameterCallback
        --suppress=*:*_deps/*
        --inline-suppr
    )

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        list(APPEND CPPCHECK_FLAGS -D__linux__)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        list(APPEND CPPCHECK_FLAGS -D__APPLE__)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
        list(APPEND CPPCHECK_FLAGS -D__FreeBSD__)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        list(APPEND CPPCHECK_FLAGS -D_WIN32)
    endif()

    set(CMAKE_C_CPPCHECK ${CPPCHECK_EXECUTABLE} ${CPPCHECK_FLAGS})
endif()
