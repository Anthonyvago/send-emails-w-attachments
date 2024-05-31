#!/bin/bash

# Go to the root directory
SCRIPT_DIR=$( dirname -- "$( readlink -f -- "$0"; )"; )
BUILD_DIR="$SCRIPT_DIR/../build"

clear

# List of directories to exclude
EXCLUDE_DIRS=("smtpclientlibrary-build" "smtpclientlibrary-download" "smtpclientlibrary-src" "_deps")

# Remove all files and subdirectories except for excluded directories
for dir in "${EXCLUDE_DIRS[@]}"; do
    # Exclude the specified directories
    if [[ -d "$BUILD_DIR/$dir" ]]; then
        echo "Skipping removal of $dir"
    fi
done

# Remove all other files and subdirectories inside the build directory
find "$BUILD_DIR" -mindepth 1 -maxdepth 1 -type d -not \( -name "${EXCLUDE_DIRS[0]}" -o -name "${EXCLUDE_DIRS[1]}" -o -name "${EXCLUDE_DIRS[2]}" -o -name "${EXCLUDE_DIRS[3]}" \) -exec rm -rf {} \;
find "$BUILD_DIR" -mindepth 1 -maxdepth 1 -type f -exec rm -f {} \;

echo "Build directory cleaned (excluding specified directories)."
