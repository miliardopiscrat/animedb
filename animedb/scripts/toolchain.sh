#!/bin/bash
cd ..

if [ ! -d "compiler" ]; then
ggID='1fL4TMGhfmXRQ3cOEGa3H3afExt6pMrzR'  
ggURL='https://drive.google.com/uc?export=download'  
filename="$(curl -sc /tmp/gcokie "${ggURL}&id=${ggID}" | grep -o '="uc-name.*</span>' | sed 's/.*">//;s/<.a> .*//')"  
getcode="$(awk '/_warning_/ {print $NF}' /tmp/gcokie)"  
curl -Lb /tmp/gcokie "${ggURL}&confirm=${getcode}&id=${ggID}" -o "${filename}"  

tar -xvzf compiler.tar.gz
rm -rf compiler.tar.gz
#tar -xvzf ./scripts/make.tar.gz
fi
