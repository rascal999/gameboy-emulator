#!/bin/bash

cd ..
make clean

make
if [[ "$?" != "0" ]]; then
   exit
fi

sudo make install
if [[ "$?" == "0" ]]; then
   gb
fi
cd -
