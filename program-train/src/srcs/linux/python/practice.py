#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-05-04 15:49:26
# default python version 2.7

import binascii
import struct
import sys,os
from pprint import pprint

print "\n\n" + "*"*80 + "\n\n"

print("nice!");

a = 10;
print a;
string = "hello world ";

print string + `a`;
print 123

print "string : " + repr(string)
print "'s' in string : " + repr('s' in string)

#name = raw_input("what's your name ? \n");
#print name;
#print " welcom !";

print "------------------------------------------------------------"

print '''多行显示 - 1
多行显示 - 2''';

print "nice to \
meet you";

print "/home/minphone/space_sdc";

print "C:\user\ember";

# r - 表示原始字符串的意思
print r"C:\user\ember";

# u - 表示unicode方式输出 - 在python3中，均是unicode的，不需要加这个符号
print u"hello unicode";

print "------------------------------------------------------------"

greeting = 'nice'
print "greeting : " + repr(greeting)
print "greeting[0] : " + repr(greeting[0])
print "greeting[-1] : " + repr(greeting[-1])

numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print "numbers[:] : " + repr(numbers[:])
print "numbers[3:6] : " + repr(numbers[3:6])
print "numbers[0:1] : " + repr(numbers[0:1])
print "numbers[-3:-1] : " + repr(numbers[-3:-1])
print "numbers[-3:] : " + repr(numbers[-3:])
print "numbers[:3] : " + repr(numbers[:3])
print "numbers[3:10:2] : " + repr(numbers[3:10:2])

number2 = [11, 12, 13, 14, 15]
print "numbers2[:] : " + repr(number2[:])
print "numbers + number2 : " + repr(numbers + number2)

numbers3 = ['*'] * 5
print numbers3

sequence = [None] * 10
print sequence

print "------------------------------------------------------------"

string = 'string'

print "'s' in string"
print 's' in string
print 'length of string :'
print len(string)
print max(string)
print min(string)

import math

age = 12.5
print "age = "
print age

print "floor(age) = "
print math.floor(age)
print int(math.floor(age))
print "ceil(age)"
print math.ceil(age)
print int(math.ceil(age))

import cmath
print cmath.sqrt(-1) #-1的开方是虚数

print (1 + 3j) * (9 + 4j)

print "nice " 'to ' "meet you " "python!"

print "age = " + `age`
print "math.floor(age) : " + `math.floor(age)`
print "int(math.floor(age)) : " + `int(math.floor(age))`
print "math.ceil(age) : " + `math.ceil(age)`
print "int(math.ceil(age)) : " + `int(math.ceil(age))`

print "age = " + repr(age)
print "math.floor(age) : " + repr(math.floor(age))
print "int(math.floor(age)) : " + repr(int(math.floor(age)))
print "math.ceil(age) : " + repr(math.ceil(age))
print "int(math.ceil(age)) : " + repr(int(math.ceil(age)))

#name = raw_input("Input your name : ") #一般使用raw_input()
#print "Name : " + name

print "------------------------------------------------------------"

x = [1, 2, 4]
print x
x[1] = 5
print x

del x[0]
print x

name = list("minphone") # name = "minphone" 会导致出差
name[2:5] = list("lin")
print "name = " + repr(name)
name.append('go');
print "name = " + repr(name)
print "name.count('n') : " + repr(name.count('n'))

a = [3, 2, 7]
b = [4, 5, 6]
print "a+b : " + repr(a + b)
print "a = " + repr(a)
a.extend(b);
print "a.extend(b) : " + repr(a)
print "a = " + repr(a)

print "a[:len(a)] : " + repr(a[:len(a)])

print "a.index(4) : " + repr(a.index(4))
print "a.insert(3, 'four') : " + repr(a.insert(3, 'four'))
print "a = " + repr(a)

p = a.pop()
print "p = " + repr(p)
print "a = " + repr(a)

a.remove(4); #删除值的时候，必须填值，删除字符串的时候，带上字符串引号
print "a = " + repr(a)

a.remove("four");
print "a = " + repr(a)

a.reverse();
print "a = " + repr(a)

a.sort()
print "a = " + repr(a)

print "------------------------------------------------------------"

x = ['arrdvark', 'abalone', 'acame', 'add', 'aerate']
print "x = " + repr(x)

x.sort()
print "x.sort()"
print "x = " + repr(x)

x.sort(key=len)
print "x.sort(key=len)"
print "x = " + repr(x)

