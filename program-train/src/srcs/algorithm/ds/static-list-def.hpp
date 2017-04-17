/*
 * Progarm Name: static-list-def.hpp
 * Created Time: 2017-01-06 09:27:41
 * Last modified: 2017-01-06 10:04:25
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STATIC_LIST_DEF_HPP_
#define _STATIC_LIST_DEF_HPP_

/*  
 *  如果为数组中的每一个元素附加一个链接指针，就形成静态链表结构
 *  由于它是利用数组定义的，在整个运算过程中存储空间的大小不会变化，因此称为静态链表
 *  */

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T>
struct sLinkNode{
    T   m_data;
    int m_link;
};

template <typename T>
class StaticList{
public:
    StaticList(const T &x);
    StaticList(const StaticList<T> &sl);
    ~StaticList();
    StaticList<T> &operator=(const StaticList<T> &sl);
    int  length() const;
    int  is_empty() const;
    int  search(T& x) const;
    int  locate(int index) const;
    int  insert(int i, T& x);
    int  remove(int i, T& x);
    int  input(T x);
    void output(void);
private:
    static const int m_max_size = 100;
    sLinkNode<T>     m_data_pool[m_max_size];
    sLinkNode<T>    *m_first;
};

//-----------------------------------------------------------------------------

template <typename T>
const int StaticList<T>::m_max_size;

template <typename T>
StaticList<T>::StaticList(const T &x)
{
}

template <typename T>
StaticList<T>::StaticList(const StaticList<T> &sl)
{
}

template <typename T>
StaticList<T>::~StaticList()
{
}

template <typename T>
StaticList<T> &StaticList<T>::operator=(const StaticList<T> &sl)
{
    return sl;
}

template <typename T>
int  StaticList<T>::length() const
{
    return 0;
}

template <typename T>
int  StaticList<T>::is_empty() const
{
    return 0;
}

template <typename T>
int  StaticList<T>::search(T& x) const
{
    return 0;
}

template <typename T>
int  StaticList<T>::locate(int index) const
{
    return 0;
}

template <typename T>
int  StaticList<T>::insert(int i, T& x)
{
    return 0;
}

template <typename T>
int  StaticList<T>::remove(int i, T& x)
{
    return 0;
}

template <typename T>
int  StaticList<T>::input(T x)
{
    return 0;
}

template <typename T>
void StaticList<T>::output(void)
{
}

#endif //_STATIC_LIST_DEF_HPP_

