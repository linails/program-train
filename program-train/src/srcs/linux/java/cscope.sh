#! /bin/sh
# Created Time: 2016-09-26 00:00:24
#

# -R : 在生成索引文件时，搜索子目录树中的代码 
# -b : 只生成索引文件，不进入cscope的界面
# -k : 在生成索引文件时，不搜索 /usr/include 目录
# -q : 生成 cscope.in.out 和 cscope.po.out 文件，加快 cscope 的索引速度

find . -name "*.h" -name "*.hpp" -o -name "*.c" -o -name "*.cpp" -o -name "*.cc" \
    -o -name "*.java" > cscope.files

cscope -bkq -i cscope.files

ctags -R

