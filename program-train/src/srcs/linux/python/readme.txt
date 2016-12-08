# readme.txt
# Created Time: 2016-08-30 14:10:55
# Last modified: 2016-10-19 13:06:42
#

01.python3不支持``反引号，所有使用反引号的都使用repr函数进行替代 : repr() 表示返回值的字符串表示形式
02.平常的输入一般使用 raw_input() ; input() 是把输入当作python表达式
03.abs() 返回数字的绝对值
04.cmath.sqrt() 返回平方根，也可以应用于负数
05.float() 将字符串或数字转换为浮点数
06.round() 四舍五入
07.几乎所有的情况都使用列表替代元组，只在字典的键中使用元组
08.所有序列类型都可以进行某些特定的操作：索引(indexing)、分片(sliceing)、加(adding)、乘(multiplying)、
  以及检查某个成员是否  是序列成员
09.索引使用负数时，则从序列右边开始计数，第一个为-1
10.用 in 来检查一个值是否在序列中
11.append()  : 用于在列表末尾追加新的对象
12.count()   : 用于统计某个元素在列表中出现的次数
12.extend()  : 用于在列表末尾一次性追加另一个序列中的多个值
13.index()   : 查找某个值第一个匹配项的索引位置
14.insert()  : 将对象插入到列表中
15.pop()     : 移除列表中的最后一个元素，并返回该元素的值
16.remove()  : 移除列表中的某个值的第一个匹配项
17.reverse() : 列表中的所有元素顺序反转，变成逆序
18.sort()    : 排序
19.元组是通过圆括号括起来的
20.tuple()   : 与list函数基本一样，以一个序列作为参数并把它转换为元组
21.string 模块提供另外一种格式化值的方法：
   模板字符串；substitute 这个模板方法会用传递进来的关键字参数 foo 来替换字符串中的 $foo
22.非常有用的字符串方法：
   string.digits : 包含数字0~9的字符串
   string.letters: 包含所有字母(大写或小写)的字符串
   string.lowercase: 包含所有小写字母的字符串
   string.printable: 包含所有可打印字符的字符串 
   string.punctuation: 包含所有标点的字符串
   string.uppercase: 包含所有大写字母的字符串

   find() : 可以在一个较长的字符串中查找子字符串
   join() : 是非常重要的字符串方法，是split方法的逆运算，用来在队列中添加元素
   lower() : 返回字符串的小写字母版
   replace() : 返回某字符串的所有匹配项均被替换之后得到的字符串
   split() : 非常重要的字符串方法，是join的逆运算，用来将字符串分割成序列
   strip() : 返回去除两侧空格的字符串(不包括内部)
23.字典是python中唯一的内建映射类型
24.import somemodule
   from somemodule import somefunction
   from somemodule import somefunction. anotherfunction. yetanotherfunction
   from somemodule import * :要导入所有功能的时候，使用这个版本
   import math as foobar : 在句末尾增加一个as子句，为整个模块提供别名 ，也可以为函数提供别名
25.bool 函数可以用来转换其他值到bool值，不常用，因为python会自动转换
26.表达式的列表推导式：
   [表达式 for 变量 in 列表]
           for 变量 in 列表    <- 这个部分可以重复多次
   [表达式 for 变量 in 列表 if 条件]
           for 变量 in 列表 if 条件    <- 这个部分可以重复多次
27.python中的魔法方法__init__是用的最多的，析构函数__del__不建议使用
28.__metaclass__ = type #定义这个表示后面定义的类是新式的类
29.super(B, self).__init__() #只在新类中使用，或者是python3.0中
30.def __init__(self): 构造函数
   def __len__(self):
   def __getitem__(self, key):
   def __setitem__(self, key, value):
   def __delitem__(self, key):
31.property函数的4个参数分别被叫做：fget、fset、fdel和doc--
32.下面的值在作为布尔表达式的时候，会当作 false
   False  None  0   ""  ()  []  {}
   总结：空和假都是 false
33.if - elif - else
34.python中的比较运算符
   x == y
   x < y
   x > y
   x >= y
   x <= y
   x != y
  -------------------
   x is y      :x 和 y 是同一个对象
   x is not y  :x 和 y 是不同的对象
   x in y      :x 是 y 容器的成员
   x not in y  :x 不是 y 容器的成员
  -------------------
  运算符可以连用：eg. 0 < age < 100

35. not / and / or
36.for / while 循环都可以使用 continue / break / else 子句
37.hasattr(func, __call__) 判断函数是否可被调用
   callable() python2中可以使用
38.
39.
40.

#--------------------------------------------------------------------------
01.import sys
  sys.path.append('/home/yourusername/python')
  这个只是告诉解释器，除了从默认的目录中寻找之外，还需要从目录'/home/yourusername/python'中寻找模块
  完成这个步骤之后，就可以导入自己的模块了
02.sys.platform :系统平台
03.sys.argv[0] #argv[0] is python script name
04.import time
  time.sleep(1)
  time.sleep(0.01)
05.
06.
07.
08.
