//
// OpenDMI: DMI/SMBIOS library
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#ifndef OPENDMI_ENTRY_H
#define OPENDMI_ENTRY_H

#pragma once

#include <sys/cdefs.h>
#include <stdint.h>

struct dmi_entry_v21
{
    char anchor[4];
    uint8_t checksum;
    uint8_t length;
    uint8_t version_major;
    uint8_t version_minor;
    uint16_t max_table_size;
    uint8_t revision;
};

struct dmi_entry_v30
{
    char anchor[5];
    uint8_t checksum;
    uint8_t length;
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t version_patch;
    uint8_t revision;
    uint8_t reserved;
    uint32_t max_table_size;
    uint64_t table_addr;
};

#endif // !OPENDMI_ENTRY_H