x.sort(reverse=True)
print "x.sort(reverse=True)"
print "x = " + repr(x)

print "------------------------------------------------------------"

c = 12, #定义了一个元组
print "c = " + repr(c)

print "a = " + repr(a)
b = tuple(a)            #返回元组
print "a = " + repr(a)
print "b = " + repr(b)

print "b[0] : " + repr(b[0])

s = "minphone@gotohome"

print "'go' in s : " + repr('go' in s) # 用 in 查找子字符串

print "------------------------------------------------------------"

forma = "output : %s - %s !"
value = ("one", "two")
print forma % value

format = "output : %s - %s !"
print format % value

#元组才可以使用格式化，以及字典可以使用格式化
#values = ["tone", "ttwo"]
#print format % values

from string import Template

s = Template('$x. glorious $x!')
print "s.substitute(x='ng') = " + s.substitute(x='ng')

s1 = s.substitute(x='ng')
print "s1 = " + repr(s1)

s = Template('$thing must never $action')
d = {}
d['thing'] = 'gentleman'
d['action'] = 'show his socks'

print "s.substitute(d) : " + s.substitute(d) # s 本身就是字符串
print "s.substitute(d) : " + repr(s.substitute(d))

print "'%s plus %s equals %s' % (1, 2, 3) : " + repr('%s plus %s equals %s' % (1, 2, 3))

print "------------------------------------------------------------"

title = "Monty Python's flying circus"
print "title.find('Monty') : " + repr(title.find("Monty")) # return index of title
print "title.find('flying') : " + repr(title.find("flying"))
print "title.find('hxlyg') : " + repr(title.find("hxlyg")) # failed return -1

subject = "$$$ get rich now!!! $$$"
print "subject : " + subject
print "subject.find('$$$', 1) : " + repr(subject.find('$$$', 1)) # only provide start index
print "subject.find('$$$', 1, 16) : " + repr(subject.find('$$$', 1, 16)) # provide start and end index

seq = ['1', '2', '3', '4', '5']
sep = '+'
#seq.join(sep) 这种用法是错误的，list没有join方法
s = sep.join(seq)
print "sep : " + sep
print "seq : " + repr(seq)
print "s = " + s
q = s.split('+')
print "q =", q

ts = "nice to meet you"
tsq = ts.split()
print "tsq :", tsq

dirs = '', 'usr', 'bin', 'env'
s = '/'.join(dirs)
print "s = " + s


print "C: + '\\'.join(dirs) : " + 'C:' + '\\'.join(dirs)


print "'TrondlDOGHOJLK'.lower() : " + 'TrondlDOGHOJLK'.lower()
print "'This is a test'.replace('is', 'eez') : " + 'This is a test'.replace('is', 'eez')
print "'   doiojgoij    '.strip() : " + '   doiojgoij    '.strip()

from string import maketrans
table = maketrans('cs', 'kz')
print "len(table) : " + repr(len(table))
print "table : " + table[97:123]

print "------------------------------------------------------------"

phonebook = {'Alice':'1234', 'Beth':'2222', 'Cecil':'3245'}
print "phonebook : " + repr(phonebook)

items = [('name', 'gumby'), ('age', 42)]
d = dict(items)
print "d = " + repr(d)
print "d['age'] : " + repr(d['age'])

#e = dict('name' = 'minphone', 'age' = 27) #keyword can't be an expression
e = dict(name = 'minphone', age = 27)
print "e = " + repr(e)

e['sex'] = 'man'
e['work'] = 'programer'
print "e = " + repr(e)

print "len(e) : " + repr(len(e))
print "e['sex'] : " + repr(e['sex'])
e['work'] = 'manager'
print "e = " + repr(e)

del e['sex']
print "'sex' in e : " + repr('sex' in e)

f = e.copy()
print "f = " + repr(f)

print "------------------------------------------------------------"

print "age : ", 42 #用逗号隔开，可以一行输入多个表达式

name = 'Gumby'
salutation = "Mr."
greeting = 'Hello'
print name, salutation, greeting

print 'hello', #这里加了逗号，就会自动添加空格
print "world"

x, y, z = 1, 2, 3 #序列解包/可选代解包
print "x, y, z :" , x, y, z
values = 1, 2, 3
print "values : ", values

scoundrel = {'name':'Robin', 'girlfriend':'Marion'}
key,value = scoundrel.popitem()
print "scoundrel :", scoundrel
print "key : " + repr(key)
print "value : " + repr(value)

