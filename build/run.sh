#!/bin/bash

# import vars
source vars.sh

# check dir
./create.sh

# run
if ! [ "$(ls -A $BIN | wc -l)" -eq 0 ] && \
   ! [ "$(ls -A $OBJ | wc -l)" -eq 0 ]; then
   cd $BIN/
   ./$PRG
else
    echo "bin directory empty!"
fi
