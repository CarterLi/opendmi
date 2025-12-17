#!/bin/bash

BUILD_DIR=build
BUILD_TYPE=Debug

ENABLE_CXX=OFF
ENABLE_GOLANG=OFF
ENABLE_PYTHON=OFF
ENABLE_RUST=OFF
ENABLE_DBUS=OFF

configure() {
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
                echo "Invalid option: ${OPTION}" 1>&2
                exit 1
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

if [ $# -eq 0 ]; then
    echo "Missing command" 1>&2
    exit 1
fi

COMMAND=$1
shift

case "$COMMAND" in
    configure)
        configure "$@"
        ;;
    build)
        cmake --build ${BUILD_DIR}
        ;;
    test)
        ctest --test-dir ${BUILD_DIR}
        ;;
    clean)
        cmake --build ${BUILD_DIR} --target clean
        ;;
    distclean)
        rm -rf ${BUILD_DIR}
        ;;
    *)
        echo "Invalid command: $COMMAND" 1>&2
        exit 1
esac
