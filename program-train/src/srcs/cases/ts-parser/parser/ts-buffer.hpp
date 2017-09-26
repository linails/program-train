/*
 * Progarm Name: ts-buffer.hpp
 * Created Time: 2017-06-26 12:41:08
 * Last modified: 2017-06-27 16:32:22
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_BUFFER_HPP_
#define _TS_BUFFER_HPP_

#include <cstdio>
#include "ts-unit.hpp"
#include <queue>

using std::queue;

class  TsUnit;

struct TsBuffer{
    TsBuffer(size_t maxsize = 512);
    ~TsBuffer();
    int    set_length(size_t size);
    size_t size(void);
    bool   empty(void);
    int    clear(void);
    int    cut_tsunit(queue<TsUnit> &ts_units);
    int    top_remain(TsBuffer &tsbuf, int index = 0);
    int    tail_remain(TsBuffer &tsbuf, int index = 0);
private:
    int    top_pos_verify(size_t top_remain);
public:
    size_t   m_maxsize      = 0;
    size_t   m_size         = 0;
    char    *buf            = nullptr;
    int      m_top_remain   = -1;
    int      m_tail_remain  = -1;
};

#endif //_TS_BUFFER_HPP_

