#!/bin/bash

# import vars
source vars.sh

# create dir
if [ ! -d $BIN ]; then
   mkdir -p $BIN
   mkdir -p $OBJ
fi
