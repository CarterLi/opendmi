#!/bin/sh
#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025-2026, The OpenDMI contributors
#
# SPDX-License-Identifier: BSD-3-Clause
#
OSNAME=`uname -s`

LLVM_PROF=llvm-profdata
LLVM_COV=llvm-cov

if [ "${OSNAME}" == "Darwin" ]; then
    LLVM_PROF="xcrun ${LLVM_PROF}"
    LLVM_COV="xcrun ${LLVM_COV}"
fi

_missing_command() {
    echo "Missing command. Use -h or --help for help" 1>&2
    exit 1
}

_invalid_command() {
    echo "Invalid command: $1. Use -h or --help for help" 1>&2
    exit 1
}

_merge()
{
    ${LLVM_PROF} merge --sparse build/libopendmi/bin/*.profraw -o libopendmi.profdata 
}

_show()
{
    ${LLVM_COV} show ./build/libopendmi/lib/libopendmi.dylib -instr-profile=libopendmi.profdata
}

_report()
{
    ${LLVM_COV} report build/libopendmi/lib/libopendmi.dylib -instr-profile=libopendmi.profdata
}

if [ $# -eq 0 ]; then
    _missing_command
fi

COMMAND=$1
shift

case "${COMMAND}" in
    merge)
        _merge
        ;;
    show)
        _show
        ;;
    report)
        _report
        ;;
    *)
        _invalid_command ${COMMAND}
        ;;
esac
