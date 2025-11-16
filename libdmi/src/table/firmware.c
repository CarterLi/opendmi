//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdlib.h>

#include <opendmi/name.h>
#include <opendmi/utils.h>
#include <opendmi/table/firmware.h>

static const dmi_name_t dmi_firmware_feature_names[] =
{
    {
        .id   = 2,
        .code = "unknown",
        .name = "Unknown"
    },
    {
        .id   = 3,
        .code = "unsupported",
        .name = "Firmware characteristics are not supported"
    },
    {
        .id   = 4,
        .code = "isa-support",
        .name = "ISA support"
    },
    {
        .id   = 5,
        .code = "mca-support",
        .name = "MCA support"
    },
    {
        .id   = 6,
        .code = "eisa-support",
        .name = "EISA support"
    },
    {
        .id   = 7,
        .code = "pci-support",
        .name = "PCI support"
    },
    {
        .id   = 8,
        .code = "pcmcia-support",
        .name = "PC card (PCMCIA) support"
    },
    {
        .id   = 9,
        .code = "pnp-support",
        .name = "Plug and Play support"
    },
    {
        .id   = 10,
        .code = "apm-support",
        .name = "APM support"
    },
    {
        .id   = 11,
        .code = "upgradeable-flash",
        .name = "Firmware is upgradeable (flash)"
    },
    {
        .id   = 12,
        .code = "shadowing-allowed",
        .name = "Firmware shadowing is allowed"
    },
    {
        .id   = 13,
        .code = "vesa-support",
        .name = "VL-VESA support"
    },
    {
        .id   = 14,
        .code = "escd-support",
        .name = "ESCD support"
    },
    {
        .id   = 15,
        .code = "boot-cd",
        .name = "Boot from CD"
    },
    {
        .id   = 16,
        .code = "boot-selectable",
        .name = "Selectable boot"
    },
    {
        .id   = 17,
        .code = "socketed-rom",
        .name = "Socketed ROM"
    },
    {
        .id   = 18,
        .code = "boot-pcmcia-support",
        .name = "Boot from PC card (PCMCIA)"
    },
    {
        .id   = 19,
        .code = "edd-support",
        .name = "EDD specification support"
    },
    {
        .id   = 20,
        .code = "floppy-nec-support",
        .name = "Int 13h japanese floppy for NEC 9800 1.2 MB support"
    },
    {
        .id   = 21,
        .code = "floppy-toshiba-support",
        .name = "Int 13h japanese floppy for Toshiba 1.2 MB support"
    },
    {
        .id   = 22,
        .code = "floppy-525-360k-support",
        .name = "Int 13h 5.25\"” / 360 KB floppy services support"
    },
    {
        .id   = 23,
        .code = "floppy-525-1m2-support",
        .name = "Int 13h 5.25\" / 1.2 MB floppy services support"
    },
    {
        .id   = 24,
        .code = "floppy-35-720k-support",
        .name = "Int 13h 3.5\" / 720 KB floppy services support"
    },
    {
        .id   = 25,
        .code = "floppy-35-2m88-support",
        .name = "Int 13h 3.5\" / 2.88 MB floppy services support"
    },
    {
        .id   = 26,
        .code = "print-screen-support",
        .name = "Int 5h print screen service support"
    },
    {
        .id   = 27,
        .code = "keyboard-support",
        .name = "Int 9h 8042 keyboard services support"
    },
    {
        .id   = 28,
        .code = "serial-support",
        .name = "Int 14h serial services support"
    },
    {
        .id   = 29,
        .code = "printer-support",
        .name = "Int 17h printer services support"
    },
    {
        .id   = 30,
        .code = "video-cga-mono-support",
        .name = "Int 10h CGA/Mono video services support"
    },
    {
        .id   = 31,
        .code = "nec-pc-98",
        .name = "NEC PC-98"
    },
    DMI_NAME_NULL
};

static const dmi_name_t dmi_firmware_feature_ex_names[] =
{
    {
        .id   = 0,
        .code = "acpi-support",
        .name = "ACPI support"
    },
    {
        .id   = 1,
        .code = "usb-legacy-support",
        .name = "USB legacy support"
    },
    {
        .id   = 2,
        .code = "agp-support",
        .name = "AGP support"
    },
    {
        .id   = 3,
        .code = "boot-i2o",
        .name = "I2O boot support"
    },
    {
        .id   = 4,
        .code = "boot-ls120",
        .name = "LS-120 SuperDisk boot support"
    },
    {
        .id   = 5,
        .code = "boot-atapi-zip",
        .name = "ATAPI ZIP drive boot support"
    },
    {
        .id   = 6,
        .code = "boot-ieee1394",
        .name = "IEEE1394 boot support"
    },
    {
        .id   = 7,
        .code = "smart-battery",
        .name = "Smart battery support"
    },
    {
        .id   = 8,
        .code = "bios-boot-spec",
        .name = "BIOS boot specification support"
    },
    {
        .id   = 9,
        .code = "boot-network-fn-key",
        .name = "Function key-initiated network boot support"
    },
    {
        .id   = 10,
        .code = "content-distribution",
        .name = "Targeted content distribution enabled"
    },
    {
        .id   = 11,
        .code = "uefi-spec",
        .name = "UEFI specification support"
    },
    {
        .id   = 12,
        .code = "virtual-machine",
        .name = "SMBIOS describes a virtual machine"
    },
    {
        .id   = 13,
        .code = "mfg-mode-support",
        .name = "Manufacturing mode support"
    },
    {
        .id = 14,
        .code = "mfg-mode-enabled",
        .name = "Manufacturing mode enabled"
    },
    DMI_NAME_NULL
};

