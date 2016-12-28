/*
 * Progarm Name: stringTools.h
 * Created Time: 2016-05-26 19:47:33
 * Last modified: 2016-12-28 13:01:53
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STRINGTOOLS_H_
#define _STRINGTOOLS_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/*
 * stringTools 
 *  pattern 1: usual pattern
 *  pattern 2: {'1', '[1-9]', '[1-9]'}
 * */
class stringTools{
public:
    stringTools(string &str);
    stringTools(const char *str);
    ~stringTools();

    /*filter success return 0
     *  pattern 2: {'1', '[1-9]', '[1-9]'}
     *  pattern 3: {'[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]-[^①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]'}
     * */
    int  filter(const char *pattern2, string &unit);
    int  filter(const char *pattern2, char *unit);
    int  match(const char *pattern, string &unit, int index=0);
    int  match(const char *pattern, char *unit, int index=0);
    int  match(const char *pattern, vector<string> &units);
    int  print_utf_code(string &s, int mode = 0);   // mode : [0/bin | 1/hex]
    int  print_utf_code(const char *str, int mode = 0);
private:
    int  get_pattern_mode(const char *pattern);
    int  get_subpatterns(const char *pattern);
    int  count_char(const char *str, char ch);
private:
    string              m_str;
    string              m_pattern;
    vector<string>      m_subpatterns;
};

#endif //_STRINGTOOLS_H_

