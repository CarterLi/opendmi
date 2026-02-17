#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_LIBYAJL QUIET libyajl-2.1)
endif()

find_path(LIBYAJL_INCLUDE_DIR
    NAMES yajl/yajl_parse.h
    HINTS ${PC_LIBYAJL_INCLUDEDIR} ${PC_LIBYAJL_INCLUDE_DIRS}
)

if(DEFINED LIBYAJL_LIBRARIES AND NOT DEFINED LIBYAJL_LIBRARY)
    set(LIBYAJL_LIBRARY ${LIBYAJL_LIBRARIES})
endif()

find_library(LIBYAJL_LIBRARY
    NAMES yajl
    HINTS ${PC_LIBYAJL_LIBDIR} ${PC_LIBYAJL_LIBRARY_DIRS}
)

set(LIBYAJL_INCLUDE_DIRS ${LIBYAJL_INCLUDE_DIR})
set(LIBYAJL_LIBRARIES ${LIBYAJL_LIBRARY})

unset(LIBYAJL_DEFINITIONS)
foreach(libyajl_pc_lib_dir IN LISTS PC_LIBYAJL_LIBDIR PC_LIBYAJL_LIBRARY_DIRS)
    if (LIBYAJL_LIBRARY MATCHES "^${libyajl_pc_lib_dir}")
        list(APPEND LIBYAJL_INCLUDE_DIRS ${PC_LIBYAJL_INCLUDE_DIRS})
        set(LIBYAJL_DEFINITIONS ${PC_LIBYAJL_CFLAGS_OTHER})
        break()
    endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibYajl
    REQUIRED_VARS LIBYAJL_LIBRARY LIBYAJL_INCLUDE_DIR
    VERSION_VAR LIBYAJL_VERSION_STRING
)

mark_as_advanced(LIBYAJL_INCLUDE_DIR LIBYAJL_LIBRARY)

if(LibYajl_FOUND AND NOT TARGET LibYajl::LibYajl)
    add_library(LibYajl::LibYajl UNKNOWN IMPORTED)
    set_target_properties(LibYajl::LibYajl PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${LIBYAJL_INCLUDE_DIRS}")
    set_target_properties(LibYajl::LibYajl PROPERTIES INTERFACE_COMPILE_OPTIONS "${LIBYAJL_DEFINITIONS}")
    set_property(TARGET LibYajl::LibYajl APPEND PROPERTY IMPORTED_LOCATION "${LIBYAJL_LIBRARY}")
endif()
