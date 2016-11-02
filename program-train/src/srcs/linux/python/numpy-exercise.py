#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-28 14:00:57
# Last modified: 2016-11-01 16:36:45
# 

import sys,os
import numpy as np
from pprint import pprint

print
print "------------------------------------"
print

print np.__version__
print np.__file__

print "------------------------------------"

a = np.array([1, 2, 3, 4])
b = np.array([5, 6, 7, 8])
c = np.array([[1, 2, 3, 4], [4, 5, 6, 7], [7, 8, 9, 10]])

print 
print "b.shape :", b.shape
print b

print 
print "c.shape :", c.shape
print c

print 
# Note : 通过修改 shape属性，就可以修改数组
c.shape = 4, 3
print c

print 
# Note : 当设置某个轴的元素个数为-1时，将自动计算此轴的长度
c.shape = 3, -1
print c
print "c.shape :", c.shape

print "------------------------------------"

print 
d = a.reshape((2, 2))
print "d.shape : ", d.shape
print d  # Note : 数组 d 和 a 共享一个空间，修改一个，另一个也被修改

print 
print "d[0][0] :", d[0][0]
d[0][0] = 20
print d
print a

a[1] = 100
print "a[1] = 100"
print "d :", d
print "a :", a

print "------------------------------------"

# Note : 获取元素类型 | 还可以指定数据类型
print "a.dtype :", a.dtype

print "np.array([1, 2, 3, 4], dtype=np.float) : ", np.array([1, 2, 3, 4], dtype=np.float)
print "np.array([1, 2, 3, 4], dtype=np.complex) : ", np.array([1, 2, 3, 4], dtype=np.complex)

print "------------------------------------"

print "set(np.typeDict.values()) :"
pprint(set(np.typeDict.values()))

print "------------------------------------"

print "np.arange(0, 1, 0.1) :" # Note: range [0, 1)
pprint(np.arange(0, 1, 0.1))

print "np.linespace(0, 1, 12) :" # Note: 元素开始值、终值、元素个数 : 等差数列
pprint(np.linspace(0, 1, 12))

print "np.logspace(0, 2, 5) :" # Note: 与linespace 类似，等比数列
pprint(np.logspace(0, 2, 5))

print "------------------------------------"

# Note: 默认基数是10，可以通过base设置基数，并设置endpoint为False
print "np.logspace(0, 1, 12, base=2, endpoint=False) : - base = 2, endpoint = False"
pprint(np.logspace(0, 1, 12, base=2, endpoint=False))

print "------------------------------------"

__metaclass__ = type #定义这个表示后面定义的类是新式的类
class Test:
    def __init__(self):
        print "class Test init"
    def __del__(self):
        print "class Test uninit"

test = Test()

print "------------------------------------"

# zeros() | ones() | empty() 可以创建指定形状和类型的数组
# empty() 仅仅分配数组所使用的内存，不对数组元素进行初始化操作

print 'np.empty((2,3), np.int) :'
pprint(np.empty((2,3), np.int))

# Note: zeros() 将数组元素初始化为0
print "np.zeros(4, np.float) :"
pprint(np.zeros(4, np.float))

# Note: ones() 将数组元素初始化为1
print "np.ones(4, np.float) :"
pprint(np.ones(4, np.float))

# Note: 
# zeros_like() / ones_like() / empty_like() 等函数可以创建与参数数组的形状及类型相同的数组
#
# eg.
# a = zeros(4)
# b = zeros_like(a)

print "------------------------------------"

# Note: frombuffer(), fromstring(), fromfile()
# 这些函数可以从字节序列或文件创建数组

s = "abcdefgh"
a = np.fromstring(s, dtype=np.int8)
print "a : - %d " % len(a)
pprint(a)

# 如果从s创建16bit的整数数组，那么两个相邻的字节就表示一个整数
a = np.fromstring(s, dtype=np.int16)
print "a : - %d " % len(a)
pprint(a)

a = np.fromstring(s, dtype=np.float)
print "a : - %d " % len(a)
pprint(a)

print "------------------------------------"
