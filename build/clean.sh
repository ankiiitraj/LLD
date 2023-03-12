#!/bin/bash

# import vars
source vars.sh

# check dir
./create.sh

# clean bin & obj
if ! [ "$(ls -A $BIN | wc -l)" -eq 0 ] && \
   ! [ "$(ls -A $OBJ | wc -l)" -eq 0 ]; then
   echo "cleaning..."
   rm $BIN/*
   rm $OBJ/*
fi
