#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
FIND_PATH(LIBYAML_INCLUDE_DIRS
    NAMES yaml.h
    PATHS $ENV{LIBYAML_ROOT}/include
    OPTIONAL
)

FIND_LIBRARY(LIBYAML_LIBRARIES
    NAMES yaml
    PATHS $ENV{LIBYAML_ROOT}/lib
    OPTIONAL
)

if(NOT LIBYAML_INCLUDE_DIRS OR NOT LIBYAML_LIBRARIES)
    if(LibYaml_FIND_REQUIRED)
        message(SEND_ERROR "libyaml library/include file not found, set LIBYAML_ROOT")
    endif()
else()
    set(LibYaml_FOUND TRUE)
    message(STATUS "Found LibYaml: ${LibYaml_LIBRARIES}")
endif()

MARK_AS_ADVANCED(LIBYAML_INCLUDE_DIRS LIBYAML_LIBRARIES)