static const dmi_attribute_t dmi_firmware_attrs[] =
{
    DMI_ATTRIBUTE(dmi_firmware_t, vendor, STRING, {
        .code   = "vendor",
        .name   = "Vendor"
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, version, STRING, {
        .code   = "version",
        .name   = "Version"
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, bios_segment, ADDRESS, {
        .code   = "bios-segment",
        .name   = "BIOS segment"
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, release_date, STRING, {
        .code   = "release-date",
        .name   = "Release date"
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, rom_size, SIZE, {
        .code   = "rom-size",
        .name   = "ROM size"
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, features, SET, {
        .code   = "features",
        .name   = "Features",
        .values = dmi_firmware_feature_names
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, features_ex, SET, {
        .code   = "features-ex",
        .name   = "Extra features",
        .values = dmi_firmware_feature_ex_names
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, platform_version, VERSION, {
        .code   = "platform-version",
        .name   = "Platform firmware version",
        .scale  = 2
    }),
    DMI_ATTRIBUTE(dmi_firmware_t, controller_version, VERSION, {
        .code   = "controller-version",
        .name   = "Embedded controller firmware version",
        .scale  = 2
    }),
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_firmware_table =
{
    .tag           = "firmware",
    .name          = "Platform firmware information",
    .type          = DMI_TYPE_FIRMWARE,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .unique        = true,
    .min_length    = 0x12,
    .attributes    = dmi_firmware_attrs,
    .handlers      = {
        .decode = (dmi_table_decode_fn_t)dmi_firmware_decode,
        .free   = (dmi_table_free_fn_t)dmi_firmware_free
    }
};

dmi_size_t dmi_firmware_rom_size(dmi_byte_t value)
{
    return ((dmi_size_t)value + 1) << 16;
}

dmi_size_t dmi_firmware_rom_size_ex(dmi_word_t value)
{
    dmi_size_t size = (dmi_size_t)(value & 0x3FFF);
    dmi_word_t scale = (value & 0xC000) >> 14;

    if (scale == 0)
        size <<= 20;
    else if (scale == 1)
        size <<= 30;
    else
        return 0;

    return size;
}

dmi_firmware_t *dmi_firmware_decode(const dmi_table_t *table)
{
    dmi_firmware_t *info = nullptr;
    dmi_firmware_data_t *data = dmi_cast(data, table->data);

    info = calloc(1, sizeof(*info));
    if (!info)
        return nullptr;

    dmi_firmware_features_t features = {
        ._value = dmi_decode_qword(data->features)
    };

    info->vendor       = dmi_table_string(table, data->vendor);
    info->version      = dmi_table_string(table, data->version);
    info->bios_segment = dmi_decode_word(data->bios_segment);
    info->release_date = dmi_table_string(table, data->release_date);
    info->rom_size     = dmi_firmware_rom_size(data->rom_size);
    info->features     = features;

    // SMBIOS 2.1: Extra feature bits
    unsigned extra = table->body_length - 0x12;
    dmi_firmware_features_ex_t features_ex = {
        ._value = {
            extra > 0 ? data->features_ex[0] : 0,
            extra > 1 ? data->features_ex[1] : 0
        }
    };
    info->features_ex = features_ex;

    // SMBIOS 2.4 features
    if (table->body_length >= 0x14) {
        if (data->platform_release_major != 0xFFU) {
            info->platform_version = dmi_version(data->platform_release_major,
                                                data->platform_release_minor, 0);
        } else {
            info->platform_version = DMI_VERSION_NONE;
        }

        if (data->controller_release_major != 0xFFU) {
            info->controller_version = dmi_version(data->controller_release_major,
                                                data->controller_release_minor, 0);
        } else {
            info->controller_version = DMI_VERSION_NONE;
        }
    }

    // SMBIOS 3.1 features
    if (table->body_length >= 0x18) {
        if (data->rom_size == 0xFFU)
            info->rom_size = dmi_firmware_rom_size_ex(dmi_decode_word(data->rom_size_ex));
    }

    return info;
}

void dmi_firmware_free(dmi_firmware_t *info)
{
    free(info);
}
