/*
 * Progarm Name: formatParsing.h
 * Created Time: 2016-05-15 12:14:15
 * Last modified: 2016-12-17 23:52:34
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FORMATPARSING_H_
#define _FORMATPARSING_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

/*for c callback*/
extern int formatPrint(string fname, string line);

typedef vector<vector<string> > ContentsType_t; 

typedef struct{
    string             word;       //亶
    vector<string>     attr;       //1 , dǎn
    ContentsType_t     contents;   //(形声。本义:谷多) , 同本义 [full of grains] ... 
}WordCell_t;

class formatTool{
public:
    formatTool(string fname, string line);
    ~formatTool();
    int  get_wordcell(WordCell_t &wc);
private:
    void formatParsing_cycd(string &s);      /*for 成语词典*/
    void formatParsing_hycddq(string &s);    /*for 汉语词典大全*/
    void formatParsing_hytycfyccd(string &s);/*for 汉语同义词反义词词典*/
    void formatParsing_xdhycd(string &s);    /*for 现代汉语词典*/
    void formatParsing_xhzd(string &s);      /*for 新华字典*/
    int  regex_split(string &s, vector<string> &units);
private:
    static const char *fnameList[];
    static void (formatTool::*formatParsingList[])(string &);
    string m_fname;
    string m_line;
    WordCell_t  m_wc;
};

#endif //_FORMATPARSING_H_

