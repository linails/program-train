/*
 * Progarm Name: ts-parser.hpp
 * Created Time: 2017-06-22 13:22:23
 * Last modified: 2017-06-22 13:29:55
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_HPP_
#define _TS_PARSER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>

using std::string;

class TsParser{
public:
    TsParser(string file = "");
    ~TsParser();
private:
    string          m_file;
};

#endif //_TS_PARSER_HPP_

