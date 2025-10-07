project(opendmi-libdmi)

include_directories(include)
add_compile_options(-Wall -Wextra -Werror -pedantic -Wno-zero-length-array)

add_library(dmi-object OBJECT
    src/types.c
    src/entry.c
    src/table.c
    src/chassis.c
    src/baseboard.c
    src/processor.c
    src/cache.c
    src/utils.c)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(dmi-object PRIVATE src/backend/linux.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_sources(dmi-object PRIVATE src/backend/darwin.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    target_sources(dmi-object PRIVATE src/backend/freebsd.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(dmi-object PRIVATE src/backend/windows.c)
endif ()

add_library(dmi-static STATIC $<TARGET_OBJECTS:dmi-object>)
set_target_properties(dmi-static PROPERTIES OUTPUT_NAME dmi)

add_library(dmi-shared SHARED $<TARGET_OBJECTS:dmi-object>)
set_target_properties(dmi-shared PROPERTIES OUTPUT_NAME dmi)
