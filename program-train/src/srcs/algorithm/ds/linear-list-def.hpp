/*
 * Progarm Name: linear-list-def.hpp
 * Reference : <<数据结构：用面向对象方法与C++语言描述>>
 * Created Time: 2016-08-27 08:41:39
 * Last modified: 2016-12-30 21:56:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _LINEAR_LIST_DEF_HPP_
#define _LINEAR_LIST_DEF_HPP__

/*
 * 线性表的存储表示有两种，顺序存储方式和链表存储方式
 * */

template <typename T>
class LinearList{
public:
    LinearList(){};
    virtual ~LinearList(){};
    virtual int  size(void) const = 0;
    virtual int  length(void) const = 0;
    virtual int  search(T& x) const = 0;
    virtual T   *get_data(int i) const = 0;
    virtual void set_data(int i, T& x) = 0;
    virtual int  insert(int i, T& x) = 0;
    virtual int  remove(int i, T& x) = 0;
    virtual int  isempty(void) const = 0;
    virtual int  isfull(void) const = 0;
    virtual int  sort(void) = 0;
    virtual int  input(T x) = 0;
    virtual void output(void) = 0;
};

#endif //_LINEAR_LIST_DEF_HPP_

