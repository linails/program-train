/*
 * Progarm Name: stringTools.cpp
 * Created Time: 2016-05-26 19:47:27
 * Last modified: 2016-12-27 23:52:40
 * @author: minphone.linails linails@foxmail.com 
 */

#include "stringTools.h"
#include "regex_common.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using std::cout;
using std::endl;

stringTools::stringTools(std::string &str)
    :m_str(str)
{
}

stringTools::stringTools(const char *str)
    :m_str(str)
{
}

stringTools::~stringTools()
{
}

/*filter success return 0
 *  pattern 2: {'1', '[1-9]', '[1-9]'}
 * */
int stringTools::filter(const char *pattern2, std::string &unit)
{
    this->get_subpatterns(pattern2);

    for(auto iter = this->m_subpatterns.begin();
             iter!= this->m_subpatterns.end(); iter++){
    }

    return 0;
}

/*filter success return 0
 *  pattern 2: {'1', '[1-9]', '[1-9]'}
 * */
int stringTools::filter(const char *pattern2, char *unit)
{
    int     ret = 0;
    string  sunit;
    
    if(0 == (ret = this->filter(pattern2,sunit))){
        for(auto iter = sunit.begin();
                 iter!= sunit.end(); iter++){
            *unit++ = *iter;
        }
    }

    return ret;
}

int stringTools::match(const char *pattern, string &unit, int index)
{
    int ret = 0;

    return ret;
}

int stringTools::match(const char *pattern, char *unit, int index)
{
    int ret = 0;

    return ret;
}

int stringTools::match(const char *pattern, vector<string> &units)
{
    int ret = 0;

    int mode = this->get_pattern_mode(pattern);

    cout << "mode = " << mode << endl;

    if(3 == mode){
        const char * pair_l = pattern;
        const char * pair_r = pattern; while(*pair_r++ != ']');

        string start(pair_l++ + 1, pair_r++ - 1); while(*pair_l++ != '['); while(*pair_r++ != ']');
        string end;

        if(0 == this->count_char(pattern, '^')){
            string str(pair_l - 1 + 1, pair_r - 1); end = str;
        }else{
            string str(pair_l - 1 + 2, pair_r - 1); end = str;
        }

        cout << "start : " << start << " - size : " << start.size() << endl;
        cout << "end : " << end << " - size : " << end.size() << endl;

        /* parser start & end */
        {
            vector<string> vstart;
            vector<string> vend;

            auto parser = [](vector<string> &dst, string &str){
                auto siter = str.begin();
                auto eiter = siter;
                while(eiter != str.end()){
                    eiter += 3;
                    string s(siter, eiter); siter = eiter;

                    dst.push_back(s);
                }

                //for(auto &s : dst){
                //    cout << "dst : " << s << endl;
                //}
            };

            parser(vstart, start);
            parser(vend, end);

            /* 
             * 编码格式为 utf-8
             *
             * utf-8 是 unicode 的实现方式之一
             * utf-8 最大的一个特点，就是它是一种变长的编码方式，它可以使用 1~6 字节来
             * 表示一个符号，根据不同的符号而变化字节长度
             *
             * 规则：(只有两条)
             *  1> 对于单字节的符号，字节的第一位设为0，后面7位为这个符号的 unicode 码，
             *     因此对于英语字母，utf-8 与 ascii 相同
             *  2> 对于 n 字节的符号(n>1), 第一个字节的前 n 位都设为1，第 n+1 位设为0，
             *     后面字节的前两位一律设置为 10，剩下的没有提及的二进制位，即为这个符号
             *     的 unicode 编码
             *
             *  eg .
             *    1 byte : 0xxxxxxx
             *    2 byte : 110xxxxx 10xxxxxx
             *    3 byte : 1110xxxx 10xxxxxx 10xxxxxx
             *    4 byte : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
             *    5 byte : 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
             *    6 byte : 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
             * */
            string hz("名词、动词、形容词、数词、量词、代词、副词、介词、连词、助词、叹词、拟声词");
            cout << "hz.size() : " << hz.size() << endl;
            for(size_t i=0; i<hz.size(); i++){
                if(0 == ((i+1) % 3)){
                    printf(" %.2x-%.2x-%.2x\n", hz[i-2], hz[i-1], hz[i]);
                }
            }

        }

        const char * index = this->m_str.c_str(); 

        pair_l = index;
        pair_r = index;

        while(*index != '\0'){

#if 0
            if(pair_r >= pair_l){
                for(size_t i=0; i<start.size(); i++){
                    if(start[i] == *index){
                        pair_l = index;
                        break;
                    }
                }
            }else{
                for(size_t i=0; i<end.size(); i++){
                    if(end[i] == *index){
                        pair_r = index;

                        string u(pair_l, pair_r);
                        cout << "u : " << u << endl;

                        break;
                    }
                }
            }
#endif

            index++;
        }

    }

    return ret;
}

/*success return pattern mode >= 0
 * mode :
 *    0) fixed string
 *    1) []
 *    2) fixed string & []
 *    3) []-[]
 * */
int stringTools::get_pattern_mode(const char *pattern)
{
    int ret = 0;

    string s(pattern);

    if(0 == s.size()){
        ret = -1;
    }else{

        switch(this->count_char(pattern, '[')){
            case 1:
                if(s[0] == '[' && s[s.size()] == ']'){
                    ret = 1;
                }else if(string::npos != s.find('[') && string::npos != s.find(']')){
                        ret = 2;
                }
                break;
            case 2:
                cout << "count_char '[' : " << 2 << endl;
                ret = 3;
                break;
        }
    }

    return ret;
}

/*get sub patterns success return 0*/
int stringTools::get_subpatterns(const char *pattern)
{
    int ret = 0;

    return ret;
}

int  stringTools::count_char(const char *str, char ch)
{
    int ret = 0;
#if 0
    const char *index = str;

    while(*index != '\0'){
        if(*index++ == ch){
            if(index - str < 2){
                ret++;
            }else if(*(index - 2) != '\\'){
                ret++;
            }
        }
    }
#else
    while(*str != '\0') if(*str++ == ch) ret++;
#endif

    return ret;
}

