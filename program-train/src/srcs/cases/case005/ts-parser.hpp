/*
 * Progarm Name: ts-parser.hpp
 * Created Time: 2017-06-22 13:22:23
 * Last modified: 2017-06-26 13:01:17
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_HPP_
#define _TS_PARSER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <list>
#include "ts-unit.hpp"
#include <array>
#include "ts-buffer.hpp"

using std::string;
using std::thread;
using std::list;
using std::array;

#define BUF_MAX_SIZE    (1024 * 1024 * 5)

class TsParser{
public:
    TsParser(string file = "");
    ~TsParser();
private:
    int  get_file_info(void);
    void load_data_loop(void);
    void parser(void);
private:
    string          m_file;
    int             m_fd         = -1;
    off_t           m_cur_offset = -1;
    off_t           m_filesize   = -1;
    TsBuffer       *m_tsbuf          = nullptr;
    thread         *m_ld_thread      = nullptr;
    thread         *m_parser_thread  = nullptr;
    list<TsUnit>    m_ts_units;
};

#endif //_TS_PARSER_HPP_

