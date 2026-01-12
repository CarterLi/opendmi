#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
message(STATUS "Looking for AsciiDoctor (optional)...")

find_program(ASCIIDOCTOR_EXECUTABLE asciidoctor OPTIONAL)
mark_as_advanced(ASCIIDOCTOR_EXECUTABLE)

if(NOT ASCIIDOCTOR_EXECUTABLE)
    set(ASCIIDOCTOR_FOUND "NO")
else()
    set(ASCIIDOCTOR_FOUND "YES")
    message(STATUS "Found AsciiDoctor: ${ASCIIDOCTOR_EXECUTABLE}")
endif()

if(NOT ASCIIDOCTOR_FOUND AND ASCIIDOCTOR_FIND_REQUIRED)
    MESSAGE(WARNING "AsciiDoctor not found, manual pages generation will be disabled")
endif()
