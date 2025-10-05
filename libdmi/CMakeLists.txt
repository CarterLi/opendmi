project(opendmi-libdmi)

include_directories(include)
add_compile_options(-Wall -Wextra -Werror -pedantic -Wno-zero-length-array)

add_library(dmi-object OBJECT
    src/table.c
    src/baseboard.c
    src/processor.c
    src/cache.c
    src/utils.c)

add_library(dmi-static STATIC $<TARGET_OBJECTS:dmi-object>)
set_target_properties(dmi-static PROPERTIES OUTPUT_NAME dmi)

add_library(dmi-shared SHARED $<TARGET_OBJECTS:dmi-object>)
set_target_properties(dmi-shared PROPERTIES OUTPUT_NAME dmi)
