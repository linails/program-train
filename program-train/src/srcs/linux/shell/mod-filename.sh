#! /bin/sh
# Created Time: 2017-07-19 22:45:58
#

echo "dir = $1 | prefix : \$2 = $2 | \$3 = $3"

if [ "$3"="yes" ]; then
    index=0
    for fn in `ls $1 | tr ' ' '#'`; do
        index=`expr $index + 1`
        #echo "index = $index"
        if [ -d "$1/$fn" ]; then
            echo "skip dir : $fn"
        else
            suffix=`echo $fn | awk -F "." '{print $2}'`
            newname="$2$index.$suffix"
            echo "newname = $newname"
            mv "`echo $1/$fn | sed 's/#/ /g'`" $1/$newname
        fi
    done
fi

