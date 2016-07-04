#! /bin/sh
# Created Time: 2016-04-23 14:26:21
#
cd ../build
rm -rf *
#cmake ../
cmake ../ -DCMAKE_C_COMPILER=/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-gcc-4.9.2 -DCMAKE_CXX_COMPILER=/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-g++


make
