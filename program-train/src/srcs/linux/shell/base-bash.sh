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

#---------------------------------------------
arrayXue[0]="a"
arrayXue[1]="b"

# ${#arrayXue[@]} : 数组长度
echo "length of arrayXue = ${#arrayXue[@]}"
for var in ${arrayXue[@]}; do
    echo "var = $var"
done

#---------------------------------------------
# bash 中定义函数内的局部变量用 local 关键字

