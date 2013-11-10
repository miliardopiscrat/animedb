#!/bin/sh

cd ..


if [ ! -d "compiler" ]; then
mkdir compiler
wget --quiet http://download.xtreamer.net/Firmware/Prodigy/Toolchain_for_Xtreamer_Jukebox.zip
unzip Toolchain_for_Xtreamer_Jukebox.zip -d compiler/
tar -xjf compiler/msdk-4.3.6-mips-EL-2.6.34-0.9.30.3_hwfpu.tar.bz2 -C compiler/
rm -rf Toolchain_for_Xtreamer_Jukebox.zip
rm -rf compiler/*.bz2
fi
