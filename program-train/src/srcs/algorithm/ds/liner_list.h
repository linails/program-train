/*
 * Progarm Name: liner_list.h
 * Reference : <<数据结构：用面向对象方法与C++语言描述>>
 * Created Time: 2016-08-27 08:41:39
 * Last modified: 2016-08-27 08:42:33
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _LINER_LIST_H_
#define _LINER_LIST_H_

template <typename T>
class LinearList{
public:
    LinearList(){};
    virtual int  size() const = 0;
    virtual int  length() const = 0;
    virtual int  search(T& x) const = 0;
    virtual int  locate(int i) const = 0;
    virtual T   *get_data(int i) const = 0;
    virtual void set_data(int i, T& x) = 0;
    virtual bool insert(int i, T& x) = 0;
    virtual bool remove(int i, T& x) = 0;
    virtual bool isempty() const = 0;
    virtual bool isfull() const = 0;
    virtual void sort() = 0;
    virtual void input() = 0;
    virtual void output() = 0;
    virtual LinearList<T> &operator=(const LinearList<T> &L) = 0;
    virtual ~LinearList();
};

#endif //_LINER_LIST_H_

