//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <opendmi/table/processor.h>
#include <opendmi/name.h>

static const dmi_name_set_t dmi_processor_type_names =
{
    .code  = "processor-types",
    .names = {
        DMI_NAME_UNSPEC(DMI_PROCESSOR_TYPE_UNSPEC),
        DMI_NAME_OTHER(DMI_PROCESSOR_TYPE_OTHER),
        DMI_NAME_UNKNOWN(DMI_PROCESSOR_TYPE_UNKNOWN),
        {
            .id   = DMI_PROCESSOR_TYPE_CENTRAL,
            .code = "central",
            .name = "Central processor"
        },
        {
            .id   = DMI_PROCESSOR_TYPE_MATH,
            .code = "math",
            .name = "Math processor"
        },
        {
            .id   = DMI_PROCESSOR_TYPE_DSP,
            .code = "dsp",
            .name = "DSP processor"
        },
        {
            .id   = DMI_PROCESSOR_TYPE_VIDEO,
            .code = "video",
            .name = "Video processor"
        },
        DMI_NAME_NULL
    }
};

static const dmi_name_set_t dmi_processor_upgrade_names =
{
    .code  = "processor-upgrades",
    .names = {
        DMI_NAME_UNSPEC(DMI_PROCESSOR_UPGRADE_UNSPEC),
        DMI_NAME_OTHER(DMI_PROCESSOR_UPGRADE_OTHER),
        DMI_NAME_UNKNOWN(DMI_PROCESSOR_UPGRADE_UNKNOWN),
        {
            .id   = DMI_PROCESSOR_UPGRADE_DAUGHTER_BOARD,
            .code = "daughter-board",
            .name = "Daughter board"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_ZIF,
            .code = "socket-zif",
            .name = "ZIF socket"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_PIGGY_BACK,
            .code = "piggy-back",
            .name = "Replaceable piggy-back"
        },
        DMI_NAME_NONE(DMI_PROCESSOR_UPGRADE_NONE),
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LIF,
            .code = "socket-lif",
            .name = "LIF socket"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SLOT_1,
            .code = "slot-1",
            .name = "Slot 1"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SLOT_2,
            .code = "slot-2",
            .name = "Slot 2"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_370PIN,
            .code = "socket-370pin",
            .name = "370-pin socket"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SLOT_A,
            .code = "slot-a",
            .name = "Slot A"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SLOT_M,
            .code = "slot-m",
            .name = "Slot M"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_423,
            .code = "socket-423",
            .name = "Socket 423"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_A,
            .code = "socket-a",
            .name = "Socket A (462)"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_478,
            .code = "socket-478",
            .name = "Socket 478"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_754,
            .code = "socket-754",
            .name = "Socket 754"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_940,
            .code = "socket-940",
            .name = "Socket 940"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_939,
            .code = "socket-939",
            .name = "Socket 939"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_MPGA604,
            .code = "socket-mpga604",
            .name = "Socket mPGA604"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA771,
            .code = "socket-lga771",
            .name = "Socket LGA771"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA775,
            .code = "socket-lga775",
            .name = "Socket LGA775"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_S1,
            .code = "socket-s1",
            .name = "Socket S1"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_AM2,
            .code = "socket-am2",
            .name = "Socket AM2"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_F,
            .code = "socket-f",
            .name = "Socket F (1207)"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1366,
            .code = "socket-lga1366",
            .name = "Socket LGA1366"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_G34,
            .code = "socket-g34",
            .name = "Socket G34"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_AM3,
            .code = "socket-am3",
            .name = "Socket AM3"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_C32,
            .code = "socket-c32",
            .name = "Socket C32"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1156,
            .code = "socket-lga1156",
            .name = "Socket LGA1156"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1567,
            .code = "socket-lga1567",
            .name = "Socket LGA1567"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_PGA988A,
            .code = "socket-pga988a",
            .name = "Socket PGA988A"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1288,
            .code = "socket-bga1288",
            .name = "Socket BGA1288"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_RPGA988B,
            .code = "socket-rpga988b",
            .name = "Socket rPGA988B"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1023,
            .code = "socket-bga1023",
            .name = "Socket BGA1023"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1224,
            .code = "socket-bga1224",
            .name = "Socket BGA1224"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1155,
            .code = "socket-lga1155",
            .name = "Socket LGA1155"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1356,
            .code = "socket-lga1356",
            .name = "Socket LGA1356"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA2011,
            .code = "socket-lga2011",
            .name = "Socket LGA2011"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_FS1,
            .code = "socket-fs1",
            .name = "Socket FS1"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_FS2,
            .code = "socket-fs2",
            .name = "Socket FS2"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_FM1,
            .code = "socket-fm1",
            .name = "Socket FM1"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_FM2,
            .code = "socket-fm2",
            .name = "Socket FM2"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA2011_3,
            .code = "socket-lga2011-3",
            .name = "Socket LGA2011-3"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1356_3,
            .code = "socket-lga1356-3",
            .name = "Socket LGA1356-3"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1150,
            .code = "socket-lga1150",
            .name = "Socket LGA1150"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1168,
            .code = "socket-bga1168",
            .name = "Socket BGA1168"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1234,
            .code = "socket-bga1234",
            .name = "Socket BGA1234"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1364,
            .code = "socket-bga1364",
            .name = "Socket BGA1364"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_AM4,
            .code = "socket-am4",
            .name = "Socket AM4"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1151,
            .code = "socket-lga1151",
            .name = "Socket LGA1151"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1356,
            .code = "socket-bga1356",
            .name = "Socket BGA1356"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1440,
            .code = "socket-bga1440",
            .name = "Socket BGA1440"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1515,
            .code = "socket-bga1515",
            .name = "Socket BGA1515"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA3647_1,
            .code = "socket-lga3647-1",
            .name = "Socket LGA3647-1"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_SP3,
            .code = "socket-sp3",
            .name = "Socket SP3"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_SP3R2,
            .code = "socket-sp3r2",
            .name = "Socket SP3r2"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA2066,
            .code = "socket-lga2066",
            .name = "Socket LGA2066"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1392,
            .code = "socket-bga1392",
            .name = "Socket BGA1392"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1510,
            .code = "socket-bga1510",
            .name = "Socket BGA1510"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1528,
            .code = "socket-bga1528",
            .name = "Socket BGA1528"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA4189,
            .code = "socket-lga4189",
            .name = "Socket LGA4189"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1200,
            .code = "socket-lga1200",
            .name = "Socket LGA1200"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA4677,
            .code = "socket-lga4677",
            .name = "Socket LGA4677"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1700,
            .code = "socket-lga1700",
            .name = "Socket LGA1700"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1744,
            .code = "socket-bga1744",
            .name = "Socket BGA1744"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1781,
            .code = "socket-bga1781",
            .name = "Socket BGA1781"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1211,
            .code = "socket-bga1211",
            .name = "Socket BGA1211"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA2422,
            .code = "socket-bga2422",
            .name = "Socket BGA2422"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1211,
            .code = "socket-lga1211",
            .name = "Socket LGA1211"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA2422,
            .code = "socket-lga2422",
            .name = "Socket LGA2422"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA5773,
            .code = "socket-lga5773",
            .name = "Socket LGA5773"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA5773,
            .code = "sockt-bga5773",
            .name = "Socket BGA5773"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_AM5,
            .code = "socket-am5",
            .name = "Socket AM5"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_SP5,
            .code = "socket-sp5",
            .name = "Socket SP5"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_SP6,
            .code = "socket-sp6",
            .name = "Socket SP6"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA883,
            .code = "socket-bga883",
            .name = "Socket BGA883"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1190,
            .code = "socket-bga1190",
            .name = "Socket BGA1190"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA4129,
            .code = "socket-bga4129",
            .name = "Socket BGA4129"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA4710,
            .code = "socket-lga4710",
            .name = "Socket LGA4710"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA7529,
            .code = "socket-lga7529",
            .name = "Socket LGA7529"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1964,
            .code = "socket-bga1964",
            .name = "Socket BGA1964"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA1792,
            .code = "socket-bga1792",
            .name = "Socket BGA1792"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA2049,
            .code = "socket-bga2049",
            .name = "Socket BGA2049"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA2551,
            .code = "socket-bga2551",
            .name = "Socket BGA2551"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_LGA1851,
            .code = "socket-lga1851",
            .name = "Socket LGA1851"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA2114,
            .code = "socket-bga2114",
            .name = "Socket BGA2114"
        },
        {
            .id   = DMI_PROCESSOR_UPGRADE_SOCKET_BGA2833,
            .code = "socket-bga2833",
            .name = "Socket BGA2833"
        },
        DMI_NAME_NULL
    }
};

const dmi_attribute_t dmi_processor_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_processor_table =
{
    .code          = "processor",
    .name          = "Processor information",
    .type          = DMI_TYPE_PROCESSOR,
    .required_from = DMI_VERSION(2, 3, 0),
    .required_till = DMI_VERSION_NONE,
    .min_length    = 0x1A,
    .attributes    = dmi_processor_attrs
};

const dmi_attribute_t dmi_processor_ex_attrs[] =
{
    DMI_ATTRIBUTE_NULL
};

const dmi_table_spec_t dmi_processor_ex_table =
{
    .code       = "processor-ex",
    .name       = "Processor additional information",
    .type       = DMI_TYPE_PROCESSOR_EX,
    .min_length = 0x06,
    .attributes = dmi_processor_ex_attrs
};

const char *dmi_processor_type_name(enum dmi_processor_type value)
{
    return dmi_name_lookup(&dmi_processor_type_names, value);
}

const char *dmi_processor_upgrade_name(enum dmi_processor_upgrade value)
{
    return dmi_name_lookup(&dmi_processor_upgrade_names, value);
}
