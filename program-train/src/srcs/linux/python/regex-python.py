#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-12-17 14:01:17
# Last modified: 2016-12-17 22:18:59
# 

import re

def regex_0():
    pattern = 'this'
    text = 'Does this text match the pattern?'

    match = re.search(pattern, text)

    # start() 和 end() 方法可以给出字符串中的相应索引
    s = match.start()
    e = match.end()

    print 'Found "%s"\nin "%s"\nfrom %d to %d ("%s")' %\
            (match.re.pattern, match.string, s, e, text[s:e])

regex_0()

def parser_dic():
    text = "得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46"

    pattern = "^\\w+?[^`]"

    match = re.search(pattern, text)
    s = match.start()
    e = match.end()

    print "match pattern : ", match.re.pattern
    print "match string : " , match.string

#parser_dic()

def string_patterns(string, patterns=[]):
    for pattern, desc in patterns:
        print 'Pattern %r (%s)\n' % (pattern, desc)
        print '  %s' % string
        for match in re.finditer(pattern, string):
            s = match.start()
            e = match.end()
            substr = string[s:e]
            n_backslashes = string[:s].count('\\')
            prefix = '.' * (s + n_backslashes)
            print '=>%s%s' % (prefix, substr)
        print
    return

string_patterns(
        'abbaaabbbbaaaa',
        [('ab', "'a' followed by 'b'")]
        )

string_patterns(
        "得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)",
        #"(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46",
        #"得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46",
        [('(\(\d\)).+(?=\(\d\)|(\(\d\)).+$)', "read char")]
        #[('^\\w+?[^`]', "read char")]
        #[('^[^`]{0,6}', "read char")]
        )

def regex_patterns(string, patterns=[]):
    for pattern, desc in patterns:
        print 'Pattern %r (%s)\n' % (pattern, desc)
        print '  %s' % string
        s = 0
        for match in re.finditer(pattern, string[s:]):
            s += match.start()
            e = match.end()
            substr = string[s:e]
            n_backslashes = string[:s].count('\\')
            prefix = '.' * (s + n_backslashes)
            print '=>%s%s' % (prefix, substr)
        print
    return

regex_patterns(
        #"得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)",
        #"(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46",
        "得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46",
        [('(\(\d\)).+(?=\(\d\)|(\(\d\)).+$)', "read char")]
        #[('^\\w+?[^`]', "read char")]
        #[('^[^`]{0,6}', "read char")]
        )
