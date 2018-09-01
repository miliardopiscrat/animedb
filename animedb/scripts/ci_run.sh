#!/bin/bash

export PATH=`pwd`/../compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin:$PATH

cd ..

echo `ls /home/circleci/animedb/animedb/scripts/../compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin/`

./make TARGET=linux testlib -j4

./make TARGET=mipsel all -j4
./make TARGET=mipsel tarball

