#! /bin/sh
# Created Time: 2017-10-25 14:41:50
#

# 递归调用
func()
{
    echo "\$1 = $1"

    if [ "$1" = "1" ]; then
        func $1
    fi
}

func 0
echo "---------------"
func 1

