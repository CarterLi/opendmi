#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
project(opendmi-libopendmi)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/config.h.in
    ${PROJECT_SOURCE_DIR}/src/config.h
    USE_SOURCE_PERMISSIONS)

add_library(opendmi-object OBJECT)
target_include_directories(opendmi-object PUBLIC include)
target_sources(opendmi-object
    PRIVATE
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
        src/table/onboard-device-ex.c
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
    PUBLIC INTERFACE
        FILE_SET HEADERS
            BASE_DIRS include
            FILES
                include/opendmi/attribute.h
                include/opendmi/backend.h
                include/opendmi/context.h
                include/opendmi/defs.h
                include/opendmi/entry.h
                include/opendmi/error.h
                include/opendmi/extension.h
                include/opendmi/log.h
                include/opendmi/name.h
                include/opendmi/registry.h
                include/opendmi/table.h
                include/opendmi/types.h
                include/opendmi/utils.h
                include/opendmi/value.h
                include/opendmi/version.h
                include/opendmi/backend/dump.h
                include/opendmi/table/additional-info.h
                include/opendmi/table/baseboard.h
                include/opendmi/table/battery.h
                include/opendmi/table/bis-entry-point.h
                include/opendmi/table/cache.h
                include/opendmi/table/chassis.h
                include/opendmi/table/common.h
                include/opendmi/table/cooling-device.h
                include/opendmi/table/current-probe.h
                include/opendmi/table/device.h
                include/opendmi/table/firmware-inventory.h
                include/opendmi/table/firmware-language.h
                include/opendmi/table/firmware.h
                include/opendmi/table/group-assoc.h
                include/opendmi/table/hardware-security.h
                include/opendmi/table/ipmi-device.h
                include/opendmi/table/memory-array-addr.h
                include/opendmi/table/memory-array.h
                include/opendmi/table/memory-channel.h
                include/opendmi/table/memory-controller.h
                include/opendmi/table/memory-device-addr.h
                include/opendmi/table/memory-device.h
                include/opendmi/table/memory-error.h
                include/opendmi/table/memory-error-32.h
                include/opendmi/table/memory-error-64.h
                include/opendmi/table/memory-module.h
                include/opendmi/table/mgmt-controller.h
                include/opendmi/table/mgmt-device.h
                include/opendmi/table/mgmt-device-component.h
                include/opendmi/table/mgmt-device-threshold.h
                include/opendmi/table/oem-strings.h
                include/opendmi/table/onboard-device.h
                include/opendmi/table/oob-remote-access.h
                include/opendmi/table/pointing-device.h
                include/opendmi/table/port-connector.h
                include/opendmi/table/power-controls.h
                include/opendmi/table/power-supply.h
                include/opendmi/table/probe.h
                include/opendmi/table/processor.h
                include/opendmi/table/slot.h
                include/opendmi/table/string-property.h
                include/opendmi/table/system.h
                include/opendmi/table/system-boot.h
                include/opendmi/table/system-config.h
                include/opendmi/table/system-event-log.h
                include/opendmi/table/system-reset.h
                include/opendmi/table/temperature-probe.h
                include/opendmi/table/tpm-device.h
                include/opendmi/table/voltage-probe.h
                include/opendmi/extension/apple.h
                include/opendmi/extension/dell.h
                include/opendmi/extension/intel.h
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(opendmi-object
        PRIVATE
            src/backend/linux.c
        PUBLIC INTERFACE
            FILE_SET HEADERS
                BASE_DIRS include
                FILES include/opendmi/backend/linux.h
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    find_library(COREFOUNDATION_LIB CoreFoundation)
    find_library(IOKIT_LIB IOKit)
    list(APPEND LIBDMI_LIBRARIES ${COREFOUNDATION_LIB} ${IOKIT_LIB})

    target_sources(opendmi-object
        PRIVATE
            src/backend/darwin.c
        PUBLIC INTERFACE
            FILE_SET HEADERS
                BASE_DIRS include
                FILES include/opendmi/backend/darwin.h
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    target_sources(opendmi-object
        PRIVATE
            src/backend/freebsd.c
        PUBLIC INTERFACE
            FILE_SET HEADERS
                BASE_DIRS include
                FILES include/opendmi/backend/freebsd.h
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(opendmi-object
        PRIVATE
            src/backend/windows.c
        PUBLIC INTERFACE
            FILE_SET HEADERS
                BASE_DIRS include
                FILES include/opendmi/backend/windows.h
    )
endif ()

if (NOT MSVC)
target_compile_options(opendmi-object PRIVATE -fPIC)
endif ()

add_library(opendmi-static STATIC $<TARGET_OBJECTS:opendmi-object>)
target_include_directories(opendmi-static INTERFACE include)
target_link_libraries(opendmi-static PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(opendmi-static PROPERTIES OUTPUT_NAME opendmi)

add_library(opendmi-shared SHARED $<TARGET_OBJECTS:opendmi-object>)
target_include_directories(opendmi-shared INTERFACE include)
target_link_libraries(opendmi-shared PUBLIC ${LIBDMI_LIBRARIES})
set_target_properties(opendmi-shared PROPERTIES OUTPUT_NAME opendmi)

install(TARGETS opendmi-object FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS opendmi-static ARCHIVE DESTINATION lib)
install(TARGETS opendmi-shared LIBRARY DESTINATION lib)

macro(opendmi_test name sources)
add_executable(${name}-test ${sources})
target_link_libraries(${name}-test opendmi-shared)
add_test(NAME ${name} COMMAND ${name}-test)
endmacro()

opendmi_test(bswap16 test/bswap16.c)
opendmi_test(decode-word test/decode-word.c)
opendmi_test(bswap32 test/bswap32.c)
opendmi_test(decode-dword test/decode-dword.c)
opendmi_test(bswap64 test/bswap64.c)
opendmi_test(decode-qword test/decode-qword.c)
opendmi_test(decode-bcd test/decode-bcd.c)
opendmi_test(decode-uuid test/decode-uuid.c)
opendmi_test(ipow32 test/ipow32.c)
opendmi_test(ipow64 test/ipow64.c)
opendmi_test(status-name test/status-name.c)
opendmi_test(error-correct-type-name test/error-correct-type-name.c)
opendmi_test(baseboard-type-name test/baseboard-type-name.c)
opendmi_test(chassis-type-name test/chassis-type-name.c)
opendmi_test(chassis-security-status-name test/chassis-security-status-name.c)
opendmi_test(cache-type-name test/cache-type-name.c)
opendmi_test(cache-mode-name test/cache-mode-name.c)
opendmi_test(cache-assoc-name test/cache-assoc-name.c)
opendmi_test(cache-location-name test/cache-location-name.c)
opendmi_test(cache-size test/cache-size.c)
opendmi_test(cache-size-ex test/cache-size-ex.c)
opendmi_test(onboard-device-type-name test/onboard-device-type-name.c)
opendmi_test(memory-array-location-name test/memory-array-location-name.c)
opendmi_test(memory-array-usage-name test/memory-array-usage-name.c)
opendmi_test(memory-interleave-name test/memory-interleave-name.c)
opendmi_test(memory-channel-type-name test/memory-channel-type-name.c)
opendmi_test(memory-device-size test/memory-device-size.c)
opendmi_test(memory-device-size-ex test/memory-device-size-ex.c)
opendmi_test(memory-error-type-name test/memory-error-type-name.c)
opendmi_test(memory-error-granularity-name test/memory-error-granularity-name.c)
opendmi_test(memory-error-operation-name test/memory-error-operation-name.c)
opendmi_test(probe-location-name test/probe-location-name.c)
opendmi_test(battery-chemistry-name test/battery-chemistry-name.c)
opendmi_test(slot-usage-name test/slot-usage-name.c)
opendmi_test(slot-width-name test/slot-width-name.c)
