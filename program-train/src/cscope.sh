#! /bin/sh
# Created Time: 2015-12-05 22:53:58
#

#cscope -Rbkq

rm cscope.files
rm cscope*.out

find ./srcs -name "*.hpp" -o -name "*.h" -o -name "*.cpp" -o -name "*.c" >> cscope.files
find ./libs -name "*.hpp" -o -name "*.h" -o -name "*.cpp" -o -name "*.c" >> cscope.files

cscope -Rbkq -i cscope.files