print "------------------------------------------------------------"

x = 2
print "x :", x
x += 3
print "x += 3 :", x
print "bool('hello') :", bool('hello') #bool函数用来转换其他值到bool值

print "------------------------------------------------------------"

#name = raw_input('what is your name : ')
name = 'Gumby'
if name == 'Gumby':
    print "Hello. Mr. Gumby"
else:
    print "Hello. stranger"

num = input('Enber a number : ')
if num > 0:
    print "num > 0"
elif num < 0:
    print "num < 0"
else:
    print "num = 0"

age = 10
assert 0 < age < 100
#age = 110
#assert 0 < age < 100 #can crash program

print "------------------------------------------------------------"

x = 1
while x <= 10:
    print "x =", x
    x += 1

words = ['this', 'is', 'an', 'ex', 'parrot']
for word in words:
    print word

print "range(0, 10) : " + repr(range(0, 10)) #迭代输出

for i in range(10):
    print "i = " + repr(i)

print "------------------------------------------------------------"

names = ['anne', 'beth', 'george', 'damon']
ages = [12, 25, 34, 34]
for name, age in zip(names, ages):
    print name, 'is', age, 'years old'
for pair in zip(names, ages):
    print pair

for index, name in enumerate(names): #enumerate()用于得到索引
    print "name :", name,"-->",
    print "index :", index

nums = [2, 4, 3, 7, 1, 0]
print "nums : " + repr(nums)
snums = sorted(nums)
print "snums : " , snums
rnums = reversed(snums)
print "rnums : " , list(rnums)

print "for n in reversed(snums)"
for n in reversed(snums):
    print "n = ", n

print "rs = reversed(snums) -> for n in rs:"
rs = reversed(snums)
for n in rs:    #迭代器在这里会逐渐累加
    print "n = ", n

print "------------------------------------------------------------"

print '[x*x for x in range(10)] :', [x*x for x in range(10)]
print "[(x, y) for x in range(5) for y in range(5, 10)] :", [(x, y) for x in range(5) for y in range(5, 10)]

print "x =", x

# 删除x后，就没有这个变量了
#del x
#print "x =", x

print "------------------------------------------------------------"

exec "print 'hello world ! <- by exec'"

scope = {}
exec "sqrt = 1" in scope
print "scope['sqrt'] :", scope['sqrt']

print "len(scope) :", len(scope)
print "scope.keys() :", scope.keys()

scope['x'] = 2
scope['y'] = 3
print "eval('x*y', scope) :", eval('x*y', scope)

print "------------------------------------------------------------"

fibs = [0, 1]
for i in range(8):
    fibs.append(fibs[-1] + fibs[-2])

print "fibs :", fibs

y = math.sqrt
print "callable(y) :", callable(y) #callable()函数可以用来判断函数是否可被调用，在python3中不可用

def calc_fibs(num):
    result = [0, 1]
    for i in range(num):
        result.append(result[-1] + result[-2])
    return result

print "calc_fibs(10) :", calc_fibs(10)
#print help(calc_fibs)

print "------------------------------------------------------------"

print "names =", names
n2 = names
print "n2 is names :", n2 is names
n3 = names[:]
print "n3 is names :", n3 is names

def print_params(title, *params1):
    print "title :", title
    print "params :", params1

title = 'print-title'
print_params(title, 1, 2, 3)

pa = 'test paras'
print_params(title, pa)
#print_params(title, some = 1) #需要使用2个*来实现传递参数名

def add(x, y): return x + y

param = (1, 2)

#print "add(param) :", add(param) # false
print "add(*param) :", add(*param)

print "------------------------------------------------------------"

print("'abcabbda'.count('a') :"), 'abcabbda'.count('a')

from random import choice
x = choice(['hello.world!', [1, 3, 'a', 'nice']])
print('x : '), x
print "x.count('e') :", x.count('e')

print "------------------------------------------------------------"

class Class:
    member = 0
    smem = 0
    def method(self):
        print "I have a self!"
    def increase(self):
        Class.member += 1
        self.smem += 1

def function():
    print "I don't ..."

instance = Class()
print "instance.method() :",
instance.method()
instance.method = function   #通过直接赋值，相当于是把方法引用指向了function
print "instance.method() :", 
instance.method()

instance1 = Class()
instance1.method()

print "instance.member :", instance.member
print "instance1.member :", instance1.member

