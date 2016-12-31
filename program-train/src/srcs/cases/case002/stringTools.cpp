/*
 * Progarm Name: stringTools.cpp
 * Created Time: 2016-05-26 19:47:27
 * Last modified: 2016-12-29 21:20:47
 * @author: minphone.linails linails@foxmail.com 
 */

#include "stringTools.h"
#include "regex_common.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using std::cout;
using std::endl;

stringTools::stringTools(std::string str)
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

    auto match_mode3 = [this](const char *pattern, vector<string> &units){
        const char * pair_l = pattern;
        const char * pair_r = pattern; while(*pair_r++ != ']');

        string start(pair_l++ + 1, pair_r++ - 1); while(*pair_l++ != '['); while(*pair_r++ != ']');
        string end;

        if(0 == this->count_char(pattern, '^')){
            string str(pair_l - 1 + 1, pair_r - 1); end = str;
        }else{
            string str(pair_l - 1 + 2, pair_r - 1); end = str;
        }

        //cout << "start : " << start << " - size : " << start.size() << endl;
        //cout << "end : " << end << " - size : " << end.size() << endl;


        /* 
         * split utf code of start & end & this->m_str
         * */
        vector<string> vstart;
        vector<string> vend;
        vector<string> vstr;

        this->split_utf_code(vstart, start);
        this->split_utf_code(vend, end);
        this->split_utf_code(vstr, this->m_str);


        /*
         * get units
         * */

        auto check = [](vector<string> &chk, string &u){
            for(auto &c : chk) if(c == u) return 1; return 0;
        };

        auto check_start = [&vstart, &check](string &u){ return check(vstart, u); };
        auto check_end   = [&vend,   &check](string &u){ return check(vend, u); };

        for(auto iter = vstr.begin();
                 iter!= vstr.end(); iter++){

            /* get start index */
            auto iterfs = find_if(iter, vstr.end(), check_start);
            if(iterfs != vstr.end()){
                /* get end index */
                auto iterfe = find_if(iterfs+1, vstr.end(), check_end);

                vector<string> vtmp(iterfs, iterfe);
                string result;
                for(auto &vs : vtmp){ result += vs; }
                units.push_back(result);

                if(iterfe != vstr.end()){
                    iter = --iterfe;
                }else{
                    break;
                }
            }else{
                vector<string> vtmp(iter, iterfs);
                string result;
                for(auto &vs : vtmp){ result += vs; }
                units.push_back(result);

                break;
            }

        }
    };

    switch(mode){
        case 1:
            cout << "mode : " << mode << endl;
            break;
        case 2:
            cout << "mode : " << mode << endl;
            break;
        case 3 :
            match_mode3(pattern, units);
            break;
        default:
            cout << "mode : " << mode << endl;
            break;
    }

    return ret;
}

/* 
 * mode : [0/bin | 1/hex]
 * */
int  stringTools::print_utf_code(string &s, int mode)
{
    int ret = 0;

    auto print_utf_v = [](vector<unsigned char> &vch, int mode){
        string s;

        if(0 == mode) cout << "0b : ";
        else          cout << "0x : ";
        

        for(auto ch : vch){
            if(0 == mode){
                for(int i=0; i<8; i++){
                    if(ch & (0x01 << (7-i))) cout << "1";
                    else                     cout << "0";
                }
            }else{
                printf("%.2x", ch);
            }
            cout << "-";
            s.push_back(ch);
        }
        cout << s << endl;
    };

    vector<vector<unsigned char> > vvch;

    ret = this->parser_utf_code(vvch, s);

    for(auto &u : vvch) print_utf_v(u, mode);

    return ret;
}

int  stringTools::print_utf_code(const char *str, int mode)
{
    int ret = 0;

    string s(str);
    ret = this->print_utf_code(s, mode);

    return ret;
}

int  stringTools::split_utf_code(vector<string> &result, string s)
{
    int ret = 0;

    vector<vector<unsigned char> > vvch;

    if(true == s.empty()){
        ret = this->parser_utf_code(vvch, this->m_str);
    }else{
        ret = this->parser_utf_code(vvch, s);
    }

    string st;
    for(auto &u : vvch){
        st.clear();
        for(auto ch : u) st.push_back(ch);
        result.push_back(st);
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
                //cout << "count_char '[' : " << 2 << endl;
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

int  stringTools::parser_utf_code(vector<vector<unsigned char> > &vvch, string &s)
{
    int ret = 0;

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

    vector<unsigned char> vch;

    for(auto ch : s){

        unsigned char c = ch;
        /* 
         *    1 byte : 0xxxxxxx
         *    2 byte : 110xxxxx 10xxxxxx
         * */

        if(0 == (c & 0x80)){            // ascii

            if(true != vch.empty()) vvch.push_back(vch);

            vch.clear();
            vch.push_back(c);

        }else if(0xc0 == (c & 0xc0)){   // first byte of 2-6 bytes

            if(true != vch.empty()) vvch.push_back(vch);

            vch.clear();
            vch.push_back(c);

        }else{
            vch.push_back(c);
        }

    }

    vvch.push_back(vch);

    return ret;
}

