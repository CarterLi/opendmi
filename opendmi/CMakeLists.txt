#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
project(opendmi-opendmi)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

if(Curses_FOUND AND NOT TARGET Curses::Curses)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(
        Curses::Curses
        PROPERTIES
            INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
    )
endif()

configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
    USE_SOURCE_PERMISSIONS)

add_executable(opendmi
    src/main.c
    src/format.c
    src/format/text.c
)

if(ENABLE_JSON)
    target_sources(opendmi PRIVATE src/format/json.c)
endif()

if(ENABLE_XML)
    target_include_directories(opendmi PRIVATE ${LIBXML2_INCLUDE_DIRS})
    target_sources(opendmi PRIVATE src/format/xml.c)
    target_link_libraries(opendmi PRIVATE ${LIBXML2_LIBRARIES})
endif()

if(ENABLE_YAML)
    target_include_directories(opendmi PRIVATE ${LIBYAML_INCLUDE_DIRS})
    target_sources(opendmi PRIVATE src/format/yaml.c)
    target_link_libraries(opendmi PRIVATE ${LIBYAML_LIBRARIES})
endif()

target_include_directories(opendmi PRIVATE include)
target_link_libraries(opendmi PRIVATE opendmi-shared Curses::Curses)

install(TARGETS opendmi RUNTIME DESTINATION bin)
