#! /bin/sh
# Created Time: 2017-01-3 12:52:33
#

cd ../build

echo "current exe path:"
pwd

valg="valgrind --tool=memcheck --leak-check=full "

if [ "$#" != "0" ]; then
    echo "para count : "$#
    echo "para list : "$*
    ${valg}bin/program-train $*
else
    ${valg}bin/program-train
fi

