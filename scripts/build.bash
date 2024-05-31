#!/bin/bash

# First, go to the root directory:
SCRIPT_DIR=$( dirname -- "$( readlink -f -- "$0"; )"; )
cd ${SCRIPT_DIR}/../

# set variable 'NR_CORES' to the number of cores - 1:
NR_CORES=$(($(nproc)-1))

# if NR_CORES is 0, set it to 1:
if [ $NR_CORES -eq 0 ]; then
    NR_CORES=1
fi

mkdir build -p
cd build
cmake ..
make -j$NR_CORES