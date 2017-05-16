#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2017-03-07 22:01:05
# Last modified: 2017-03-07 22:18:52
# 

import numpy as np
from numpy import *
from pprint import pprint

myzero = np.zeros([3, 5])
pprint(myzero)

myone = np.ones([3, 5])
pprint(myone)

myrand = np.random.rand(3, 4)
pprint(myrand)

myeye = np.eye(3)
pprint(myeye)

print "-------------------------------------"

myeye = np.eye(3)
myone = np.ones([3, 3])

pprint(myeye + myone)
pprint(myone - myeye)

print "-------------------------------------"

a = 10
mymatrix = mat([[1,2,3], [4,5,6], [7,8,9]])
mymatrix2 = 1.5 * ones([3, 3])          # 矩阵数乘

pprint(sum(mymatrix))                   # 矩阵个元素求和
pprint(multiply(mymatrix , mymatrix2))  # 矩阵点乘
pprint(a * mymatrix)                    # 矩阵数乘
pprint(power(mymatrix, 2))              # 矩阵各元素的 n 次幂

print "-------------------------------------"

mymatrix = mat([[1,2,3], [4,5,6], [7,8,9]])
mymatrix2 = mat([[1], [2], [3]])
pprint(mymatrix * mymatrix2)            # 矩阵乘法

print "-------------------------------------"




