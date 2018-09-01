#!/bin/bash
cd ..
rm -rf compiler

if [ ! -d "compiler" ]; then
cd ./scripts
tar -xvzf gdrive.tar.gz
./gdrive --access-token "4/TQBFy5Qufh15ruEmdUiLdAbqXO18ALRpO-Ert1zgXIPBQzKUa5fjNr8"
./gdrive download "1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR"
tar -xvzf compiler.tar.gz -C ../
rm -rf compiler.tar.gz
fi
