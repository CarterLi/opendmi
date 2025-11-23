project(opendmi-libdmi)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
    USE_SOURCE_PERMISSIONS)

set(LIBDMI_SOURCES
    src/name.c
    src/utils.c
    src/error.c
    src/log.c
    src/context.c
    src/entry.c
    src/table.c
    src/attribute.c
    src/registry.c
    src/table/additional-info.c
    src/table/baseboard.c
    src/table/battery.c
    src/table/bis-entry-point.c
    src/table/cache.c
    src/table/chassis.c
    src/table/common.c
    src/table/cooling-device.c
    src/table/current-probe.c
    src/table/firmware.c
    src/table/firmware-inventory.c
    src/table/firmware-language.c
    src/table/group-assoc.c
    src/table/hardware-security.c
    src/table/ipmi-device.c
    src/table/memory-array.c
    src/table/memory-array-addr.c
    src/table/memory-channel.c
    src/table/memory-controller.c
    src/table/memory-device.c
    src/table/memory-device-addr.c
    src/table/memory-error.c
    src/table/memory-error-32.c
    src/table/memory-error-64.c
    src/table/memory-module.c
    src/table/mgmt-controller.c
    src/table/mgmt-device.c
    src/table/mgmt-device-component.c
    src/table/mgmt-device-threshold.c
    src/table/oem-strings.c
    src/table/onboard-device.c
    src/table/oob-remote-access.c
    src/table/pointing-device.c
    src/table/port-connector.c
    src/table/power-controls.c
    src/table/power-supply.c
    src/table/probe.c
    src/table/processor.c
    src/table/slot.c
    src/table/string-property.c
    src/table/system.c
    src/table/system-boot.c
    src/table/system-config.c
    src/table/system-event-log.c
    src/table/system-reset.c
    src/table/temperature-probe.c
    src/table/tpm-device.c
    src/table/voltage-probe.c
    src/extension/apple.c
    src/extension/dell.c
    src/extension/intel.c
    src/backend/dump.c
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND LIBDMI_SOURCES src/backend/linux.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(COREFOUNDATION_LIB CoreFoundation)
    find_library(IOKIT_LIB IOKit)
    list(APPEND LIBDMI_LIBRARIES ${COREFOUNDATION_LIB} ${IOKIT_LIB})

    list(APPEND LIBDMI_SOURCES src/backend/darwin.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    list(APPEND LIBDMI_SOURCES src/backend/freebsd.c)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND LIBDMI_SOURCES src/backend/windows.c)
endif ()

add_library(dmi-object OBJECT ${LIBDMI_SOURCES})
target_include_directories(dmi-object PUBLIC include)
target_compile_options(dmi-object PRIVATE -fPIC)

add_library(dmi-static STATIC $<TARGET_OBJECTS:dmi-object>)
target_include_directories(dmi-static INTERFACE include)
target_link_libraries(dmi-static PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(dmi-static PROPERTIES OUTPUT_NAME dmi)

add_library(dmi-shared SHARED $<TARGET_OBJECTS:dmi-object>)
target_include_directories(dmi-shared INTERFACE include)
target_link_libraries(dmi-shared PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(dmi-shared PROPERTIES OUTPUT_NAME dmi)

macro(libdmi_test name sources)
add_executable(${name}-test ${sources})
target_link_libraries(${name}-test dmi-shared)
add_test(NAME ${name} COMMAND ${name}-test)
endmacro()

libdmi_test(bswap16 test/bswap16.c)
libdmi_test(decode-word test/decode-word.c)
libdmi_test(bswap32 test/bswap32.c)
libdmi_test(decode-dword test/decode-dword.c)
libdmi_test(bswap64 test/bswap64.c)
libdmi_test(decode-qword test/decode-qword.c)
libdmi_test(decode-bcd test/decode-bcd.c)
libdmi_test(decode-uuid test/decode-uuid.c)
libdmi_test(ipow32 test/ipow32.c)
libdmi_test(ipow64 test/ipow64.c)
libdmi_test(status-name test/status-name.c)
libdmi_test(ecc-type-name test/ecc-type-name.c)
libdmi_test(chassis-type-name test/chassis-type-name.c)
libdmi_test(chassis-state-name test/chassis-state-name.c)
libdmi_test(cache-size test/cache-size.c)
libdmi_test(cache-size-ex test/cache-size-ex.c)
libdmi_test(memory-device-size test/memory-device-size.c)
libdmi_test(memory-device-size-ex test/memory-device-size-ex.c)
libdmi_test(battery-chemistry-name test/battery-chemistry-name.c)
