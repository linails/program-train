#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-11-02 10:28:22
# Last modified: 2016-12-01 20:59:59
# 

from pprint import pprint

def print_dic():
    print "-------------------------------------------------------------";
    print "print_dic ... ";
    params = {"server":"mmmmmm", "database":"nnnnnn", "uid":"ssssss", "pwd":"wwwwww"};

    params.keys();
    pprint(params.keys());

    params.values();
    pprint(params.values());

    params.items();
    pprint(params.items());

print_dic();
#-------------------------------------------------------------

# 第三方库
# info 函数的设计意图是提供给工作在 python IDE中的开发人员使用

# def print_info():
#     li = [];
#     info(li);

# print_info();

#-------------------------------------------------------------

def print_type():
    # type 函数返回任意对象的数据类型
    print "-------------------------------------------------------------";
    li = [];
    print "type(li)", type(li);
    print "type(1)", type(1);
    print "type(pprint)", type(pprint);

print_type();

#-------------------------------------------------------------

def print_str():
    # str 函数将数据强制转换为字符串，每种数据类型都可以强制转换为字符串
    print "-------------------------------------------------------------";
    print "str(1)", str(1)
    params = {"server":"mmmmmm", "database":"nnnnnn", "uid":"ssssss", "pwd":"wwwwww"};
    print "str(params)", str(params)
    print "str(None)", str(None);

print_str();

#-------------------------------------------------------------

def print_div():
    # div 函数用于返回任意对象的属性和方法列表，包括模块对象、函数对象、字符串对象、
    # 列表对象、字典对象......相当多的东西
    print "-------------------------------------------------------------";
    li = []
    print "dir(li) :", dir(li)
    params = {}
    print "dir(params) :", dir(params)

print_div();

