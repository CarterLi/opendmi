#include <opendmi/utils/win32.h>

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <winternl.h>

const char *dmi_win32err_to_string(DWORD error_code)
{
    static char buffer[256];

    DWORD len = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_code,
        0,
        buffer,
        sizeof(buffer),
        NULL);

    if (len == 0) {
        snprintf(buffer, sizeof(buffer), "Unknown error code (%lu)", error_code);
    } else {
        // Remove trailing newline
        while (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n')) {
            buffer[--len] = '\0';
        }
        snprintf(buffer + len, sizeof(buffer) - len, " (%lu)", error_code);
    }

    return buffer;
}

const char *dmi_ntstatus_to_string(NTSTATUS status)
{
    return dmi_win32err_to_string(RtlNtStatusToDosError(status));
}
