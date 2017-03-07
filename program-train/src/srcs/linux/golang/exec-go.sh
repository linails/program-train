#! /bin/sh
# Created Time: 2017-03-07 09:17:22
#

echo "current exe path:"
pwd

if [ "$#" != "0" ]; then
    echo "para count : "$#
    echo "para list : "$*
    go run $*
fi


