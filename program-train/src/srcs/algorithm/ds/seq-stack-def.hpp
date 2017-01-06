/*
 * Progarm Name: seq-stack-def.hpp
 * Created Time: 2017-01-06 10:05:21
 * Last modified: 2017-01-06 12:31:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SEQ_STACK_DEF_HPP_
#define _SEQ_STACK_DEF_HPP_

#include <iostream>
#include "seq-list-def.hpp"
#include <cassert>
#include <typeinfo>
#include "mstack-def.hpp"

using std::cout;
using std::endl;

template <typename T>
class SeqStack: public MStack<T>{
public:
    SeqStack(int size = 100);
    ~SeqStack();
    int  push(T x);
    int  pop(T &x);
    int  is_empty(void) const;
    int  is_full(void) const;
    int  get_size(void) const;
    void output(void);
private:
    SeqList<T> m_seqlist;
};

//-----------------------------------------------------------------------------

template <typename T>
SeqStack<T>::SeqStack(int size)
    :m_seqlist(size)
{
}

template <typename T>
SeqStack<T>::~SeqStack()
{
}

template <typename T>
int  SeqStack<T>::push(T x)
{
    int ret = 0;

    ret = this->m_seqlist.insert(this->m_seqlist.length(), x);

    return ret;
}

template <typename T>
int  SeqStack<T>::pop(T &x)
{
    int ret = 0;

    ret = this->m_seqlist.remove(this->m_seqlist.length() - 1, x);

    return ret;
}

template <typename T>
int  SeqStack<T>::is_empty(void) const
{
    return this->m_seqlist.isempty();
}

template <typename T>
int  SeqStack<T>::is_full(void) const
{
    return this->m_seqlist.isfull();
}

template <typename T>
int  SeqStack<T>::get_size(void) const
{
    return this->m_seqlist.size();
}

template <typename T>
void SeqStack<T>::output(void)
{
    cout << "SeqStack<" << typeid(T).name() << ">" << endl;
    this->m_seqlist.output();
}

#endif //_SEQ_STACK_DEF_HPP_

