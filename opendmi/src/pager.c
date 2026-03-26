//
// OpenDMI: Cross-platform DMI/SMBIOS framework
// Copyright (c) 2025-2026, The OpenDMI contributors
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include "config.h"

#ifndef _WIN32
#include <spawn.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <wordexp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <opendmi/context.h>
#include <opendmi/pager.h>
#include <opendmi/utils/file.h>

static pid_t pid = -1;
void wait_pager_exit(void)
{
    fclose(stdout); // Ensure the pager process receives EOF
    if (pid > 0) {
        waitpid(pid, NULL, 0);
        pid = -1;
    }
}

bool dmi_pager_start(dmi_context_t *context)
{
    bool success = false;
    wordexp_t we = {};
    int rv;
    int fds[2];

    const char *pager = getenv("PAGER");
    if (pager == nullptr)
        return true;

    rv = wordexp(pager, &we, WRDE_NOCMD);
    if (rv != 0) {
        switch (rv) {
        case WRDE_BADCHAR:
        case WRDE_BADVAL:
        case WRDE_SYNTAX:
            dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Invalid $PAGER value: '%s'", pager);
            break;

        case WRDE_CMDSUB:
            dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Command substitution is not allowed in $PAGER");
            break;

        case WRDE_NOSPACE:
            dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
            break;
        }

        return false;
    }

    if (we.we_wordc == 0) {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Empty $PAGER value");
        wordfree(&we);
        return false;
    }

    do {
        if (pipe(fds) < 0) {
            dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Unable to create pipe: %s", strerror(errno));
            break;
        }

        posix_spawn_file_actions_t actions;
        if (posix_spawn_file_actions_init(&actions) != 0) {
            dmi_error_raise(context, DMI_ERROR_OUT_OF_MEMORY);
            dmi_file_close(fds[STDIN_FILENO]);
            dmi_file_close(fds[STDOUT_FILENO]);
            break;
        }

        int fa_rv = 0;
        fa_rv = posix_spawn_file_actions_adddup2(&actions, fds[STDIN_FILENO], STDIN_FILENO);
        if (fa_rv == 0) fa_rv = posix_spawn_file_actions_addclose(&actions, fds[STDIN_FILENO]);
        if (fa_rv == 0) fa_rv = posix_spawn_file_actions_addclose(&actions, fds[STDOUT_FILENO]);

        if (fa_rv != 0) {
            dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Failed to configure pager stdio: %s", strerror(fa_rv));
            posix_spawn_file_actions_destroy(&actions);
            dmi_file_close(fds[STDIN_FILENO]);
            dmi_file_close(fds[STDOUT_FILENO]);
            break;
        }

        int spawn_rv = posix_spawnp(&pid, we.we_wordv[0], &actions, NULL, we.we_wordv, environ);
        posix_spawn_file_actions_destroy(&actions);

        if (spawn_rv != 0) {
            if (spawn_rv == ENOENT) {
                dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Pager executable not found: '%s'", we.we_wordv[0]);
            } else {
                dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Unable to exec pager: %s", strerror(spawn_rv));
            }
            dmi_file_close(fds[STDIN_FILENO]);
            dmi_file_close(fds[STDOUT_FILENO]);
            break;
        }

        dmi_file_close(STDOUT_FILENO);

        if (dup2(fds[STDOUT_FILENO], STDOUT_FILENO) < 0) {
            dmi_error_raise_ex(context, DMI_ERROR_FILE_DUP, "%s", strerror(errno));
            dmi_file_close(fds[STDIN_FILENO]);
            dmi_file_close(fds[STDOUT_FILENO]);
            kill(pid, SIGKILL);
            break;
        }

        dmi_file_close(fds[STDIN_FILENO]);
        dmi_file_close(fds[STDOUT_FILENO]);

        atexit(wait_pager_exit);

        success = true;
    } while (false);

    wordfree(&we);

    return success;
}

#else // _WIN32

#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <windows.h>

#include <opendmi/context.h>
#include <opendmi/utils.h>

