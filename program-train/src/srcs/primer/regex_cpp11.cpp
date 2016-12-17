/*
 * Progarm Name: regex_cpp11.cpp
 * Created Time: 2016-06-16 11:24:06
 * Last modified: 2016-12-17 20:36:44
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "regex_cpp11.h"

/*gcc-5.3*/
/*c++11 regex*/
#include <regex>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using std::endl;
using std::cout;
using std::map;
using std::regex;
using std::sregex_token_iterator;
using std::smatch;

/*
 * 正则表达式 总结:
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [正则表达式的限定符]
 *  1> *    : 匹配前面的子表达式零次或多次，例如：zo* 能匹配 "z" 以及 "zoo" , * 等价于 {0, }
 *  2> +    : 匹配前面的子表达式一次或多次, 例如：'zo+' 能匹配 "zo" 以及 "zoo", 但不能匹配 "z", + 等价于 {1, }
 *  3> ?    : 匹配前面的子表达式零次或一次, 例如："do(es)?" 可以匹配 "do" 或 "does" 中的 "do" , ? 等价于 {0, 1}
 *  4> {n}  : n 是一个非负整数，匹配确定的 n 次，例如：'o{2}' 不能匹配 'Bob' 中的 'o', 但能匹配 'food' 中的 'oo'
 *  5> {n,} : n 是一个非负整数，至少匹配 n 次，例如：'o{2,}' 不能匹配 'Bob' 中的 'o', 但等匹配 'fooooood' 中的所有 'o'
 *  6> {n,m}: m 和 n 都是非负整数，其中 n<=m, 最少匹配 n 次且最多匹配 m 次，例如：'o{1,3}' 将匹配 'fooooood' 中的前三个 'o'
 *            'o{0,1}' 等价于 'o?' | 逗号和两个数之间不能有空格
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [1.常用的元字符]
 *  1> .    : 匹配除换行符以外的任意字符
 *  2> \w   : 匹配字母或数字或下划线或汉字
 *  3> \s   : 匹配任意的空白符
 *  4> \d   : 匹配数字
 *  5> \b   : 匹配单词的开始或结束
 *  6> ^    : 匹配字符串的开始
 *  7> $    : 匹配字符串的结束
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [2.常用的限定符]
 *  1> *    : 重复零次或更多次
 *  2> +    : 重复一次或更多次
 *  3> ?    : 重复零次或一次
 *  4> {n}  : 重复 n 次
 *  5> {n,} : 重复 n 次或更多次
 *  6> {n,m}: 重复 n 到 m 次
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [3.常用的反义代码]
 *  1> \W   : 匹配任意不是字母，数字，下划线，汉字的字符
 *  2> \S   : 匹配任意不是空白符的字符
 *  3> \D   : 匹配任意非数字的字符
 *  4> \B   : 匹配不是单词开头或结束的位置
 *  5> [^x] : 匹配除了 x 以外的任意字符
 *  6> [^aeiou] : 匹配除了 aeiou 这几个字母以外的任意字符
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [4.常用的分组语法]
 *  1> (exp)        : [捕获] 匹配 exp, 并捕获文本到自动命名的组里
 *  2> (?<name>exp) : [捕获] 匹配 exp, 并捕获文本到名称为 name 的组里，也可以写成 (?'name'exp)
 *  3> (?:exp)      : [捕获] 匹配 exp, 不捕获匹配的文本，也不给此分组分配组号
 *  4> (?=exp)      : [零宽断言] 匹配 exp 前面的位置
 *  5> (?<=exp)     : [零宽断言] 匹配 exp 后面的位置
 *  6> (?!exp)      : [零宽断言] 匹配后面跟的不是 exp 的位置
 *  7> (?<!exp)     : [零宽断言] 匹配前面不是 exp 的位置
 *  8> (?#comment)  : 注释
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [5.懒惰限定符]
 *  1> *?     : 重复任意次，但尽可能少重复
 *  2> +?     : 重复 1 次或更多次，但尽可能少重复
 *  3> ??     : 重复 0 次或 1 次，但尽可能少重复
 *  4> {n,m}? : 重复 n 到 m 次，但尽可能少重复
 *  5> {n,}?  : 重复 n 次以上，但尽可能少重复
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * [6.常用的处理选项]
 *  1> IgnoreCase   : 匹配时不区分大小写
 *  2> Multiline    : 更改 ^ 和 $ 的含义，使它们分别在任意一行的行首和行尾匹配，而不仅仅在整个
 *                    字符串的开头和结尾匹配，(在此模式下，$ 的精确含义是：匹配 \n 之前的位置
 *                    以及字符串结束前的位置)
 *  3> Singleline   : 更改 . 的含义，使它与每个字符匹配(包括换行符 \n)
 *  4> IgnorePatternWhitespace : 忽略表达式中的非转义空白并启用由 # 标记的注释
 *  5> ExplicitCapture  : 仅捕获已被显示命名的组
 *
 * */

