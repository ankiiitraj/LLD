#!/bin/bash

# import vars
source vars.sh

# check dir
./create.sh

# clean before build
./clean.sh

# build each
g++ -c $SRC/$SHARE.cpp -I $INC/ -o $OBJ/$SHARE.o
g++ -c $SRC/$LEDGER_STATEMENT.cpp -I $INC/ -o $OBJ/$LEDGER_STATEMENT.o
g++ -c $SRC/$EXPENSE.cpp -I $INC/ -o $OBJ/$EXPENSE.o
g++ -c $SRC/$EXPENSE_APP.cpp -I $INC/ -o $OBJ/$EXPENSE_APP.o
g++ -c $SRC/$EXACT_SHARE_EXPENSE.cpp -I $INC/ -o $OBJ/$EXACT_SHARE_EXPENSE.o
g++ -c $SRC/$EQUAL_SHARE_EXPENSE.cpp -I $INC/ -o $OBJ/$EQUAL_SHARE_EXPENSE.o
g++ -c $SRC/$USER.cpp -I $INC/ -o $OBJ/$USER.o
g++ -c $SRC/$MAIN.cpp -I $INC/ -o $OBJ/$MAIN.o

# link all
 g++ $OBJ/$EQUAL_SHARE_EXPENSE.o \
  $OBJ/$EXACT_SHARE_EXPENSE.o \
  $OBJ/expense.o \
  $OBJ/$EXPENSE_APP.o \
  $OBJ/$LEDGER_STATEMENT.o \
  $OBJ/share.o \
  $OBJ/$USER.o \
  $OBJ/$MAIN.o \
  -o $BIN/$PRG
