#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-09-05 09:56:51
#

import sys
import os
import jieba
import jieba.posseg as pseg

reload(sys)
sys.setdefaultencoding("utf-8")

string = raw_input("Input String :")
seg_list = pseg.cut(string)

Lpair = []
for pair in seg_list:
    Lpair.append((pair.word, pair.flag))
    #print "word :", pair.word , " - ",
    #print "flag :", pair.flag

for pair in Lpair:
    print '(', pair[0], '-', pair[1], ')',


