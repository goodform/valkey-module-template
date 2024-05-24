#!/bin/bash

clean="false"

while [[ $# -gt 0 ]]
do
    key="$1"

    case $key in
        --clean)
        clean="true"
        shift
        ;;
        *)
        echo "Unknown option: $key"
        exit 1
        ;;
    esac
    shift
done

if [ -d "build" ]; then
    echo "Removing old build directory..."
    rm -rf build
fi

if [ "$clean" = "true" ]; then
    echo "Clean completed."
    exit 0
fi

git submodule update --init --recursive

echo "Creating new build directory..."
mkdir build
cd build

cmake ..
make -d -w

echo "Build completed."
exit 0