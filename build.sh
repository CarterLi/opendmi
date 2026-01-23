#!/bin/sh
#
# OpenDMI: Cross-platform DMI/SMBIOS framework
# Copyright (c) 2025-2026, The OpenDMI contributors
#
# SPDX-License-Identifier: BSD-3-Clause
#
SCRIPT_PATH=`readlink -f "$0"`
SCRIPT_ROOT=`dirname "$0"`
SCRIPT_NAME=`basename "$0"`

CONFIG_DIST="${SCRIPT_ROOT}/build.conf.dist"
CONFIG_LOCAL="${SCRIPT_ROOT}/build.conf"

. ${CONFIG_DIST}

if [ -f "${CONFIG_LOCAL}" ]; then
    . ${CONFIG_LOCAL}
fi

case "${BUILD_DIR}" in
    /*)
        ;;
    *)
        BUILD_DIR="${SCRIPT_ROOT}/${BUILD_DIR}"
        ;;
esac
BUILD_DIR=`readlink -f "${BUILD_DIR}"`

OSNAME=`uname -s`
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

CMAKE=`which cmake`
if [ "$?" -ne "0" ]; then
    echo "CMake not found" 1>&2
    exit 1
fi

CTEST=`which ctest`
if [ "$?" -ne "0" ]; then
    echo "CTest not found" 1>&2
    exit 1
fi

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
    echo "Copyright (c) 2025-2026, The OpenDMI contributors"
    echo
    echo "Usage:"
    echo "    ${SCRIPT_NAME} [global options] <command> [command options]"
    echo
    echo "Global options:"
    echo "    -h, --help         Print this help and exit"
    echo "    -b, --build <DIR>  Set build directory"
    echo "    -j, --jobs <N>     Set number of parallel jobs"
    echo
    echo "Commands:"
    echo "    configure  Configure build settings"
    echo "    build      Build the entire project"
    echo "    test       Perform unit tests"
    echo "    clean      Delete all files that are created by building the program"
    echo "    distclean  Delete all files that are created by configuring or building the program"
    echo
    echo "Configure options:"
    echo "    General:"
    echo "        --prefix <PATH>  Set installation prefix (default=${PREFIX})"
    echo "        --release        Release build"
    echo "        --debug          Debug build"
    echo "    Components:"
    echo "        --enable-all     Build all components"
    echo "        --enable-golang  Build with Go support (libopendmi-go, default=${ENABLE_GOLANG})"
    echo "        --enable-python  Build with Python support (libopendmi-python, default=${ENABLE_PYTHON})"
    echo "        --enable-rust    Build with Rust support (libopendmi-rust, default=${ENABLE_RUST})"
    echo "        --enable-dbus    Build with D-bus support (opendmi-dbus, default=${ENABLE_DBUS})"
    echo "    Features:"
    echo "        --with-icu       Build with ICU4C support (default=${ENABLE_ICU})"
    echo "        --with-curses    Build with Curses support (default=${ENABLE_CURSES})"
    echo "        --with-json      Build with JSON support (default=${ENABLE_JSON})"
    echo "        --with-xml       Build with XML support (default=${ENABLE_XML})"
    echo "        --with-yaml      Build with YAML support (default=${ENABLE_YAML})"
    echo "    Miscellaneous:"
    echo "        --verbose        Generate verbose Makefiles"
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
            --prefix)
                _require_argument $OPTION $#
                PREFIX="$1"
                shift
                ;;
            --debug)
                BUILD_TYPE=Debug
                ;;
            --release)
                BUILD_TYPE=Release
                ;;
            --enable-all)
                ENABLE_GOLANG=ON
                ENABLE_PYTHON=ON
                ENABLE_RUST=ON
                ENABLE_DBUS=ON
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
            --with-icu)
                ENABLE_ICU=ON
                ;;
            --with-curses)
                ENABLE_CURSES=ON
                ;;
            --with-json)
                ENABLE_JSON=ON
                ;;
            --with-xml)
                ENABLE_XML=ON
                ;;
            --with-yaml)
                ENABLE_YAML=ON
                ;;
            --verbose)
                VERBOSE=ON
                ;;
            *)
                _invalid_option ${OPTION}
                ;;
        esac
    done

    FEATURES=""
    if [ "${ENABLE_ICU}" != "AUTO" ]; then
        FEATURES="${FEATURES} -DENABLE_ICU=${ENABLE_ICU}"
    fi
    if [ "${ENABLE_CURSES}" != "AUTO" ]; then
        FEATURES="${FEATURES} -DENABLE_CURSES=${ENABLE_CURSES}"
    fi
    if [ "${ENABLE_XML}" != "AUTO" ]; then
        FEATURES="${FEATURES} -DENABLE_XML=${ENABLE_XML}"
    fi
    if [ "${ENABLE_YAML}" != "AUTO" ]; then
        FEATURES="${FEATURES} -DENABLE_YAML=${ENABLE_YAML}"
    fi
    if [ "${VERBOSE}" == "ON" ]; then
        FEATURES="${FEATURES} -DCMAKE_VERBOSE_MAKEFILE=TRUE"
    fi

    echo
    echo "Target:          ${OSNAME}"
    echo "Using CMake:     ${CMAKE}"
    echo "Using CTest:     ${CTEST}"
    echo "Build directory: ${BUILD_DIR}"
    echo "Build type:      ${BUILD_TYPE}"
    echo "Number of jobs:  ${NPROC}"
    echo

    ${CMAKE} -B ${BUILD_DIR} \
        -DCMAKE_INSTALL_PREFIX=${PREFIX} \
        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
        -DENABLE_GOLANG=${ENABLE_GOLANG} \
        -DENABLE_PYTHON=${ENABLE_PYTHON} \
        -DENABLE_RUST=${ENABLE_RUST} \
        -DENABLE_DBUS=${ENABLE_DBUS} \
        ${FEATURES}
}

_build() {
    ${CMAKE} --build ${BUILD_DIR} --parallel ${NPROC}
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

    ${CTEST} --test-dir ${BUILD_DIR} --parallel ${NPROC} ${CTEST_ARGS}
}

_install() {
    ${CMAKE} --build ${BUILD_DIR} --target install
}

_clean() {
    ${CMAKE} --build ${BUILD_DIR} --target clean
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
    install)
        _install "$@"
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
