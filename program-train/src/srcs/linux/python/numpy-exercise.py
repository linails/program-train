#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-10-28 14:00:57
# Last modified: 2016-12-06 17:18:34
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

print "(10, ) : "
pprint((10, ))

def func(i):
    return i*2

# Note: 第一个参数为计算数组元素的函数，第二个参数指定数组的形状 | 因此第二个参数必须是一个序列
a = np.fromfunction(func, (10, ))
print "a : - %d " % len(a)
pprint(a)

def func2(i, j):
    return (i+1) * (j+1)

a = np.fromfunction(func2, (9, 9))
print "a : - %d " % len(a)
pprint(a)

print "------------------------------------"

# Note: 可以使用和列表相同的方式对数组的元素进行存取
#       和列表不同的是，通过切片获取的新数组是原始数组的一个视图，是共享一个存储空间的
#       有点类似于引用了
a = np.arange(10)
print "a : - %d " % len(a)
pprint(a)

print "a[4] :", a[4]
print "a[1:-1:2] :"
pprint(a[1:-1:2])   # Note: 第三个参数表示步长，2表示间隔1个元素获取一个元素

print

a = np.array([1, 2, 3, 4])
print "a : - %d " % len(a)
pprint(a)
print "a[2] :", a[2]

print
print "a[::-1] :"
pprint(a[::-1])

print "------------------------------------"

# Note: 除了切片下标存取元素之外，Numpy还提供了整数列表、整数数组和布尔数组等几种高级下标存取方法
#       当使用整数列表对数组元素进行存取时，将使用列表中的每个元素作为下标
#       使用列表作为下标得到的数组不和原始数组共享数据

x = np.arange(10, 1, -1)    # x = [10, 1) , interval = -1
print "x = np.arange(10, 1, -1) :"
pprint(x)

b = x[[3, 3, 1, 8]]
print 
print "b = x[[3, 3, 1, 8]] :"
pprint(b)

b[1] = 10
print 
print "b[1] = 10"
print "b = ", pprint(b)
print "x = ", pprint(x)

c = x[np.array([3, 3, 1, 8])]
print 
print "c = x[np.array([3, 3, 1, 8])] :" 
pprint(c)

print "------------------------------------"

x = np.arange(5, 0, -1)
print "x = ", pprint(x)

print # Note: 布尔数组中下标为0、2的元素为True，因此获取数组x中下标为0、2的元素
print "x[np.array([True, False, True, False, False])] = ", pprint(x[np.array([True, False, True, False, False])])

print # Note: 如果是布尔列表，则把True当作1，False当作0，按照整数序列方式获取数组x中的元素
print "x[[True, False, True, False, False]] = ", pprint(x[[True, False, True, False, False]])

print # Note: 布尔数组的长度不够时，不够的部分都当作False
print "x[np.array([True, False, True, True])] = ", pprint(x[np.array([True, False, True, True])])

print 
x[np.array([True, False, True, True])] = -1, -2, -3
print "x[np.array([True, False, True, True])] = -1, -2, -3  : ", pprint(x)

print "------------------------------------"

print "range(1) :", range(1)

