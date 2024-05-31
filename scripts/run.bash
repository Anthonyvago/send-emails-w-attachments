#!/bin/bash

# Retrieve the directory of this script:
SCRIPT_DIR=$( dirname -- "$( readlink -f -- "$0"; )"; )

# Variables
BUILD_DIR="${SCRIPT_DIR}/../build"
APP_NAME="automated_mail_sender"

# Check if the build directory and the executable BOTH do not exist:
if [[ ! -d "$BUILD_DIR" ]] || [[ ! -f "$BUILD_DIR/$APP_NAME" ]]; then
    echo -e "\033[0;31mEither the build directory or the executable inside this directory does not exist..."
    echo -e "Please run \"build.bash\" first.\033[0m"
    exit 1
fi

cd $BUILD_DIR


# if an argument is given, run the program with the given argument
if [ $# -eq 0 ]; then
    ./$APP_NAME
else
    ./$APP_NAME ${SCRIPT_DIR}/$@
fi