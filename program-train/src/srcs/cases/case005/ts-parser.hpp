/*
 * Progarm Name: ts-parser.hpp
 * Created Time: 2017-06-22 13:22:23
 * Last modified: 2017-06-25 22:23:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_HPP_
#define _TS_PARSER_HPP_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <pthread.h>

using std::string;

#define BUF_MAX_SIZE    1024 * 1024 * 5

class TsParser{
public:
    TsParser(string file = "");
    ~TsParser();
private:
    int  get_file_info(void);
private:
    static void *load_data_loop(void *args);
private:
    string          m_file;
    int             m_fd = -1;
    char            m_buf[BUF_MAX_SIZE] = {0, };
    off_t           m_cur_offset = -1;
    pthread_t      *m_ld_thread = nullptr;
};

#endif //_TS_PARSER_HPP_

