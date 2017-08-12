#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2017-05-15 17:01:06
# Last modified: 2017-05-16 12:31:45
# 

import sys
import os
from pyltp import *

tagger = Postagger()
tagger.load("/home/minphone/github-win/NLP/ltp_data/pos.model")

s = "我 就 告诉 人家 我 的 名字"
words = s.split(" ")
print "words :", words
tags = tagger.postag(words)
for word, postag in zip(words, tags):
    print word + "/" + postag ,