regex_cpp11::regex_cpp11()
{
}

regex_cpp11::~regex_cpp11()
{
}

void regex_cpp11::regex_t4(void)
{
    {
        cout << "---------------------------------------------------------" << endl;
        string pattern("[^c]ei");
        pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

        regex r(pattern);
        smatch results;

        string test_str("receipt freind theif receive");
        if(regex_search(test_str, results, r)){
            cout << results.str() << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;
        /*
         * reference : cnblogs.com/zhuyp1015/archive/2012/04/08/2438215.html
         * */

        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

        string email1("marius.bancila@domain.com");
        string email2("mariusbancila@domain.com");
        string email3("marius_b@domain.co.uk");
        string email4("marius@domain");

        cout << email1 << " : " << (regex_match(email1,pattern) ? "valid" : "invalid") << endl;
        cout << email2 << " : " << (regex_match(email2,pattern) ? "valid" : "invalid") << endl;
        cout << email3 << " : " << (regex_match(email3,pattern) ? "valid" : "invalid") << endl;
        cout << email4 << " : " << (regex_match(email4,pattern) ? "valid" : "invalid") << endl;
    }
    {
        cout << "---------------------------------------------------------" << endl;
        string str("亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓");

        cout << "string : " << str << endl;

        const regex pattern("`\\d`");
        smatch      result;

        bool regbool = regex_search(str, result, pattern);

        cout << "regex search: " << (regbool ? "true" : "false") << endl;

        if(true == regbool){
            cout << "result : " << result.str() << endl;
        }

        str = "`1`";

        regbool = regex_match(str,pattern);
        cout << "regex match : " << (regbool ? "true" : "false") << endl;
    }
    {
        cout << "---------------------------------------------------------" << endl;
        /*
         * reference : cnblogs.com/zhuyp1015/archive/2012/04/08/2438232.html
         * */
        regex pattern("\\w+day");

        string weekend("Saturday and Sunday, but some Fridays also.");
        sregex_token_iterator end;

        for(sregex_token_iterator i(weekend.begin(), weekend.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
        }
    }

    string str("亶1	`1`亶1`2`dǎn<br>(1)<br>(形声。本义:谷多)<br>(2)<br>同本义 [full of grains]<br>亶,多谷也。――《说文》<br>择三有事,亶侯多藏。――《诗·小雅·十月之交》<br>(3)<br>厚道;忠实 [kind and sincere]<br>亶,信也;又,诚也。――《尔雅》<br>不实于亶。――《诗·大雅·板》<br>(4)<br>又如:亶厚(忠厚,淳厚);亶诚(真诚)<br>(5)<br>平坦;广大 [smooth]。如:亶亶(平坦。通“坦坦”)<br>(6)<br>姓");
    {
        cout << "---------------------------------------------------------" << endl;

        const char pastr[] = "`\\d`[^<]{0,4}";
        regex pattern(pastr);
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;

        regex pattern("^[^`]{1,5}");
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;

        regex pattern("\\(\\d\\)[^\\(]+");
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;

            vector<string> subunits;
            sregex_token_iterator subend;
            regex subpattern("<br>[^<]+");
            for(sregex_token_iterator i(iter->begin(), iter->end(), subpattern); i!=subend; ++i){
                subunits.push_back(*i);
            }
            for(auto iiter = subunits.begin();
                     iiter!= subunits.end(); iiter++){
                cout << "iiter : " << *iiter << endl;
            }
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;

        regex pattern("br(?=>\\(\\d\\))");
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;
        }
    }
    {
        cout << "---------------------------------------------------------" << endl;

        regex pattern("(\\(\\d\\)){1}.+?(?=>\\(\\d\\))|\\(\\d\\).*");
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;

            vector<string> subunits;
            sregex_token_iterator subend;
            regex subpattern("<br>[^<]+");
            for(sregex_token_iterator i(iter->begin(), iter->end(), subpattern); i!=subend; ++i){
                subunits.push_back(*i);
            }
            for(auto iiter = subunits.begin();
                     iiter!= subunits.end(); iiter++){
                cout << "iiter : " << *iiter << endl;
            }

        }
    }
    {
        cout << "---------------------------------------------------------" << endl;

        string s("得出	`1`得出`2`déchū<br>(1)<br>[reach;obtain;arrive]∶获得;达到<br>他得出这个结论是多次考虑的结果<br>(2)<br>[confirm (a calculation,etc.)]∶算出<br>计算了这道题得出答案为46");

        regex pattern("^[^`]{0,6}");
        sregex_token_iterator end;

        vector<string> units;

        for(sregex_token_iterator i(str.begin(), str.end(), pattern); i!=end; ++i){
            cout << "*i : " << *i << endl;
            units.push_back(*i);
        }
        for(auto iter = units.begin();
                 iter!= units.end(); iter++){
            cout << "iter : " << *iter << endl;

            vector<string> subunits;
            sregex_token_iterator subend;
            regex subpattern("<br>[^<]+");
            for(sregex_token_iterator i(iter->begin(), iter->end(), subpattern); i!=subend; ++i){
                subunits.push_back(*i);
            }
            for(auto iiter = subunits.begin();
                     iiter!= subunits.end(); iiter++){
                cout << "iiter : " << *iiter << endl;
            }
        }
    }
}

