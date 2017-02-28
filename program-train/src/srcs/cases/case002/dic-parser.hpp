/*
 * Progarm Name: dic-parser.hpp
 * Created Time: 2016-12-15 22:09:32
 * Last modified: 2017-02-28 16:38:28
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DIC_PARSER_HPP_
#define _DIC_PARSER_HPP_

#include <string>
#include "disk-dic.hpp"

using std::string;

class DicParser{
public:
    DicParser();
    ~DicParser();
    int  dicparser_main(int argc, char **argv);
private:
    int  init(int argc, char **argv);
    int  uninit(void);
    int  parser_xhzd(int argc, char **argv);
    int  parser_xdhycd(int argc, char **argv);
    int  parser_cycd(int argc, char **argv);
    int  parser_hycddq(int argc, char **argv);
    int  parser_hytycfyccd(int argc, char **argv);
private:
    DiskDic    *m_disk = nullptr;
    string      m_db   = "/home/minphone/corpus-db";
};

#endif //_DIC_PARSER_HPP_

