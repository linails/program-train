#! /bin/sh
# Created Time: 2016-04-23 14:27:47
#

EXE=bin/program-train

cd ../build
echo "current exe path : "
pwd
gdb $EXE
