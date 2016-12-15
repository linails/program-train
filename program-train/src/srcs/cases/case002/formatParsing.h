/*
 * Progarm Name: formatParsing.h
 * Created Time: 2016-05-15 12:14:15
 * Last modified: 2016-12-15 22:56:41
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FORMATPARSING_H_
#define _FORMATPARSING_H_

#include <string>
#include <vector>

/*for c callback*/
extern int formatPrint(std::string fname,std::string line);

class formatTool{
public:
    formatTool(std::string fname,std::string line);
    ~formatTool();
private:
    void formatParsing_cycd(std::string &s);      /*for 成语词典*/
    void formatParsing_hycddq(std::string &s);    /*for 汉语词典大全*/
    void formatParsing_hytycfyccd(std::string &s);/*for 汉语同义词反义词词典*/
    void formatParsing_xdhycd(std::string &s);    /*for 现代汉语词典*/
    void formatParsing_xhzd(std::string &s);      /*for 新华字典*/
private:
    typedef std::vector<std::vector<std::string> > ContentsType_t; 
    typedef struct{
        std::string             word;       //亶
        std::vector<std::string>attr;       //1 , dǎn
        ContentsType_t          contents;   //(形声。本义:谷多) , 同本义 [full of grains] ... 
    }WordCell_t;
private:
    static const char *fnameList[];
    static void (formatTool::*formatParsingList[])(std::string &);
    std::string m_fname;
    std::string m_line;
    WordCell_t  m_wc;
};

#endif //_FORMATPARSING_H_

