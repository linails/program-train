/*
 * Progarm Name: single-list-def.hpp
 * Created Time: 2017-01-03 14:13:51
 * Last modified: 2017-01-03 16:57:58
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SINGLE_LIST_DEF_HPP_
#define _SINGLE_LIST_DEF_HPP_

/* 
 * single linked list
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 顺序表的优缺点：
 *  1> 优点
 *     a) 无需为表示结点间的逻辑关系而增加额外的存储空间，存储利用率高
 *     b) 可以方便地随机存储表中的任一结点，存储速度快
 *  2> 缺点
 *     a) 在表中插入新元素或删除无用元素时，为了保持其他元素的相对次序不变，平均需要移动一半元素
 *        ，运行效率低
 *     b) 由于顺序表需要占用连续的空间，如果预先进行存储分配（静态分配）,则当表长度变化较大时
 *        ，难以确定合适的存储空间大小，若按可能达到的最大长度预分配表的空间，则容易造成一部
 *        分空间长期闲置而得不到充分利用。若事先对表长度估计不足，则插入操作可能发生溢出。
 *     c) 如果采用指针方式来定义数组，在程序运行时动态分配存储空间，一旦需要，可以用另外一个更大
 *        的数据代替原来的数组，此方法虽然扩充了数组的空间，不过时间开销太大
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  为了克服顺序表的缺点，通常采用链接方式来进行存储线性表；链表适用于插入或删除频繁，
 *  存储空间不定的情形
 *
 * */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using std::string;
using std::vector;
using std::cout;
using std::endl;

template <typename T>
struct LinkNode{
    LinkNode(LinkNode<T> *ptr = NULL):m_link(ptr){}
    LinkNode(const T &data, LinkNode<T> *ptr = NULL):m_data(data), m_link(ptr){}
    T            m_data;
    LinkNode<T> *m_link;
};

template <typename T>
class SingleList{
public:
    SingleList();
    SingleList(const T &data);
    ~SingleList();
    int  length(void) const;
    int  make_empty(void);
    LinkNode<T> *get_head(void) const;
    int  set_head(LinkNode<T> *p);
    int  search(T& x) const;
    T   *get_data(int i) const;
    void set_data(int i, T& x);
    int  insert(int i, T& x);
    int  remove(int i, T& x);
    int  isempty(void) const;
    int  isfull(void) const;
    int  sort(void);
    int  input(T x);
    void output(void);
    SingleList<T> &operator=(SingleList<T> &sl);
protected:
    LinkNode<T> *m_first;
};

//-----------------------------------------------------------------------------

template<typename T>
SingleList<T>::SingleList()
{
    this->m_first = new LinkNode<T>;
    if(NULL == this->m_first){
        cout << "LinkNode<T> new failed !" << endl;
    }
}

template<typename T>
SingleList<T>::SingleList(const T &data)
{
    this->m_first = new LinkNode<T>(data);
    if(NULL == this->m_first){
        cout << "LinkNode<T> new failed !" << endl;
    }
}

template<typename T>
SingleList<T>::~SingleList()
{
}

template<typename T>
int  SingleList<T>::length(void) const
{
    return 0;
}

template<typename T>
int  SingleList<T>::make_empty(void)
{
    return 0;
}

template<typename T>
LinkNode<T> *SingleList<T>::get_head(void) const
{
    return &this->m_first;
}

template<typename T>
int  SingleList<T>::set_head(LinkNode<T> *p)
{
    return 0;
}

template<typename T>
int  SingleList<T>::search(T& x) const
{
    return 0;
}

template<typename T>
T   *SingleList<T>::get_data(int i) const
{
    return this->m_first.m_data;
}

template<typename T>
void SingleList<T>::set_data(int i, T& x)
{
}

template<typename T>
int  SingleList<T>::insert(int i, T& x)
{
    return 0;
}

template<typename T>
int  SingleList<T>::remove(int i, T& x)
{
    return 0;
}

template<typename T>
int  SingleList<T>::isempty(void) const
{
    return 0;
}

template<typename T>
int  SingleList<T>::isfull(void) const
{
    return 0;
}

template<typename T>
int  SingleList<T>::sort(void)
{
    return 0;
}

template<typename T>
int  SingleList<T>::input(T x)
{
    return 0;
}

template<typename T>
void SingleList<T>::output(void)
{
}

template<typename T>
SingleList<T> &SingleList<T>::operator=(SingleList<T> &sl)
{
    return sl;
}

#endif //_SINGLE_LIST_DEF_HPP_

