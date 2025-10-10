project(opendmi-opendmi)

configure_file(src/config.h.in src/config.h USE_SOURCE_PERMISSIONS)
add_executable(opendmi src/main.c)

target_include_directories(opendmi PRIVATE include)
target_link_libraries(opendmi PRIVATE dmi-shared)
