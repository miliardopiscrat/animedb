#!/bin/sh

current_folder=$(pwd)

cd ..

export PATH=`pwd`/compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin:$PATH

cd $current_folder/animedb

make TARGET=linux clean testlib

./binary/test

make TARGET=linux clean
make TARGET=mipsel clean all
make TARGET=mipsel tarball
