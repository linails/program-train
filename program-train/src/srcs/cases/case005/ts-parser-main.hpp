/*
 * Progarm Name: ts-parser-main.hpp
 * Created Time: 2017-06-21 15:22:28
 * Last modified: 2017-06-22 13:21:01
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_MAIN_HPP_
#define _TS_PARSER_MAIN_HPP_

#include "cfg-loader.hpp"
#include "manager.hpp"
#include <string>

using std::string;

class TsParserMain{
public:
    TsParserMain();
    ~TsParserMain();
    int  main(void);
private:
    int  init(void);
    int  parser(void);
private:
    Manager        *m_mgr     = nullptr;
    CfgLoader      *m_xml_cfg = nullptr;
    string          m_ts_path;
};

#endif //_TS_PARSER_MAIN_HPP_

