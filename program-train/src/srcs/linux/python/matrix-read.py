#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-09-28 12:54:03
#

import scipy.io
from pprint import pprint

data = scipy.io.loadmat("/home/minphone/share/temp/data/data1.mat")

keylist = data.keys()

print "type(data) :", type(data)

print keylist

for key in keylist:
    print "key :", key

print data[keylist[1]]
pprint(data[keylist[1]])
#print data["data1"]

