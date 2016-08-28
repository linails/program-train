/*
 * Progarm Name: seq_list.h
 * Reference : <<数据结构：用面向对象方法与C++语言描述>>
 * Created Time: 2016-08-27 08:44:20
 * Last modified: 2016-08-28 09:14:39
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#include "liner_list.h"
#include <iostream>

template <typename T>
class SeqList: public LinearList<T>{
public:
    SeqList(int sz = 100);
    SeqList(SeqList<T> &L);
    ~SeqList(){ delete [] data; }
    int  size(void) const { return this->max_size; }
    int  length(void) const { return this->last + 1; }
    int  search(T &x) const ;
    int  locate(int i) const;
    T   *get_data(int i) const { return (i >= 0 && i < this->last ) ? &this->data[i] : NULL; } 
    void set_data(int i, T &x){ if(i > 0 && i <= last + 1) data[i-1] = x; }
    bool insert(int i, T &x);
    bool remove(int i, T &x);
    bool isempty(void){ return (last == -1) ? true : false; }
    bool isfull(void){ return (last == max_size - 1) ? true : false; }
    void input(void);
    void output(void);
    SeqList<T> &operator=(const SeqList<T> &L);
protected:
    void resize(int new_size);
protected:
    T  *data;
    int max_size;
    int last;
};

#endif //_SEQ_LIST_H_

