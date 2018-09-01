#!/bin/bash
cd ..
rm -rf compiler

if [ ! -d "compiler" ]; then
mkdir compiler
wget -O compiler.tar.gz "https://drive.google.com/uc?export=download&confirm=KctX&id=1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR"
ls ./compiler
ls ./scripts
tar -xvzf compiler.tar.gz
rm -rf compiler.tar.gz
fi
