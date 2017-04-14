#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-09-08 09:42:27
#

#fn = "/home/minphone/share/temp/practice.py"
#fn = "/home/minphone/space_sdc/workspace/dic_parse/dicparse/src/dic/xhzd.txt"
fn = "/home/minphone/space_sdc/workspace/dic_parse/dicparse/src/dic/xdhycd.txt"

content = open(fn, 'r')

sindex = 0

for line in content:
    sindex += 1
    print "line :", sindex
    print line,



