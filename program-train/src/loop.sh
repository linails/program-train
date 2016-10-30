#! /bin/sh
# Created Time: 2016-04-23 14:35:27
#
int=1
echo "Creat tags begin"
while true
do
    echo $int
    int=`expr $int + 1`
    ./ctags.sh
    sleep 5
done
echo "while end"
