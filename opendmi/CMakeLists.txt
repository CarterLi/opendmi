project(opendmi-opendmi)

add_executable(opendmi src/main.c)

target_include_directories(opendmi PRIVATE include)
target_link_libraries(opendmi PRIVATE dmi-shared)
