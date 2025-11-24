project(opendmi-opendmi)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
    USE_SOURCE_PERMISSIONS)

add_executable(opendmi src/main.c)

target_include_directories(opendmi PRIVATE include)
target_link_libraries(opendmi PRIVATE opendmi-shared)

install(TARGETS opendmi RUNTIME DESTINATION bin)
