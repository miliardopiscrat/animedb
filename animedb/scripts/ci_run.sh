#!/bin/bash

export PATH=/root/animedb/animedb/compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu/bin:$PATH

cd ..

echo `ls /root/animedb/animedb`

./make TARGET=linux testlib -j4

#./make TARGET=mipsel all -j4
#./make TARGET=mipsel tarball

