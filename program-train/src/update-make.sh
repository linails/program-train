#! /bin/sh
# Created Time: 2016-06-27 13:25:31
#


if [ -d ../build ]; then
    echo "dir build exist"
    cd ../build/

    COMPILE_START=`date +%s%N`
    echo
    echo "compiling start ..."
    echo

    make -j4

    END=`date +%s%N`

    compile_cost=$((END-COMPILE_START))
    compile_cost=`expr $compile_cost / 1000000`

    echo "compile cost time = $compile_cost ms"
else
    mkdir ../build
    echo "mkdir ../build"
    ./build.sh
fi

