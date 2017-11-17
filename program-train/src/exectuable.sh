#! /bin/sh
# Created Time: 2016-04-23 14:34:33
#

EXE=bin/program-train

cd ../build

echo "current exe path:"
pwd

if [ "$#" != "0" ]; then
    echo "para count : "$#
    echo "para list : "$*
    $EXE $*
else
    $EXE
fi

echo "[SIZE] $EXE = `stat -c "%s" $EXE` byte"
echo

