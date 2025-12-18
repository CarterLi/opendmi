#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
project(opendmi-libopendmi-python)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

add_library(opendmi-python SHARED)
target_include_directories(opendmi-python PRIVATE include ${Python3_INCLUDE_DIRS})
target_link_libraries(opendmi-python PRIVATE Python3::Python opendmi-shared)
target_sources(opendmi-python
    PRIVATE
        src/module.c
        src/context.c
)
