#!/bin/bash

set -o pipefail

export PATH=`pwd`/../compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin:$PATH

ls $(pwd)/../compiler

cd animedb

make TARGET=linux testlib -j4

./binary/test

make TARGET=linux clean
make TARGET=mipsel all -j4
make TARGET=mipsel tarball


/animedb/scripts/toolchain.sh

./animedb/scripts/ci_run.sh

cd animedb
mv animedb.tar.gz animedb-`echo $DRONE_BUILD_NUMBER`.tar.gz
