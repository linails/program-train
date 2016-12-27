/*
 * Progarm Name: stringTools.cpp
 * Created Time: 2016-05-26 19:47:27
 * Last modified: 2016-12-27 13:02:35
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