instance.increase()
print "instance.member :", instance.member
print "instance1.member :", instance1.member

instance1.increase()
print "instance.member :", instance.member
print "instance1.member :", instance1.member

instance1.member = 'one'
instance2 = Class()
print "instance.member :", instance.member
print "instance1.member :", instance1.member
print "instance2.member :", instance2.member

instance2.member = 5
print "instance.member :", instance.member
print "instance1.member :", instance1.member
print "instance2.member :", instance2.member

print "instance.smem :", instance.smem
print "instance1.smem :", instance1.smem
print "instance2.smem :", instance2.smem

print "------------------------------------------------------------"

#raise Exception
import exceptions
print "all exceptions :"
print dir(exceptions)

print "------------------------------------------------------------"

del seq
seq = ['1', '2', '3', '4']
print "seq :", seq
#print "seq[5] :", seq[5] #throw an exception -> IndexError

print "------------------------------------------------------------"

__metaclass__ = type #定义这个表示后面定义的类是新式的类
class A:
    def __init__(self): # __init__ 就是构造函数
        self.name = "A"
        self.age = 12
        self.num = '1314520'
        self.addr = "xxxxxx"
    def print_msg(self):
        print "name :", self.name, " -",
        print "age :", self.age, " -",
        print "num :", self.num, " -",
        print "addr :", self.addr
    def regard(self):
        print "Hello , I'm class A"

#__metaclass__ = type
class B(A): # B derived from A
    def __init__(self):
        super(B, self).__init__() #只在新类中使用，或者是python3.0中
        #A.__init__(self)
        self.name = "B"
        self.age = 32
        self.num = '11111111'
    def print_msg(self):
        print "name :", self.name, " -",
        print "age :", self.age, " -",
        print "num :", self.num, " -",
        print "addr :", self.addr

if a:
    print "a is an value"
    del a
else:
    print "a is None"

if b:
    print "b is an value"
    del b
else:
    print "b is None"

# class define
a = A()
b = B()

a.regard()
b.regard()

a.print_msg()
b.print_msg()

print "------------------------------------------------------------"

__metaclass__ = type
class Rectangle:
    def __init__(self):
        self.width = 0
        self.height = 0
    def setSize(self, size):
    #def getSize(self, size):
        self.width, self.height = size
    def getSize(self):
    #def setSize(self):
        return self.width, self.height
    size = property(getSize, setSize) # property 函数只能在新式类中使用
    #size = property(setSize, getSize) # property 函数只能在新式类中使用 
    #      , 使用这个的话，得把前面的setSize,getSize的方法对调一下才可以

if Rectangle:
    print "Rectangle is an value class"
else:
    print "Rectangle is null"


r = Rectangle()
r.width = 10
r.height = 5

print "r.size :", r.size
r.size = 150, 100 # 通过 property 函数，可以让赋值更简便

print "r.size :", r.size

print "------------------------------------------------------------"

class TestIterator:
    value = 0
    def next(self):
        self.value += 1
        if self.value > 10 : raise StopIteration
        return self.value
    def __iter__(self):
        return self

it = TestIterator()
print "list(it) :", list(it)

print "------------------------------------------------------------"

def flatten(nested):
    try:
        for sublist in nested:
            for element in flatten(sublist):
                yield element
    except TypeError:
        yield nested

print "list(flatten([[[1], 2], 3, 4, [5, [6, 7], 8]])) :", list(flatten([[[1], 2], 3, 4, [5, [6, 7], 8]]))

f = flatten([[[1], 2], 3, 4, [5, [6, 7], 8]])
print "f.next() :", f.next()
print "f.next() :", f.next()
print "f.next() :", f.next()
print "f.next() :", f.next()

print "------------------------------------------------------------"

def repeater(value):
    while True:
        new = (yield value)
        if new is not None: value = new

r = repeater(42)
print "r.next() :", r.next()
print "r.send('hello world') :", r.send('hello world')

print "------------------------------------------------------------"

print set(range(10))

if a: del a
if b: del b

a = set([1, 2, 3])
b = set([2, 4, 7])

c = a | b
print c

if c : del c
c = a & b
print c

print "------------------------------------------------------------"

import time 
print time.asctime()

import random
print random.random()

print "------------------------------------------------------------"

mylist = [1, 2, 3, 4, 5]
length = len(mylist)
if a: del a
a = 10

