#! /bin/sh
# Created Time: 2017-10-25 14:46:38
#

#
# typeset 是设置变量为 local 的变量
# 否则在递归调用中，值会被影响
#

recopy()
{
    typeset SRC=$1
    typeset DST=$2
    echo "[Error] : SRC != DST"
    echo "recopy SRC = $SRC"
    echo "recopy DST = $DST"
    #cp $SRC $DST
}

# input dir
filemd5_cmp()
{
    typeset SRC=$1
    typeset DST=$2
    typeset BEN=$3
    typeset BEN_FLAG=$BEN

    if [ "$BEN" = "s" ]; then
        BEN=$SRC
    else
        BEN=$DST
    fi

    echo "SRC = $SRC"
    echo "DST = $DST"
    echo "BEN = $BEN"
    echo "[Start] \$SRC : $SRC"
    echo "[Start] \$DST : $DST"

    for fn in `ls $BEN`; do

        if [ -d "$BEN/$fn" ]; then
            filemd5_cmp $SRC/$fn $DST/$fn $BEN_FLAG
        else
            echo "fn = $fn"
            typeset md5_b=`md5sum $BEN/$fn`
            typeset md5_b=`echo $md5_b | awk -F " " '{print $1}'`

            if [ "$BEN" = "$DST" ]; then
                typeset md5_s=`md5sum $SRC/$fn`
                typeset md5_s=`echo $md5_s | awk -F " " '{print $1}'`
                echo "md5_s = $md5_s | SRC"
                echo "md5_d = $md5_b | DST"
                if [ "$md5_s" != "$md5_b" ]; then
                    echo
                    recopy $SRC/$fn $BEN/$fn
                fi
            else
                typeset md5_d=`md5sum $DST/$fn`
                typeset md5_d=`echo $md5_d | awk -F " " '{print $1}'`
                echo "md5_s = $md5_b | SRC"
                echo "md5_d = $md5_d | DST"
                if [ "$md5_d" != "$md5_b" ]; then
                    echo
                    recopy $BEN/$fn $DST/$fn
                fi
            fi
            echo "-----------------------------------------------------------------"
        fi
    done

    echo "[End] \$SRC : $SRC"
    echo "[End] \$DST : $DST"
}

main()
{
    if [ "$#" != "0" ]; then

        echo 
        echo "PWD = `pwd`"

        if [ "$1" = "-h" ]; then
            echo 
            echo "-----------------------------------------------------------------"
            echo " options : "
            echo "  -s : src"
            echo "  -d : dst"
            echo "  -b : benchmark"
            echo 
            echo "  examples : "
            echo "     ./cpdir-md5.sh -s dirA -d dirB -b s"
            echo "     ./cpdir-md5.sh -s dirA -d dirB -b d"
            echo "     ./cpdir-md5.sh -d dirA -s dirB -b d"
            echo "     ./cpdir-md5.sh -d dirA -s dirB -b s"
            echo 
        fi

        if [ "$1" = "-s" ] && [ "$3" = "-d" ]; then
            echo "1"
            filemd5_cmp $2 $4 $6
        fi

        if [ "$1" = "-d" ] && [ "$3" = "-s" ]; then
            echo "2"
            filemd5_cmp $4 $2 $6
        fi
    else
        echo 
        echo "input : ./cpdir-md5.sh -h"
        echo 
    fi
}

main $*


