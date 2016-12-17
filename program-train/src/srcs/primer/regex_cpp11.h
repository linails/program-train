/*
 * Progarm Name: regex_cpp11.h
 * Created Time: 2016-06-16 11:24:12
 * Last modified: 2016-12-17 22:45:37
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#ifndef _REGEX_CPP11_H_
#define _REGEX_CPP11_H_

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;

struct regex_cpp11{
    regex_cpp11();
    ~regex_cpp11();
    void regex_t4(void);
    int  regex_base(void);
private:
    int  regex_common_c0x(const char *pattern, string &contents, vector<string> &units);
    int  regex_split(string s, void (*fp)(string &, vector<string> &));
};

#endif //_REGEX_CPP11_H_