for indx in xrange(length):
    mylist[indx] = a * mylist[indx]
    print "mylist[%d] :" % indx , mylist[indx]

print "mylist :", mylist

print "------------------------------------------------------------"

a = 1
b = 2
ans = a + b

print "%d plus %d equals %d" % (a, b, ans)

print "------------------------------------------------------------"

for i in range(0, 10):
    print "%5d  " % i

print "------------------------------------------------------------"

for n in range(99, 81, -1):
    root = math.sqrt(n)
    if root == int(root):
        print n
        break
else:
    print "Didn't find it"

print "------------------------------------------------------------"

lst = []

if not lst: print "lst is empty"

print "len(lst) :", len(lst)

lst.append("nice")
lst.append("to")
lst.append("you")
print "len(lst) :", len(lst)

lst[:] = []
print "len(lst) :", len(lst)

print "------------------------------------------------------------"

__metaclass__ = type 
class Zigbee:
    def __init__(self, name = "", oa = 10, ob = 11, oc = 12):
        self.name = name
        self.a = oa
        self.b = ob
        self.c = oc

    def print_all(self):
        d = 1234567890
        print ""
        print "self.name =", self.name
        print "self.a =", self.a 
        print "self.b =", self.b
        print "self.c =", self.c
        print "a = ", a
        print "b = ", b
        print "c = ", c
        print "d = ", d
        print ""

print ""
print "a = ", a
print "b = ", b
print "c = ", c
print "d = ", d
print ""

z = Zigbee("z")

z.print_all()

z1 = Zigbee('z1',0, 1, 2)
z1.print_all()

z2 = Zigbee('z2', 100, 200, 300)
z2.print_all()

lh = []
print "lh :", lh
print "len(lh) :", len(lh)

lh.append(True)
print "lh :", lh
print "len(lh) :", len(lh)

print "------------------------------------------------------------"

lh.append((1, 2, 3))
print "lh :", lh
print "len(lh) :", len(lh)

lh.append((4, 
    5, 6, 
    'string', 
    'mac', 'type'))
print "lh :", lh
print "len(lh) :", len(lh)
print "lh[2][0] :", lh[2][0]
print "lh[2][1] :", lh[2][1]
print "lh[2][2] :", lh[2][2]
print "lh[2][3] :", lh[2][3]
print "lh[2][4] :", lh[2][4]
print "lh[2][5] :", lh[2][5]

print "------------------------------------------------------------"


edge = []

edge.append(((0,0,0),(1,2,2)))
#edge.append(((3,3,3),(5,5,5)))

print "edge :", edge
print "len(edge) :", len(edge)
print "edge[0] :", edge[0]

edges = []
edges.append(edge[0])

print "edges :", edges
print "len(edges) :",len(edges)

edges.append(((3, 3, 3),(5, 5, 5)))
print "edges :", edges
print "len(edges) :",len(edges)

print "------------------------------------------------------------"

edges.append([(9, 9, 9),(0, 0, 0)])
print "edges :", edges
print "len(edges) :",len(edges)

print "------------------------------------------------------------"

a = [0, 1, 2, 3, 4, 5, 6, 7]
b = [a[:]]
c = [dat for dat in a]
d = []
for dat in a:
    d.append(dat)

print "a : ", a
print "b : ", b
print "c : ", c
print "d : ", d

print "------------------------------------------------------------"

a = 0x0001
print "a : ", a

a <<= 1
print "a : ", a

ca = str(int('0') + a)
print "ca :", ca

s = ''
print "s :", s
s += ca
print "s :", s

print "------------------------------------------------------------"

a = [0, 1, 2, 3, 4, 5, 6, 7]
def print_unit(a, idx):
    print "a[%d] : %d" % (idx, a[idx]) 
    return a[idx]
b = []
[b.append(print_unit(a, idx)) for idx in range(8)]
print "b :", b

print "-------------------------------------------------------------"

print "hex(16) :", hex(16)
print "hex(0x0001) :", str(hex(0x0001))
print "hex(0x2001) :", hex(0x2001)
print "int('0x10', 16) :", int('0x10', 16)
print "int('10') :", int('10')
print "int('10', 16) :", int('10', 16)
print "int('0x10', 16) :", int('0x10', 16)
print "struct.unpack('<hh', bytes(b'\x01\x00\x00\x00')) :", struct.unpack('<hh', bytes(b'\x01\x00\x00\x00'))
print "struct.unpack('<L', bytes(b'\x01\x00\x00\x00')) :", struct.unpack('<L', bytes(b'\x01\x00\x00\x00'))
print "struct.pack('<HH', 1, 2) :", struct.pack('<HH', 1, 2)
print "struct.pack('<LL', 1, 2) :", struct.pack('<LL', 1, 2)

