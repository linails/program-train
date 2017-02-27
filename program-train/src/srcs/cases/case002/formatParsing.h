/*
 * Progarm Name: formatParsing.h
 * Created Time: 2016-05-15 12:14:15
 * Last modified: 2017-02-27 17:50:04
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FORMATPARSING_H_
#define _FORMATPARSING_H_

#include <string>
#include <vector>
#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

using std::string;
using std::vector;
using namespace cppjieba;

/*for c callback*/
extern int formatPrint(string fname, string line);

typedef vector<vector<string> > ContentsType_t; 

typedef struct{
    string             word;       //亶
    string             spell;      // dan
    vector<string>     attr;
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
    int  regex_split(vector<string> &patterns, string &s, vector<string> &units);
private:
    static const char *const DICT_PATH      ;
    static const char *const HMM_PATH       ;
    static const char *const USER_DICT_PATH ;
    static const char *const IDF_PATH       ;
    static const char *const STOP_WORD_PATH ;
    static const char *fnameList[];
    static const char *property_words[];
    static void (formatTool::*formatParsingList[])(string &);
    string      m_fname;
    string      m_line;
    WordCell_t  m_wc;
    //static Jieba jieba;
};

#endif //_FORMATPARSING_H_

