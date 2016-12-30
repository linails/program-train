/*
 * Progarm Name: seq-list-def.hpp
 * Reference : <<数据结构：用面向对象方法与C++语言描述>>
 * Created Time: 2016-08-27 08:44:20
 * Last modified: 2016-12-30 17:59:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SEQ_LIST_DEF_HPP_
#define _SEQ_LIST_DEF_HPP_

#include "linear-list-def.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 用顺序存储方式实现的线性表称为顺序表(sequential list)，是用数组作为表的存储结构的
 * */

template <typename T>
class SeqList: public LinearList<T>{
public:
    SeqList(int sz = 100);
    SeqList(SeqList<T> &L);
    ~SeqList(){ delete [] this->data; }
    int  size(void) const { return this->max_size; }
    int  length(void) const { return this->last + 1; }
    int  search(T &x) const ;
    T   *get_data(int i) const { return (i >= 0 && i < this->last ) ? &this->data[i] : NULL; } 
    void set_data(int i, T &x){ if(i > 0 && i <= this->last + 1) this->data[i-1] = x; }
    int  insert(int i, T &x);
    int  remove(int i, T &x);
    int  isempty(void) const { return (this->last == -1) ? 0 : -1 ; }
    int  isfull(void) const { return (this->last == this->max_size - 1) ? 0 : -1 ; }
    void sort(void);
    void input(void);
    void output(void);
    SeqList<T> &operator=(const SeqList<T> &L);
protected:
    int  resize(int size);
protected:
    T  *data;
    int max_size;
    int last;
};

//-----------------------------------------------------------------------------

template <typename T>
SeqList<T>::SeqList(int sz)
{
    if(sz > 0){
        this->last      = -1;
        this->max_size  = sz;

        this->data      = new T[this->max_size];
        if(NULL == this->data){
            cout << "new T[max_size] err!" << endl;
            exit(1);
        }
    }
}

template <typename T>
SeqList<T>::SeqList(SeqList<T> &L)
{
    this->max_size  = L.size();
    this->last      = L.length() - 1;

    this->data      = new T[this->max_size];
    if(NULL == this->data){
        cout << "new T[max_size] err !" << endl;
        exit(1);
    }

    for(int i=0; i<L.length(); i++){
        this->data[i] = L.get_data(i);
    }
}

template <typename T>
int  SeqList<T>::search(T &x) const 
{
    int ret = -1;

    for(int i=0; i<this->max_size; i++){
        if(x == this->data[i]){
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
int  SeqList<T>::insert(int i, T &x)
{
    int ret = 0;

    if(this->last == this->max_size - 1)    ret = -1;
    else if((i < 0) || (i > this->last+1))  ret = -1;
    else{
        for(int j=this->last; j>=i; j--) this->data[j+1] = this->data[j];
        this->data[i] = x;
        this->last++;
    }

    return ret;
}

template <typename T>
int  SeqList<T>::remove(int i, T &x)
{
    int ret = 0;

    if(0 > this->last)                   ret = -1;
    else if((0 > i) || (i > this->last)) ret = -1;
    else{
        x = this->data[i];
        for(int j=i; j<(this->last+1); j++) this->data[j-1] = this->data[j];
        this->last--;
    }

    return ret;
}

template <typename T>
void SeqList<T>::sort(void)
{
    cout << "sort" << endl;
}

template <typename T>
void SeqList<T>::input(void)
{
    cout << "input" << endl;
}

template <typename T>
void SeqList<T>::output(void)
{
    cout << "output" << endl;
}

template <typename T>
SeqList<T> &SeqList<T>::operator=(const SeqList<T> &L)
{
    return L;
}

template <typename T>
int  SeqList<T>::resize(int size)
{
    int ret = 0;

    if(size > this->max_size){

        T *newbuf = new T[size];

        if(NULL != newbuf){
            int n = this->last + 1;
            T *sptr = this->data;
            T *dptr = newbuf;

            while(n--) *dptr++ = *sptr++;
            delete [] this->data;

            this->data = newbuf;
            this->max_size = size;

        }else{
            ret = -1;
        }

    }else{
        ret = -1;
    }

    return ret;
}

#endif //_SEQ_LIST_DEF_HPP_

