#! /bin/sh
# Created Time: 2016-11-04 10:29:19
#
 
#---------------------------------------------
# 可以使用 exec 命令通过文件描述符进行打开和关闭文件
# 通过文件描述符来进行 copy data
# copy 2 lines data from readme.txt
#
exec 4<&0 0<readme.txt

read line1
read line2

exec 0<&4
echo $line1
echo $line2

#---------------------------------------------
# '&&' 命令为先执行左边，为真时再执行右边
cp readme.txt log && echo "copy readme.txt done!" && rm log
cp stock.txt . && echo "copy stock.txt done!"

#
# \c 不换行
# \f 进纸
# \t 跳格
# \n 换行
#
echo "Input a string :\c"
#read string
echo $string

echo "\007 your home dir is %HOME, you are connected on `tty`"

