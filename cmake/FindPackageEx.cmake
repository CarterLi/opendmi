#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
macro(find_package_ex PACKAGE FLAG)
    if(NOT DEFINED ${FLAG} OR "${${FLAG}}" STREQUAL "AUTO")
        message(STATUS "Looking for ${PACKAGE} (optional)...")

        find_package(${PACKAGE} ${ARGN})
        if (${PACKAGE}_FOUND)
            set(${FLAG} ON)
        endif()
    elseif($<BOOL:${${FLAG}}>)
        message(STATUS "Looking for ${PACKAGE} (required)...")

        find_package(${PACKAGE} REQUIRED ${ARGN})
    endif()
endmacro()
