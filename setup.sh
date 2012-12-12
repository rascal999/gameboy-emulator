#!/bin/bash

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
