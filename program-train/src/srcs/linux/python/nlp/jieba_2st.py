#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-09-02 17:57:59
#

import sys
import os
import jieba
import jieba.posseg as pseg

reload(sys)
sys.setdefaultencoding("utf-8")

seg_list = jieba.cut('我要在今晚21:00开卧室场景1, 你觉得效果怎么样', cut_all=False)
print "Default Mode:", "/ ".join(seg_list)

seg_list = jieba.cut('引进对象或事物的关系者', cut_all=False)
print "Default Mode:", "/ ".join(seg_list)

seg_list = pseg.cut('引进对象或事物的关系者')

Lword = []
Lflag = []
Lpair = []

for word in seg_list:
    Lword.append(word.word)
    Lflag.append(word.flag)
    #pair = (word.word, word.flag)
    Lpair.append((word.word, word.flag))

sword = " - "
s = sword.join(Lword)
l = sword.join(Lflag)

print "s :", s
print "l :", l

for pair in Lpair:
    print "%-5s - %-3s" % (pair[0], pair[1])

