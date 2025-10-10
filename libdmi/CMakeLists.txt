project(opendmi-libdmi)

add_compile_options(-Wall -Wextra -Werror -pedantic -Wno-zero-length-array)

add_library(dmi-object OBJECT
    src/types.c
    src/utils.c
    src/error.c
    src/context.c
    src/entry.c
    src/table.c
    src/table/chassis.c
    src/table/baseboard.c
    src/table/processor.c
    src/table/cache.c
    src/table/battery.c
    src/table/probe.c
    src/table/cooler.c
    src/backend/dump.c)

target_include_directories(dmi-object PUBLIC include)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(dmi-object PRIVATE src/backend/linux.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(COREFOUNDATION_LIB CoreFoundation)
    find_library(IOKIT_LIB IOKit)
    list(APPEND LIBDMI_LIBRARIES ${COREFOUNDATION_LIB} ${IOKIT_LIB})

    target_sources(dmi-object PRIVATE src/backend/darwin.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    target_sources(dmi-object PRIVATE src/backend/freebsd.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(dmi-object PRIVATE src/backend/windows.c)
endif ()

add_library(dmi-static STATIC $<TARGET_OBJECTS:dmi-object>)
target_include_directories(dmi-static INTERFACE include)
target_link_libraries(dmi-static PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(dmi-static PROPERTIES OUTPUT_NAME dmi)

add_library(dmi-shared SHARED $<TARGET_OBJECTS:dmi-object>)
target_include_directories(dmi-shared INTERFACE include)
target_link_libraries(dmi-shared PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(dmi-shared PROPERTIES OUTPUT_NAME dmi)
