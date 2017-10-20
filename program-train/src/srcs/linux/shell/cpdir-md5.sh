#! /bin/sh
# Created Time: 2017-10-20 15:50:02
#

recopy()
{
    SRC=$1
    DST=$2
    echo "[Error] : SRC != DST"
    echo "recopy SRC = $SRC"
    echo "recopy DST = $DST"
    #cp $SRC $DST
}

filemd5_cmp()
{
    SRC=$1
    DST=$2
    BEN=$3

    if [ "$BEN" = "s" ]; then
        BEN=$SRC
    else
        BEN=$DST
    fi

    echo "SRC = $SRC"
    echo "DST = $DST"
    echo "BEN = $BEN"

    for fn in `ls $BEN`; do
        echo "fn = $fn"
        md5_b=`md5sum $BEN/$fn`
        md5_b=`echo $md5_b | awk -F " " '{print $1}'`

        if [ "$BEN" = "$DST" ]; then
            md5_s=`md5sum $SRC/$fn`
            md5_s=`echo $md5_s | awk -F " " '{print $1}'`
            echo "md5_s = $md5_s | SRC"
            echo "md5_d = $md5_b | DST"
            if [ "$md5_s" != "$md5_b" ]; then
                recopy $SRC/$fn $BEN/$fn
            fi
        else
            md5_d=`md5sum $DST/$fn`
            md5_d=`echo $md5_d | awk -F " " '{print $1}'`
            echo "md5_s = $md5_b | SRC"
            echo "md5_d = $md5_d | DST"
            if [ "$md5_d" != "$md5_b" ]; then
                recopy $BEN/$fn $DST/$fn
            fi
        fi
        echo "-----------------------------------------------------------------"
    done
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

