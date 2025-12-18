#!/bin/bash
#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>
#
# SPDX-License-Identifier: BSD-3-Clause
#
SCRIPT=`basename $0`
OSNAME=`uname -s`
BUILD_DIR=build
BUILD_TYPE=Release

ENABLE_CXX=OFF
ENABLE_GOLANG=OFF
ENABLE_PYTHON=OFF
ENABLE_RUST=OFF
ENABLE_DBUS=OFF

case "${OSNAME}" in
    Linux)
        NPROC=`nproc --all`
        ;;
    FreeBSD|Darwin)
        NPROC=`sysctl -n hw.ncpu`
        ;;
    *)
        NPROC=1
esac

_missing_command() {
    echo "Missing command. Use -h or --help for help" 1>&2
    exit 1
}

_invalid_command() {
    echo "Invalid command: $1. Use -h or --help for help" 1>&2
    exit 1
}

_invalid_option() {
    echo "Invalid option: $1. Use -h or --help for help" 1>&2
    exit 1
}

_require_argument() {
    if [ $2 -eq 0 ]; then
        echo "Option requires an argument: $1" 1>&2
        exit 1
    fi
}

_usage() {
    echo "OpenDMI: Cross-platform DMI/SMBIOS framework"
    echo "Copyright (c) 2025, Dmitry Sednev <dmitry@sednev.ru>"
    echo
    echo "Usage:"
    echo "    ${SCRIPT} [global options] <command> [command options]"
    echo
    echo "Global options:"
    echo "    -h, --help         Print this help and exit"
    echo "    -b, --build <DIR>  Set build directory"
    echo "    -j, --jobs <N>     Set number of parallel jobs"
    echo
    echo "Commands:"
    echo "   configure  Configure build settings"
    echo "   build      Build the entire project"
    echo "   test       Perform unit tests"
    echo "   clean      Delete all files that are created by building the program"
    echo "   distclean  Delete all files that are created by configuring or building the program"
    echo
    echo "Configure options:"
    echo "   --release        Use release build configuration (default)"
    echo "   --debug          Use debug build configuration"
    echo "   --enable-cxx     Enable C++ support (libopendmi++)"
    echo "   --enable-golang  Enable Go support (libopendmi-go)"
    echo "   --enable-python  Enable Python support (libopendmi-python)"
    echo "   --enable-rust    Enable Rust support (libopendmi-rust)"
    echo "   --enable-dbus    Enable D-bus support (opendmi-dbus)"
    echo
    echo "Defaults:"
    echo "    Build directory: ${BUILD_DIR}"
    echo "    Build type:      ${BUILD_TYPE}"
    echo "    Number of jobs:  ${NPROC}"
}

_configure() {
    while [ $# -gt 0 ]; do
        OPTION=$1
        shift

        case "$OPTION" in
            --debug)
                BUILD_TYPE=Debug
                ;;
            --release)
                BUILD_TYPE=Release
                ;;
            --enable-cxx)
                ENABLE_CXX=ON
                ;;
            --enable-golang)
                ENABLE_GOLANG=ON
                ;;
            --enable-python)
                ENABLE_PYTHON=ON
                ;;
            --enable-rust)
                ENABLE_RUST=ON
                ;;
            --enable-dbus)
                ENABLE_DBUS=ON
                ;;
            *)
                _invalid_option ${OPTION}
                ;;
        esac
    done

    cmake -B ${BUILD_DIR} \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DOPENDMI_CXX=${ENABLE_CXX} \
        -DOPENDMI_GOLANG=${ENABLE_GOLANG} \
        -DOPENDMI_PYTHON=${ENABLE_PYTHON} \
        -DOPENDMI_RUST=${ENABLE_RUST} \
        -DOPENDMI_DBUS=${ENABLE_DBUS}
}

_build() {
    cmake --build ${BUILD_DIR} --parallel ${NPROC}
}

_test() {
    CTEST_ARGS=""

    while [ $# -gt 0 ]; do
        OPTION=$1
        shift

        case "$OPTION" in
            --failed)
                CTEST_ARGS="${CTEST_ARGS} --rerun-failed"
                ;;
            *)
                _invalid_option ${OPTION}
                ;;
        esac
    done

    ctest --test-dir ${BUILD_DIR} --parallel ${NPROC} ${CTEST_ARGS}
}

_clean() {
    cmake --build ${BUILD_DIR} --target clean
}

_distclean()
{
    rm -rf ${BUILD_DIR}
}

while [ $# -gt 0 ]; do
    OPTION=$1

    STARTCH=`echo ${OPTION} | cut -c1-1`
    if [ "${STARTCH}" != "-" ]; then
        break
    fi
    shift

    case "${OPTION}" in
        -h|--help)
            _usage
            exit 0
            ;;
        -b|--build)
            _require_argument ${OPTION} $#
            BUILD_DIR=$1
            shift
            ;;
        -j|--jobs)
            _require_argument ${OPTION} $#
            NPROC=$1
            shift
            ;;
        *)
            _invalid_option ${OPTION}
            ;;
    esac
done

if [ $# -eq 0 ]; then
    _missing_command
fi

COMMAND=$1
shift

case "${COMMAND}" in
    configure)
        _configure "$@"
        ;;
    build)
        _build "$@"
        ;;
    test)
        _test "$@"
        ;;
    clean)
        _clean "$@"
        ;;
    distclean)
        _distclean "$@"
        ;;
    *)
        _invalid_command ${COMMAND}
        ;;
esac
