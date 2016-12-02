#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-12-02 15:05:32
# Last modified: 2016-12-02 15:41:31
# 

from pprint import pprint

# 带 yield 的函数称为 generator

def general():
    print "general ..."
    def fab(max):
        n, a, b = 0, 0, 1
        l = []
        while n < max:
            print "b :", b
            l.append(b)
            a, b = b, a + b
            n = n + 1
        return l

    print "fab(5) :", fab(5)

general()

#
# for i in range(1000): pass
# 会导致生成一个1000个元素的list
#
# for i in xrange(1000): pass
# 则不会生成一个1000个元素的list，而是在每次迭代中返回下一个数值，内存空间占用小
#

def itera_class():
    print "itera_class ..."
    __metaclass__ = type #定义这个表示后面定义的类是新式的类
    class Fab:
        def __init__(self, max):
            self.max = max
            self.n, self.a, self.b = 0, 0, 1

        def __iter__(self):
            return self

        def next(self):
            if self.n < self.max:
                r = self.b
                self.a, self.b = self.b, self.a + self.b
                self.n = self.n + 1
                return r
            raise StopIteration()

    for n in Fab(5):
        print 'n :', n

itera_class()

def yield_func():
    # yield 的作用就是把一个函数变成了一个 generator
    # 带有 yield 的函数不再是一个普通的函数
    # 调用此类型的函数，不会执行函数，而是会返回一个iterator对象

    # 调用fab()函数时，会执行fab()函数内部的代码，执行到 yield b时，返回一个迭代值
    # 下次迭代时，则代码从 yield b 的下一条语句继续执行，而函数的本地变量继续保持
    # 上次中断执行时的值
    print "yield_func ..."
    def fab(max):
        n, a, b = 0, 0, 1
        while n < max:
            print " - yield"
            yield b
            print " * *yield"
            a, b = b, a + b
            n = n + 1

    for n in fab(5):
        print 'n :', n

    print "-----------"

    f= fab(5)

    print "0 -"
    print "f.next() :", f.next()
    print "0 end"
    print "0 -"
    print "f.next() :", f.next()
    print "0 end"
    print "0 -"
    print "f.next() :", f.next()
    print "0 end"
    print "0 -"
    print "f.next() :", f.next()
    print "0 end"

yield_func()

# reference <<Expert Python Programming>>
class myIterator(object):
    def __init__(self, step):
        self.step = step

    def next(self):
        if self.step == 0:
            raise StopIteration
        else:
            self.step -= 1
            return self.step

    def __iter__(self):
        return self


