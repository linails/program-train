/*
 * Progarm Name: circle-list-def.hpp
 * Created Time: 2017-01-04 15:50:44
 * Last modified: 2017-01-04 17:23:05
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CIRCLE_LIST_DEF_HPP_
#define _CIRCLE_LIST_DEF_HPP_

/*
 * 循环链表(circular list)是另一种形式的表示线性表的链表，它的结点结构与单链表相同，与单链表不同的
 * 仅仅是链表中的表尾结点的link域中不是NULL，而是指向头结点
 *
 * 这样只要知道其他一个结点，就可以遍历表中的其他任何一个结点
 * */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <typeinfo>
#include "single-list-def.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

template <typename T>
class CircList : public SingleList<T>{
public:
    CircList();
    CircList(const T &data);
    CircList(CircList<T> &list);
    ~CircList();
    int  length(void) const;
    LinkNode<T> *get_head(void) const;
    int  set_head(LinkNode<T> *p);
    LinkNode<T> *search(T& x) const;
    LinkNode<T> *locate(int index) const;
    T   *get_data(int i) const;
    int  set_data(int i, T& x);
    int  insert(int i, T& x);
    int  remove(int i, T& x);
    int  input(T x);
    void output(void);
protected:
    LinkNode<T> *m_last;
};

//-----------------------------------------------------------------------------

template <typename T>
CircList<T>::CircList()
{
    cout << "CircList ..." << endl;
}

template <typename T>
CircList<T>::CircList(const T &data)
    :SingleList<T>(data)
{
}

template <typename T>
CircList<T>::CircList(CircList<T> &list)
    :SingleList<T>(list)
{
}

template <typename T>
CircList<T>::~CircList()
{
    cout << "~CircList ... " << endl;
}

template <typename T>
int  CircList<T>::length(void) const
{
    return 0;
}

template <typename T>
LinkNode<T> *CircList<T>::get_head(void) const
{
}

template <typename T>
int  CircList<T>::set_head(LinkNode<T> *p)
{
}

template <typename T>
LinkNode<T> *CircList<T>::search(T& x) const
{
}

template <typename T>
LinkNode<T> *CircList<T>::locate(int index) const
{
}

template <typename T>
T   *CircList<T>::get_data(int i) const
{
}

template <typename T>
int  CircList<T>::set_data(int i, T& x)
{
}

template <typename T>
int  CircList<T>::insert(int i, T& x)
{
}

template <typename T>
int  CircList<T>::remove(int i, T& x)
{
}

template <typename T>
int  CircList<T>::input(T x)
{
}

template <typename T>
void CircList<T>::output(void)
{
}

#endif //_CIRCLE_LIST_DEF_HPP_

