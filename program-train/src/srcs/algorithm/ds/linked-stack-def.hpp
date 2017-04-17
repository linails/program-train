/*
 * Progarm Name: linked-stack-def.hpp
 * Created Time: 2017-01-06 10:05:21
 * Last modified: 2017-01-06 14:44:28
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _LINKED_STACK_DEF_HPP_
#define _LINKED_STACK_DEF_HPP_

#include <iostream>
#include "single-list-def.hpp"
#include <cassert>
#include <typeinfo>
#include "mstack-def.hpp"

using std::cout;
using std::endl;

template <typename T>
class LinkedStack: public MStack<T>{
public:
    LinkedStack(int size = 100);
    ~LinkedStack();
    int  push(T x);
    int  pop(T &x);
    int  is_empty(void) const;
    int  is_full(void) const;
    int  get_size(void) const;
    void output(void);
private:
    SingleList<T> m_singlelist;
    int           m_size;
};

//-----------------------------------------------------------------------------

template <typename T>
LinkedStack<T>::LinkedStack(int size)
    :m_size(size)
{
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
}

template <typename T>
int  LinkedStack<T>::push(T x)
{
    int ret = 0;

    if(0 < (ret = this->m_singlelist.length())){
        ret = this->m_singlelist.insert(ret - 1, x);
    }else{
        ret = this->m_singlelist.insert(ret, x);
    }

    return ret;
}

template <typename T>
int  LinkedStack<T>::pop(T &x)
{
    int ret = 0;

    if(1 < (ret = this->m_singlelist.length())){
        ret = this->m_singlelist.remove(ret - 1, x);
    }else{
        if(this->m_size > ret)
            ret = this->m_singlelist.remove(ret, x);
        else{
            cout << "[Error] : stack overflow !" << endl;
            ret = -1;
        }
    }

    return ret;
}

template <typename T>
int  LinkedStack<T>::is_empty(void) const
{
    if(0 == this->m_singlelist.length()) return 0;
    else                                 return -1;
}

template <typename T>
int  LinkedStack<T>::is_full(void) const
{
    int ret = 0;

    if(this->m_singlelist.length() < this->m_size) ret = -1;

    return ret;
}

template <typename T>
int  LinkedStack<T>::get_size(void) const
{
    return this->m_size;
}

template <typename T>
void LinkedStack<T>::output(void)
{
    cout << "LinkedStack<" << typeid(T).name() << ">" << endl;
    this->m_singlelist.output();
}

#endif //_LINKED_STACK_DEF_HPP_

