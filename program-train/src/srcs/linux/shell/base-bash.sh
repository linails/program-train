#! /bin/bash
# Created Time: 2016-11-04 10:28:01
#

pylibs=(
    "libs0"
    "libs1"
)

echo ${pylibs[*]}

# -n 禁止换行
# -e 使转义生效
echo -n "Input a string :"
echo -e "Input a string: \c"
read string
echo "string ="$string