int  regex_cpp11::regex_base(void)
{
    int ret = 0;

    auto print_contents = [](string &s, vector<string> &uints){
        cout << endl;
        cout << "s : " << s << endl;

        cout << "u : " << endl;
        int i = 0;
        for(auto &u : uints){
            printf(" %d> %s\n", ++i, u.c_str());
        }
    };

    {
        string s("Is is the cost of of gasoline going up up of Of?");
        vector<string> units;

        /* 
         * regex  : "\b([a-z]+) \1\b"
         * string : "\\b([a-z]+) \\1\\b"
         *
         * 捕获的表达式，如 [a-z]+ 指定的，包括一个或多个字母
         * 表达式的第二部分是对以前捕获的子匹配项的引用，\1 表示第一个子匹配项 [a-z]+
         * */
        this->regex_common_c0x("\\b([a-z]+) \\1\\b", s, units);

        print_contents(s, units);
    }

    return ret;
}

/*regex c++11 - common - success return 0*/
int  regex_cpp11::regex_common_c0x(const char *pattern, string &contents, vector<string> &units)
{
    regex   patterns(pattern);
    sregex_token_iterator   end;

    for(sregex_token_iterator i(contents.begin(), contents.end(), patterns);
            i != end; ++i){
        units.push_back(*i);
    }

    if(true == units.empty()) return -1;

    return 0;
}


