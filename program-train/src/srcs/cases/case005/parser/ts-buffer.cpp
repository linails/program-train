/*
 * Progarm Name: ts-buffer.cpp
 * Created Time: 2017-06-26 12:44:36
 * Last modified: 2017-06-27 12:11:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-buffer.hpp"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>

using std::cout;
using std::endl;

TsBuffer::TsBuffer(size_t maxsize)
    :m_maxsize(maxsize)
{
    this->buf = new char[maxsize]();
}

TsBuffer::~TsBuffer()
{
    if(nullptr != this->buf){
        delete[] this->buf;
        this->buf = nullptr;
    }
}

int  TsBuffer::set_length(size_t size)
{
    this->m_size = size; return 0;
}

size_t TsBuffer::size(void)
{
    return this->m_size;
}

bool   TsBuffer::empty(void)
{
    if(0 == this->m_size) return true;
    else                  return false;
}

int    TsBuffer::clear(void)
{
    this->m_size         = 0;
    this->m_top_remain   = -1;
    this->m_tail_remain  = -1;

    memset(this->buf, 0, this->m_maxsize);

    return 0;
}

int    TsBuffer::top_remain(TsBuffer &tsbuf, int index)
{
    this->m_top_remain = 0;

    if(0x47 != this->buf[0]){
        char *ptrd = &tsbuf.buf[index];
        char *ptrs = this->buf;

        while((0x47 != *ptrs) || this->top_pos_verify(this->m_top_remain)){
            *ptrd++ = *ptrs++;
            this->m_top_remain++;
        }

        tsbuf.set_length(this->m_top_remain + index);

        cout << "this->m_top_remain = " << this->m_top_remain << endl;

        return 0;

    }else{
        cout << "this->m_top_remain = " << this->m_top_remain << endl;
        return -1;
    }
}

int    TsBuffer::tail_remain(TsBuffer &tsbuf, int index)
{
    if(-1 != this->m_top_remain){
        this->m_tail_remain = (this->m_size - this->m_top_remain) % 188;
    }else{
        this->m_top_remain = 0;

        if(0x47 != this->buf[0]){
            char *ptrs = this->buf;
            while((0x47 != *ptrs) || this->top_pos_verify(this->m_top_remain)){
                ptrs++;
                this->m_top_remain++;
            }
        }

        this->m_tail_remain = (this->m_size - this->m_top_remain) % 188;
    }

    cout << "this->m_tail_remain = " << this->m_tail_remain << endl;

    if(0 != this->m_tail_remain){

        char *ptrd = &tsbuf.buf[index + this->m_tail_remain];
        char *ptrs = &this->buf[this->m_size];

        size_t num = this->m_tail_remain;
        do{
            *ptrd-- = *ptrs--;
        }while(num--);

        tsbuf.set_length(this->m_tail_remain + index);

        return 0;
    }else{
        return -1;
    }
}

int    TsBuffer::cut_tsunit(queue<TsUnit> &ts_units)
{
    int cnt = (this->m_size - this->m_top_remain) / 188;

    for(int i=0; i<cnt; i++){
        TsUnit unit(&(this->buf[this->m_top_remain + 188 * i]));

        //{
        //std::unique_lock<std::mutex> lock(mtx);
        ts_units.push(unit);
        //}
        //usleep(10 * 1000);
    }

    return 0;
}

int    TsBuffer::top_pos_verify(size_t top_remain)
{
    for(int i=0; i<3; i++){
        if(0x47 != this->buf[top_remain + 188 * (i+1)]){
            return -1;
        }
    }

    return 0;
}

