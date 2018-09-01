#!/bin/bash
cd ..
rm -rf compiler

if [ ! -d "compiler" ]; then
tar -xvzf gdrive.tar.gz
./gdrive download 1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR
tar -xvzf compiler.tar.gz
rm -rf compiler.tar.gz
fi
