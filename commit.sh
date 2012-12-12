#!/bin/bash

make clean
if [[ $? != 0 ]]; then
   exit
fi

autoreconf --install
if [[ $? != 0 ]]; then
   exit
fi

./configure
if [[ $? != 0 ]]; then
   exit
fi

make
if [[ $? != 0 ]]; then
   exit
fi

make check
if [[ $? != 0 ]]; then
   exit
fi

make distcheck
if [[ $? != 0 ]]; then
   exit
fi

mv gameboy-emulator-0.1.tar.gz dist/
if [[ $? != 0 ]]; then
   exit
fi

sudo make install
if [[ $? != 0 ]]; then
   exit
fi

git commit -a
if [[ $? != 0 ]]; then
   exit
fi

git push
