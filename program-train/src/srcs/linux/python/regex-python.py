#! /usr/bin/python
# -*- coding: UTF-8 -*-
# Created Time: 2016-12-17 14:01:17
# Last modified: 2016-12-25 21:25:59
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
            #prefix = '.' * (s + n_backslashes)
            #print '=>%s%s' % (prefix, substr)
            print "substr : %s - %d" % (substr, len(substr))
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

regex_patterns(
        '卫冕	<font size=+2 color="red">[卫冕]</font>wèimiǎn动指竞赛中保住上次获得的冠军称号：～成功|男子篮球队能否～，就看这场比赛了。\n',
        [('^.[^*<\s]+', "read char")]
        )

regex_patterns(
        '的	*<font size=+2 color="red">的</font>1·de助①用在定语的后面。a)定语和中心词之间是一般的修饰关系：铁～纪律｜幸福～生活。b)定语和中心词之间是领属关系：我～母亲｜无产阶级～党|大楼～出口。c)定语是人名或人称代词，中心词是表示职务或身份的名词，意思是这个人担任这个职务或取得这个身份：今天开会是你～主席｜谁～<font size=+1 color="green">介</font>绍人?d)定语是指人的名词或人称代词，中心词和前边的动词合起来表示一种动作，意思是这个人是所说的动作的受事：开他～玩笑｜找我～麻烦。②用来构成没有中心词的“的”字结构。a)代替上文所说的人或物：这是我～，那才是你～｜菊花开了，有红～，有黄～。b)指某一种人或物：男～｜送报～｜我爱吃辣～。c)表示某种情况、原因：大星期天～，你怎么不出去玩儿玩儿?｜无缘无故～，你着什么急?d)用跟主语相同的人称代词加“的”字做宾语，表示别的事跟这个人无关或这事儿跟别人无关：这里用不着你，你只管睡你～去。e)“的”字前后用相同的动词、<font size=+1 color="green">形</font>容词等，<font size=+1 color="green">连</font>用这样的结构，表示有这样的，有那样的：推～推，拉～拉｜说～说，笑～笑｜大～大，小～小。③用在谓语动词后面，强调这动作的施事者或时间、地点、方式等：谁买～书?｜他是昨天进～城｜我是在车站打～票|老张是用毛笔～信。注意(这个用法限于过去的事情。④用在陈述句的末尾，表示肯定的语气：这件事儿我知道～。⑤用在两个同类的词或词组之后，表示“等等、之类”的意思：破铜烂铁～，他捡来一大筐｜老乡们沏茶倒水～，待我们很亲热。⑥〈口〉用在两个数量词中间。a)表示相乘：这间屋子是五米～三米，合十五平方米。b)表示相加：两个～三个，一共五个。\n',
        #[('>.+?[<\]', "read char")]
        [('>.+?<|>.+?$', "read char")]
        )

