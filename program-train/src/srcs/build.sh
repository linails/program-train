#! /bin/sh
# Created Time: 2015-11-12 10:56:45
#
cd ../../build
rm -rf *
cmake ../ -DCMAKE_C_COMPILER=/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-gcc-4.9.2 -DCMAKE_CXX_COMPILER=/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-g++

make

