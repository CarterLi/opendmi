#include <opendmi/cache.h>
#include <opendmi/utils.h>

static const char *dmi_cache_types[] =
{
    [DMI_CACHE_TYPE_OTHER]       = "Other",
    [DMI_CACHE_TYPE_UNKNOWN]     = "Unknown",
    [DMI_CACHE_TYPE_INSTRUCTION] = "Instruction",
    [DMI_CACHE_TYPE_DATA]        = "Data",
    [DMI_CACHE_TYPE_UNIFIED]     = "Unified"
};

static const char *dmi_cache_modes[] =
{
    [DMI_CACHE_MODE_WRITE_THROUGH] = "Write-through",
    [DMI_CACHE_MODE_WRITE_BACK]    = "Write-back",
    [DMI_CACHE_MODE_VARIABLE]      = "Variable",
    [DMI_CACHE_MODE_UNKNOWN]       = "Unknown"
};

size_t dmi_cache_size(uint16_t value)
{
    size_t size = value & 0x7FFF;

    if (value & 0x8000)
        size <<= 16; // Granularity is 64 Kb
    else
        size <<= 10; // Granularity is 1 Kb

    return size;
}
