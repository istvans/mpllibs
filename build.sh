#!/bin/bash

BOOST_ROOT="/usr/local"

mkdir -p bin
cd bin
cmake .. \
  -DCMAKE_CXX_COMPILER:STRING="/usr/bin/g++" \
  -DCMAKE_CXX_FLAGS:STRING="-std=c++0x -I$BOOST_ROOT/include -L$BOOST_ROOT/lib"

export LD_LIBRARY_PATH=$BOOST_ROOT/lib
make $*
make test

