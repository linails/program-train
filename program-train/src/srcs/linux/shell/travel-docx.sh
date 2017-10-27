#! /bin/sh
# Created Time: 2017-10-26 22:52:28
#

DOCX=./readme.txt

for line in `cat $DOCX | tr ' ' '@'`; do
    echo $line
done

