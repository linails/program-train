#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2017-05-15 17:01:06
# Last modified: 2017-05-16 14:46:12
# 

import sys
import os
import re
#from pyltp import Segmentor
#from pyltp import Postagger
from pyltp import *
import nltk
from nltk.tree import Tree
from nltk.grammar import DependencyGrammar
from nltk.parse import *

__metaclass__ = type
class SegTester:
    def __init__(self):
        self.models = []
        self.words = [{}, {}]
        self.models.append("/home/minphone/github-win/NLP/ltp_data/cws.model")
        self.models.append("/home/minphone/github-win/NLP/ltp_data/pos.model")
        self.models.append("/home/minphone/github-win/NLP/ltp_data/ner.model")
        self.segmentor = Segmentor()
        self.segmentor.load(self.models[0])

    def seg(self, tag, string):
        words = self.segmentor.segment(string)
        self.words[0][tag] = " ".join(words)
        print tag + " : ", self.words[0][tag]

    def tagger(self, tag, ner = False):
        tagger = Postagger()
        tagger.load(self.models[1])
        words = self.words[0][tag].split(" ")
        tags = tagger.postag(words)
        if True != ner:
            for word, postag in zip(words, tags):
                print word + "/" + postag ,
            print
        else:
            recognizer = NamedEntityRecognizer()
            recognizer.load(self.models[2])
            words = self.words[0][tag].split(" ")
            netags = recognizer.recognize(words, tags)
            for word, postag, netag in zip(words, tags, netags):
                print word+"/"+postag+"/"+netag,
            print


st = SegTester()
st.seg("demo", "在包含问题的所有解空间树中，按照深度优先搜索的策略，从根节点出发深度探索解空间树")
st.seg("1", "我就告诉人家我的名字")
st.seg("2", "当别人问我名字的时候，我就告诉人家我的名字")

st.tagger("demo")
st.tagger("1")
st.tagger("2", True)

