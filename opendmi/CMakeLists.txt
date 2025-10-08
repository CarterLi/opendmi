project(opendmi-opendmi)

include_directories(include)
add_executable(opendmi src/main.c)
target_link_libraries(opendmi PRIVATE dmi-shared)
