#! /bin/sh
# Created Time: 2015-11-12 10:56:45
#
cd ../../build
rm -rf *

c_compiler=
cxx_compiler=
cmake_para=

for eachline in `cat /etc/issue`; do
    if [ "`echo $eachline | awk -F "." '{print $1}'`" = "14" ]; then
        echo "system version : 14"
        c_compiler="x86_64-unknown-linux-gnu-gcc-4.9.2"
        cxx_compiler="x86_64-unknown-linux-gnu-g++"
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
    cmake_para="-DCMAKE_C_COMPILER=$c_compiler -DCMAKE_CXX_COMPILER=$cxx_compiler"
fi

cmake ../ $cmake_para

make

