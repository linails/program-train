#! /bin/sh
# Created Time: 2017-03-07 09:17:22
#

echo "current exe path:"
pwd

if [ "$GOPATH" = "" ]; then
    echo "gopath is empty"
    export GOPATH=`pwd`/../
else
    echo "gopath : "
    echo $GOPATH
fi

if [ -d github.com ]; then
    if [ -d github.com/op ]; then
        echo "github.com/op is exist"
    else
        go get github.com/op/go-logging
    fi

    #if [ -d github.com/gods ]; then
    #    echo "github.com/gods is exist"
    #else
    #    go get github.com/emirpasic/gods
    #fi
else
    go get github.com/op/go-logging
fi

echo "---------------------------------- "

if [ "$#" != "0" ]; then
    echo "para count : "$#
    echo "para list : "$*
    go run $*
fi


