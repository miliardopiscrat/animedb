#!/bin/bash
cd ..
rm -rf compiler

if [ ! -d "compiler" ]; then
cd ./scripts
tar -xvzf gdrive.tar.gz
./gdrive download 1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR
tar -xvzf compiler.tar.gz -C ../
rm -rf compiler.tar.gz
fi
