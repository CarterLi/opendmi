#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025-2026, The OpenDMI contributors
#
# SPDX-License-Identifier: BSD-3-Clause
#
project(opendmi-reference)

if(ASCIIDOCTOR_FOUND)
    set(REFERENCE_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/reference.pdf)
    file(GLOB_RECURSE REFERENCE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.adoc)

    add_custom_command(
        OUTPUT ${REFERENCE_OUTPUT}
        COMMAND ${ASCIIDOCTOR_EXECUTABLE}
            --require asciidoctor-pdf
            --backend pdf
            --out-file ${REFERENCE_OUTPUT}
            ${CMAKE_CURRENT_SOURCE_DIR}/src/index.adoc
        DEPENDS ${REFERENCE_SOURCES}
    )

    add_custom_target(opendmi-reference ALL DEPENDS ${REFERENCE_OUTPUT})
endif()