static const char* win32err_to_string(DWORD error_code)
{
    static char buffer[256];

    DWORD len = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error_code,
        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
        buffer,
        sizeof(buffer),
        NULL);

    if (len == 0) {
        snprintf(buffer, sizeof(buffer), "Unknown error code (%lu)", error_code);
    } else {
        // Remove trailing newline
        if (buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        if (buffer[len - 2] == '\r') buffer[len - 2] = '\0';
        snprintf(buffer + len - 2, sizeof(buffer) - len + 2, " (%lu)", error_code);
    }

    return buffer;
}

static HANDLE child_process_handle = NULL;
void wait_pager_exit(void)
{
    fclose(stdout); // Ensure the pager process receives EOF
    if (child_process_handle) {
        WaitForSingleObject(child_process_handle, INFINITE);
        CloseHandle(child_process_handle);
        child_process_handle = NULL;
    }
}

bool dmi_pager_start(dmi_context_t *context)
{
    DWORD pagerLen = GetEnvironmentVariableW(L"PAGER", NULL, 0);
    if (pagerLen == 0)
        return true;

    wchar_t *pager = dmi_alloc(context, pagerLen * sizeof(wchar_t));
    if (!pager) {
        return false;
    }
    GetEnvironmentVariableW(L"PAGER", pager, pagerLen);

    wchar_t pipeName[64];
    static unsigned pidCounter = 0;
    swprintf(pipeName, sizeof(pipeName) / sizeof(*pipeName), L"\\\\.\\pipe\\OPENDMI-%u-%u", GetCurrentProcessId(), ++pidCounter);

    HANDLE hChildPipeWrite = CreateNamedPipeW(
        pipeName,
        PIPE_ACCESS_OUTBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE,
        0,
        1,
        8192,
        8192,
        0,
        NULL
    );
    if (hChildPipeWrite == INVALID_HANDLE_VALUE)
    {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "CreateNamedPipeW failed: %s", win32err_to_string(GetLastError()));
        dmi_free(pager);
        return false;
    }

    HANDLE hChildPipeRead = CreateFileW(
        pipeName,
        GENERIC_READ,
        0,
        &(SECURITY_ATTRIBUTES){
            .nLength = sizeof(SECURITY_ATTRIBUTES),
            .lpSecurityDescriptor = NULL,
            .bInheritHandle = TRUE,
        },
        OPEN_EXISTING,
        0,
        NULL
    );
    if (hChildPipeRead == INVALID_HANDLE_VALUE)
    {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "CreateFileW failed: %s", win32err_to_string(GetLastError()));
        CloseHandle(hChildPipeWrite);
        dmi_free(pager);
        return false;
    }

    PROCESS_INFORMATION piProcInfo = {};
    STARTUPINFOW siStartInfo = {
        .cb = sizeof(siStartInfo),
        .dwFlags = STARTF_USESTDHANDLES,
        .hStdInput = hChildPipeRead,
        .hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE),
        .hStdError = GetStdHandle(STD_ERROR_HANDLE),
    };

    BOOL success = CreateProcessW(
        NULL,
        pager,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &siStartInfo,
        &piProcInfo
    );

    if (!success)
    {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "CreateProcessW failed: %s", win32err_to_string(GetLastError()));
        CloseHandle(hChildPipeWrite);
        CloseHandle(hChildPipeRead);
        dmi_free(pager);
        return false;
    }

    CloseHandle(piProcInfo.hThread);
    CloseHandle(hChildPipeRead);
    dmi_free(pager);

    int newStdout = _open_osfhandle((intptr_t)hChildPipeWrite, 0);
    if (newStdout < 0) {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Unable to open pipe handle: %s", strerror(errno));
        CloseHandle(hChildPipeWrite);
        return false;
    }
    _close(STDOUT_FILENO);
    if (_dup2(newStdout, STDOUT_FILENO) < 0) {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "Unable to dup pipe handle: %s", strerror(errno));
        _close(newStdout);
        CloseHandle(hChildPipeWrite);
        return false;
    }
    _close(newStdout);
    if (!SetStdHandle(STD_OUTPUT_HANDLE, hChildPipeWrite))
    {
        dmi_error_raise_ex(context, DMI_ERROR_SYSTEM, "SetStdHandle failed: %s", win32err_to_string(GetLastError()));
        CloseHandle(hChildPipeWrite);
        return false;
    }

    child_process_handle = piProcInfo.hProcess;
    atexit(wait_pager_exit);

    return true;
}

#endif // _WIN32
