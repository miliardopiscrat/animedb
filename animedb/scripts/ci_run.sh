#!/bin/bash

export PATH=`pwd`/../compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin:$PATH

#cd animedb

make TARGET=linux testlib -j4

./binary/test

make TARGET=linux clean
make TARGET=mipsel all -j4
make TARGET=mipsel tarball

