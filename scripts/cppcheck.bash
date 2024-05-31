#!/bin/bash

# Go to the root directory
SCRIPT_DIR=$( dirname -- "$( readlink -f -- "$0"; )"; )
BUILD_DIR="$SCRIPT_DIR/../build"

cd $BUILD_DIR

# Run cppcheck
make cppcheck