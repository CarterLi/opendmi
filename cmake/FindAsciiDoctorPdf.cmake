#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
message(STATUS "Looking for AsciiDoctor-PDF (optional)...")

find_program(ASCIIDOCTOR_PDF_EXECUTABLE asciidoctor-pdf OPTIONAL)
mark_as_advanced(ASCIIDOCTOR_PDF_EXECUTABLE)

if(NOT ASCIIDOCTOR_PDF_EXECUTABLE)
    set(ASCIIDOCTOR_PDF_FOUND "NO")
else()
    set(ASCIIDOCTOR_PDF_FOUND "YES")
    message(STATUS "Found AsciiDoctor-PDF: ${ASCIIDOCTOR_PDF_EXECUTABLE}")
endif()

if(NOT ASCIIDOCTOR_PDF_FOUND AND ASCIIDOCTOR_PDF_FIND_REQUIRED)
    MESSAGE(WARNING "AsciiDoctor-PDF not found, reference manual generation will be disabled")
endif()
