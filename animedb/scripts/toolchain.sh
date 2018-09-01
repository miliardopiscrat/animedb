#!/bin/bash
cd ..
rm -rf compiler

if [ ! -d "compiler" ]; then
cd ./scripts
tar -xvzf gdrive.tar.gz
./gdrive --access-token "4/TQCT57PHjwlWuYP9bRIeCk75SVHrrMpWPDK0T2m43XPOYpwPh2TthBA" download "1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR"
tar -xvzf compiler.tar.gz -C ../
rm -rf compiler.tar.gz
fi
