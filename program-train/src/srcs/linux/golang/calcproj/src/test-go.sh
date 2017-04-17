#! /bin/sh
# Created Time: 2017-03-20 17:54:10
#

if [ "$GOPATH" = "" ]; then
    echo "gopath is empty"
    export GOPATH=`pwd`/../
else
    echo "gopath : "
    echo $GOPATH
fi

echo "---------------------------------- "

if [ "$#" != "0" ]; then
    echo "para count : "$#
    echo "para list : "$*
    go test $*
fi

