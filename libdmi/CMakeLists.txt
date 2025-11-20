project(opendmi-libdmi)

add_library(dmi-object OBJECT
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
    src/backend/dump.c)

target_include_directories(dmi-object PUBLIC include)
target_compile_options(dmi-object PRIVATE -fPIC)

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

add_executable(bswap16-test test/bswap16.c)
target_link_libraries(bswap16-test dmi-shared)
add_test(NAME bswap16 COMMAND bswap16-test)

add_executable(decode-word-test test/decode-word.c)
target_link_libraries(decode-word-test dmi-shared)
add_test(NAME decode-word COMMAND decode-word-test)

add_executable(bswap32-test test/bswap32.c)
target_link_libraries(bswap32-test dmi-shared)
add_test(NAME bswap32 COMMAND bswap32-test)

add_executable(decode-dword-test test/decode-dword.c)
target_link_libraries(decode-dword-test dmi-shared)
add_test(NAME decode-dword COMMAND decode-dword-test)

add_executable(bswap64-test test/bswap64.c)
target_link_libraries(bswap64-test dmi-shared)
add_test(NAME bswap64 COMMAND bswap64-test)

add_executable(decode-qword-test test/decode-qword.c)
target_link_libraries(decode-qword-test dmi-shared)
add_test(NAME decode-qword COMMAND decode-qword-test)

add_executable(decode-bcd-test test/decode-bcd.c)
target_link_libraries(decode-bcd-test dmi-shared)
add_test(NAME decode-bcd COMMAND decode-bcd-test)

add_executable(decode-uuid-test test/decode-uuid.c)
target_link_libraries(decode-uuid-test dmi-shared)
add_test(NAME decode-uuid COMMAND decode-uuid-test)

add_executable(ipow32-test test/ipow32.c)
target_link_libraries(ipow32-test dmi-shared)
add_test(NAME ipow32 COMMAND ipow32-test)

add_executable(ipow64-test test/ipow64.c)
target_link_libraries(ipow64-test dmi-shared)
add_test(NAME ipow64 COMMAND ipow64-test)

add_executable(cache-size-test test/cache-size.c)
target_link_libraries(cache-size-test dmi-shared)
add_test(NAME cache-size COMMAND cache-size-test)

add_executable(cache-size-ex-test test/cache-size-ex.c)
target_link_libraries(cache-size-ex-test dmi-shared)
add_test(NAME cache-size-ex COMMAND cache-size-ex-test)
