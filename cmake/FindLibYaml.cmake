#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_LIBYAML QUIET libyaml-0.2)
endif()

find_path(LIBYAML_INCLUDE_DIR
    NAMES yaml.h
    HINTS ${PC_LIBYAML_INCLUDEDIR} ${PC_LIBYAML_INCLUDE_DIRS}
)

if(DEFINED LIBYAML_LIBRARIES AND NOT DEFINED LIBYAML_LIBRARY)
    set(LIBYAML_LIBRARY ${LIBYAML_LIBRARIES})
endif()

find_library(LIBYAML_LIBRARY
    NAMES yaml
    HINTS ${PC_LIBYAML_LIBDIR} ${PC_LIBYAML_LIBRARY_DIRS}
)

set(LIBYAML_INCLUDE_DIRS ${LIBYAML_INCLUDE_DIR})
set(LIBYAML_LIBRARIES ${LIBYAML_LIBRARY})

unset(LIBYAML_DEFINITIONS)
foreach(libyaml_pc_lib_dir IN LISTS PC_LIBYAML_LIBDIR PC_LIBYAML_LIBRARY_DIRS)
    if (LIBYAML_LIBRARY MATCHES "^${libyaml_pc_lib_dir}")
        list(APPEND LIBYAML_INCLUDE_DIRS ${PC_LIBYAML_INCLUDE_DIRS})
        set(LIBYAML_DEFINITIONS ${PC_LIBYAML_CFLAGS_OTHER})
        break()
    endif()
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibYaml
    REQUIRED_VARS LIBYAML_LIBRARY LIBYAML_INCLUDE_DIR
    VERSION_VAR LIBYAML_VERSION_STRING
)

mark_as_advanced(LIBYAML_INCLUDE_DIR LIBYAML_LIBRARY)

if(LibYaml_FOUND AND NOT TARGET LibYaml::LibYaml)
    add_library(LibYaml::LibYaml UNKNOWN IMPORTED)
    set_target_properties(LibYaml::LibYaml PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${LIBYAML_INCLUDE_DIRS}")
    set_target_properties(LibYaml::LibYaml PROPERTIES INTERFACE_COMPILE_OPTIONS "${LIBYAML_DEFINITIONS}")
    set_property(TARGET LibYaml::LibYaml APPEND PROPERTY IMPORTED_LOCATION "${LIBYAML_LIBRARY}")
endif()
