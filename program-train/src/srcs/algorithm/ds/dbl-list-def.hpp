/*
 * Progarm Name: dbl-list-def.hpp
 * Created Time: 2017-01-05 17:05:07
 * Last modified: 2017-01-05 17:53:17
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
    dblNode();
    ~dblNode();
public:
    dblNode<T> *m_link_l;
    dblNode<T> *m_link_r;
    T           m_data;
};

#endif //_DBL_LIST_DEF_HPP_

