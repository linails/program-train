/*
 * Progarm Name: stringTools.h
 * Created Time: 2016-05-26 19:47:33
 * Last modified: 2017-01-02 21:42:33
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STRINGTOOLS_H_
#define _STRINGTOOLS_H_

#include <string>
#include <vector>
#include <list>

using std::string;
using std::vector;
using std::list;

/*
 * stringTools 
 *  pattern 2: {"1hu, [123au], [123]-[123], [<]-[>]"}
 *  pattern 3: {'[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]-[^①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]'}
 * */
class stringTools{
public:
    stringTools(string str = "");
    ~stringTools();

    /*
     * filter/match success return 0
     *  pattern 2: {"1hu, [123au], [123]-[123], [<]-[>]"}
     *  pattern 3: {'[①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]-[^①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮]'}
     * */
    int  filter(const char *pattern2);
    int  filter(const char *pattern2, string &unit);
    int  filter(const char *pattern2, char *unit);
    int  match(const char *pattern, string &unit, int index=0);
    int  match(const char *pattern, char *unit, int index=0);
    int  match(const char *pattern, vector<string> &units);
    int  print_utf_code(string &s, int mode = 0);   // mode : [0/bin | 1/hex]
    int  print_utf_code(const char *str, int mode = 0);
    int  split_utf_code(vector<string> &result, string s = "");
private:
    int  get_pattern_mode(const char *pattern);
    int  get_subpatterns(const char *pattern);
    int  count_char(const char *str, char ch);
    int  parser_utf_code(vector<vector<unsigned char> > &vvch, string &s);
    int  parser_utf_code(vector<vector<unsigned char> > &vvch, const char *str);
    int  parser_utf_code(list<vector<unsigned char> > &lvch, string &s);
    int  parser_utf_code(list<vector<unsigned char> > &lvch, const char *str);
    void mfilter(vector<vector<unsigned char> > &vvch, unsigned char tag);
    void mfilter(vector<vector<unsigned char> > &vvch, const char *tag);
    void mfilter(vector<vector<unsigned char> > &vvch, vector<unsigned char> &tag);
    void mfilter(vector<vector<unsigned char> > &vvch, vector<vector<unsigned char> > &tag);
private:
    string              m_str;
    string              m_pattern;
    vector<string>      m_subpatterns;
};

#endif //_STRINGTOOLS_H_

