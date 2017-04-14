# readme.txt
# Created Time: 2016-09-17 10:15:50
# Last modified: 2016-10-29 14:08:33
#

 记录 shell 脚本的学习记录

01.if [ "$a" = ""]  :判断空字符串

02.str1  = str2     :两个字符串相等时(长度和内容相等)，返回真
   str1 != str2     :
   -n str1          :当串的长度>0时为真(串非空)
   -z str1          :空串
   str1             :str1非空时为真

03.int1 -eq int2    :int1 == int2
   int1 -ne int2    :int1 != int2
   int1 -gt int2    :int1 > int2
   int1 -ge int2    :int1 >= int2
   int1 -lt int2    :int1 < int2
   int1 -le int2    :int1 <= int2

04.-r file          :为用户可读为真
   -w file          :可写为真
   -x file          :可执行为真
   -f file          :文件为正规文件为真
   -d file          :文件为目录为真
   -c file          :文件为字符特殊文件为真
   -b file          :文件为块特殊文件为真
   -s file          :文件大小非0时为真
   -t file          :当文件描述符(默认为1)指定的设备为终端时为真

05.-a               :与
   -o               :或
   !                :非

06. 
   $0 当前程序的名称，实际上是一个内部参数，不同于$1,$2,...
   $# 传递给程序的总的参数的数目
   $? 上一个代码或者shell程序在shell中退出的情况，如果正常退出则返回0，反之为非0
   $* 传递给程序的所有参数组成的字符串
   $@ 以“参数1” “参数2” “参数3” ... 形式保存所有参数
   $$ 本程序的PID
   $! 上一个命令的PID

