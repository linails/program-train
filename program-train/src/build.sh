#! /bin/sh
# Created Time: 2016-04-23 14:26:21
#

START=`date +%s%N`

# check build dir
if [ -d ../build ]; then
    echo "dir build exist"
else
    mkdir ../build
    echo "mkdir ../build"
fi

cd ../build
rm -rf *

c_compiler=
cxx_compiler=
system_type=
cmake_para=

if [ "`getconf LONG_BIT`" = "32" ]; then
    echo "32 bit system"
    system_type="i686"
else
    echo "64 bit system"
    system_type="x86_64"
fi

for eachline in `cat /etc/issue`; do
    if [ "`echo $eachline | awk -F "." '{print $1}'`" = "14" ]; then
        echo "system version : 14"
        c_compiler="x86_64-unknown-linux-gnu-gcc-4.9.2"
        cxx_compiler="x86_64-unknown-linux-gnu-g++"

        if [ "`which $c_compiler`" ]; then
            echo "$c_compiler is exist"
        else
            if [ "$system_type" = "x86_64" ]; then
                c_compiler="/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-gcc-4.9.2"
                cxx_compiler="/opt/gcc-4.9.2/bin/x86_64-unknown-linux-gnu-g++"
            else
                c_compiler="/opt/gcc-4.9.2/bin/i686-pc-linux-gnu-gcc-4.9.2"
                cxx_compiler="/opt/gcc-4.9.2/bin/i686-pc-linux-gnu-g++"
            fi
        fi

        break
    fi
done

if [ "$c_compiler" = "" ]; then
    echo "######################################################"
    echo ""
    echo "gcc -version"
    echo `gcc -v`
    echo ""
    echo "######################################################"
else
    echo "######################################################"
    echo ""
    echo "gcc -version"
    echo `$c_compiler -v`
    echo "######################################################"
    cmake_para="-DCMAKE_C_COMPILER=$c_compiler -DCMAKE_CXX_COMPILER=$cxx_compiler -DSYSTEM_TYPE=$system_type"
fi

cmake ../ $cmake_para

COMPILE_START=`date +%s%N`
echo
echo "compiling start ..."
echo

make -j4

END=`date +%s%N`

compile_cost=$((END-COMPILE_START))
compile_cost=`expr $compile_cost / 1000000`

all_cost=$((END-START))
all_cost=`expr $all_cost / 1000000`

echo "compile cost time = $compile_cost ms"
echo "All cost time = $all_cost ms"

