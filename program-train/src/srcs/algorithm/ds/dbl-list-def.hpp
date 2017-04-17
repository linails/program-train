/*
 * Progarm Name: dbl-list-def.hpp
 * Created Time: 2017-01-05 17:05:07
 * Last modified: 2017-01-06 09:48:04
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DBL_LIST_DEF_HPP_
#define _DBL_LIST_DEF_HPP_

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

/*
 * 使用双向链表(doubly linked list)的目的是为了解决链表中访问直接前驱和直接后继的问题
 * */

template <typename T>
struct dblNode{
    dblNode(dblNode<T> *ptr_l = NULL, dblNode<T> *ptr_r = NULL)
        :m_link_l(ptr_l)
        ,m_link_r(ptr_r)
    {
    }
    dblNode(const T &data, dblNode<T> *ptr_l = NULL, dblNode<T> *ptr_r = NULL)
        :m_data(data)
        ,m_link_l(ptr_l)
        ,m_link_r(ptr_r)
    {
    }
    ~dblNode();
public:
    dblNode<T> *m_link_l;
    dblNode<T> *m_link_r;
    T           m_data;
};

template <typename T>
class dblList{
public:
    dblList(const T &data);
    dblList(const dblList<T> &list);
    ~dblList();
    dblList<T> &operator=(const dblList<T> &list);
    int  length() const;
    int  is_empty() const;
    dblNode<T> *get_head(void) const;
    int  set_head(dblNode<T> *p);
    dblNode<T> *search(T& x) const;
    dblNode<T> *locate(int index) const;
    int  insert(int i, T& x);
    int  remove(int i, T& x);
    int  input(T x);
    void output(void);
private:
    dblNode<T>  *m_first;
};

//-----------------------------------------------------------------------------

template <typename T>
dblList<T>::dblList(const T &data)
{
}

template <typename T>
dblList<T>::dblList(const dblList<T> &list)
{
}

template <typename T>
dblList<T>::~dblList()
{
}

template <typename T>
dblList<T> &dblList<T>::operator=(const dblList<T> &list)
{
    return list;
}

template <typename T>
int  dblList<T>::length() const
{
    return 0;
}

template <typename T>
int  dblList<T>::is_empty() const
{
    return 0;
}

template <typename T>
dblNode<T> *dblList<T>::get_head(void) const
{
    return this->m_first;
}

template <typename T>
int  dblList<T>::set_head(dblNode<T> *p)
{
    return 0;
}

template <typename T>
dblNode<T> *dblList<T>::search(T& x) const
{
    return this->m_first;
}

template <typename T>
dblNode<T> *dblList<T>::locate(int index) const
{
    return this->m_first;
}

template <typename T>
int  dblList<T>::insert(int i, T& x)
{
    return 0;
}

template <typename T>
int  dblList<T>::remove(int i, T& x)
{
    return 0;
}

template <typename T>
int  dblList<T>::input(T x)
{
    return 0;
}

template <typename T>
void dblList<T>::output(void)
{
}

#endif //_DBL_LIST_DEF_HPP_