print "------------------------------------------------------------"

base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A')+6)]

def dec2hex(string_num):
    num = int(string_num)
    mid = []
    while True:
        if num == 0: break
        num ,rem = divmod(num, 16)
        mid.append(base[rem])
    print ""
    print "mid :", mid
    return ''.join([str(x) for x in mid[::-1]]) # Note:

print "dec2hex(100) :", dec2hex(100)
print "dec2hex(0x0100) :", dec2hex(0x0100)
print "------------------------------------------------------------"

# Note: {2 -> 0x02 | 10 -> 0x0A}
def byte2hex(num):
    base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A')+6)]
    mid = []
    if num > 0xff:
        num = 0xff
        print "out of range"
    while True:
        if num == 0: break
        num ,rem = divmod(num, 16)
        mid.append(base[rem])
    while len(mid) < 2: mid.append('0')
    return ''.join([str(x) for x in mid[::-1]]) # Note:

def mac2hex(mac):
    return ''.join([byte2hex(u) for u in mac])

# Note: {0x0102 -> str(0x0102)}
def short2hex(num):
    base = [str(x) for x in range(10)] + [chr(x) for x in range(ord('A'), ord('A')+6)]
    mid = []
    if num > 0xffff:
        num = 0xffff
        print "out of range"
    while True:
        if num == 0: break
        num ,rem = divmod(num, 16)
        mid.append(base[rem])
    while len(mid) < 4: mid.append('0')
    return ''.join([str(x) for x in mid[::-1]]) # Note:

print "byte2hex(1) :", byte2hex(1)
print "byte2hex(10) :", byte2hex(10)
print "byte2hex(256) :", byte2hex(256)

print "short2hex(0) :", short2hex(0)
print "short2hex(0x0100) :", short2hex(0x0100)
print "short2hex(0x010f) :", short2hex(0x010f)

print "mac2hex([1, 2, 3, 4, 5, 6, 7, 8]) :",mac2hex([1, 2, 3, 4, 5, 6, 7, 8])

print "------------------------------------------------------------"

a = '1234'
b = '0x'+a
print "a =", a
print "b =", b

a = 0
b = 0
c = 1

if a > 0 or b > 0:
    print "a > 0 or b > 0 : True"
else:
    print "a > 0 or b > 0 : False"

if a > 0 or c > 0:
    print "a > 0 or c > 0 : True"
else:
    print "a > 0 or c > 0 : False"

print "a + b :", a+b
print "a + c :", a+c

print "------------------------------------------------------------"

# Note: ((x, y, z), nwk, [0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08], 'C')
node = []
nodes = []

node.append((0, 0, 0))
node.append(short2hex(0x0102))
node.append(mac2hex([0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08]))
node.append('C')
nodes.append(tuple(node))

print "node :", node

node = []
node.append((0, 0, 1))
node.append(short2hex(0x0103))
node.append(mac2hex([0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09]))
node.append('R')
nodes.append(tuple(node))

node = []
node.append((0, 1, 2))
node.append(short2hex(0x0103))
node.append(mac2hex([0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x0a]))
node.append('R')
nodes.append(tuple(node))

node = []
node.append((0, 2, 3))
node.append(short2hex(0x0104))
node.append(mac2hex([0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x0b]))
node.append('R')
nodes.append(tuple(node))

print "nodes :", nodes
pprint(nodes)

nodestmp = {}
nodestmp['a'] = 1
nodestmp[(0, 0, 0)] = 'C'
print "bnodestmp :", nodestmp

nodestmp.clear()
def dictasignment(dic, u):
    dic[u[0]]=u[3]

[dictasignment(nodestmp, u) for u in nodes]
print "anodestmp :", nodestmp

nodestmp[(0, 0, 0)]='E'
print "anodestmp :", nodestmp

print "nodestmp[(0, 0, 0)] :", nodestmp[(0, 0, 0)]

print "------------------------------------------------------------"

def rets():
    s = "01234567"
    return s

print "rets() :", rets()
print "rets()[5:8] :", rets()[5:8]

print "------------------------------------------------------------"
print "range(8) :", range(8)

