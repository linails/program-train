/*
 * Progarm Name: ts-parser.hpp
 * Created Time: 2017-06-22 13:22:23
 * Last modified: 2017-06-27 17:09:33
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_HPP_
#define _TS_PARSER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include "ts-unit.hpp"
#include "ts-buffer.hpp"

using std::string;
using std::thread;
using std::mutex;
using std::recursive_mutex;
using std::queue;

struct TsBuffer;
class  TsUnit;
class  TsPAT;
class  TsPMT;
class  TsPES;

#define BUF_MAX_SIZE    (1024 * 1024 * 5)

class TsParser{
public:
    TsParser(string file = "");
    ~TsParser();
    int  hex_print(const char *tag, const char *buf, size_t cnt);
public:
    static TsParser *get_instance(TsParser *ptr = nullptr);
    TsPAT   *get_pat(TsPAT *ptr = nullptr);
    TsPMT   *get_pmt(TsPMT *ptr = nullptr);
    TsPES   *get_pes(TsPES *ptr = nullptr);
private:
    int  get_file_info(void);
    void load_data_loop(void);
    void parser(void);
private:
    static TsParser *instance;
    string          m_file;
    int             m_fd         = -1;
    off_t           m_cur_offset = -1;
    off_t           m_filesize   = -1;
    int             m_done_flag  = -1;
    TsBuffer       *m_tsbuf         = nullptr;
    TsPAT          *m_pat           = nullptr;
    TsPMT          *m_pmt           = nullptr;
    TsPES          *m_pes           = nullptr;
    thread         *m_ld_thread     = nullptr;
    thread         *m_parser_thread = nullptr;
    queue<TsUnit>   m_ts_units;
    mutex           m_lock;
};

#endif //_TS_PARSER_HPP_

