/*
 * Progarm Name: circle-list-def.hpp
 * Created Time: 2017-01-04 15:50:44
 * Last modified: 2017-01-06 14:24:59
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
    CircList(const CircList<T> &list);
    ~CircList();
    int  length(void) const;
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
    this->m_last = this->m_first;

    this->m_first->m_link = this->m_last;
}

template <typename T>
CircList<T>::CircList(const T &data)
    :SingleList<T>(data)
{
    this->m_last = this->m_first;

    this->m_first->m_link = this->m_last;
}

template <typename T>
CircList<T>::CircList(const CircList<T> &list)
    :SingleList<T>(list)
{
    this->m_last = this->m_first;

    while(NULL != this->m_last->m_link) this->m_last = this->m_last->m_link;

    this->m_last->m_link = this->m_first;
}

template <typename T>
CircList<T>::~CircList()
{
    /* 
     * 由于先执行派生类的析构函数，因此将 this->m_last->m_link = NULL
     *
     * 这个时候就可以在调用 ~SingleList<T>::SingleList() 的时候进行析构释放空间
     * */
    this->m_last->m_link = NULL;
}

template <typename T>
int  CircList<T>::length(void) const
{
    int ret = 0;

    this->m_last->m_link = NULL;

    ret = SingleList<T>::length();

    this->m_last->m_link = this->m_first;

    return ret;
}

template <typename T>
int  CircList<T>::set_head(LinkNode<T> *p)
{
    int ret = 0;

    if(0 == (ret = SingleList<T>::set_head(p)))
        this->m_last->m_link = this->m_first;
    else
        ret = -1;

    return ret;
}

template <typename T>
LinkNode<T> *CircList<T>::search(T& x) const
{
    this->m_last->m_link = NULL;

    LinkNode<T> *p = SingleList<T>::search(x);

    this->m_last->m_link = this->m_first;

    return p;
}

template <typename T>
LinkNode<T> *CircList<T>::locate(int index) const
{
    LinkNode<T> *p = NULL;

    if(0 < this->length()){
        int real_index = index % this->length();
        cout << "length() : " << this->length() << " - real_index : " << real_index << " - index : " << index << endl;

        this->m_last->m_link = NULL;

        p = SingleList<T>::locate(real_index);

        this->m_last->m_link = this->m_first;
    }

    return p;
}

template <typename T>
T   *CircList<T>::get_data(int i) const
{
    LinkNode<T> *p = this->locate(i);

    if(NULL != p){
        return &p->m_data;
    }else
        return NULL;
}

template <typename T>
int  CircList<T>::set_data(int i, T& x)
{
    int ret = 0;
    LinkNode<T> *p = NULL;

    if(NULL != (p = this->locate(i))){
        p->m_data = x;
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  CircList<T>::insert(int i, T& x)
{
    int ret = 0;
    LinkNode<T> *p = NULL;

    if(0 == this->m_flag_first){
        if(NULL != (p = this->locate(i))){
            LinkNode<T> *np = new LinkNode<T>(x);
            if(NULL != np){

                if(1 >= this->length()){
                    this->m_last = np;
                    this->m_last->m_link  = this->m_first;
                    this->m_first->m_link = np;
                }else{
                    np->m_link = p->m_link;
                    p->m_link  = np;
                }

            }else
                cout << "[Error] : LinkNode<T> new failed !" << endl;
        }else
            ret = -1;
    }else{
        this->m_first->m_data = x;
        this->m_flag_first = 0;
    }

    return ret;
}

template <typename T>
int  CircList<T>::remove(int i, T& x)
{
    int ret = 0;

    cout << "this->length() : " << this->length() << endl;

    if(2 != this->length()){
        this->m_last->m_link = NULL;
        ret = SingleList<T>::remove(i, x);
        //assert(-1 != ret);
        this->m_last->m_link = this->m_first;
        cout << " ->length() : " << this->length() << endl;
    }else{
        this->m_last->m_link = NULL;
        ret = SingleList<T>::remove(i, x);
        //assert(-1 != ret);
        this->m_last = this->m_first;
        this->m_last->m_link = this->m_first;
    }

    return ret;
}

template <typename T>
int  CircList<T>::input(T x)
{
    int ret = 0;

    if(-1 == (ret = this->insert(this->length(), x))){
        cout << "[Error] : insert failed !" << endl;
    }

    return ret;
}

template <typename T>
void CircList<T>::output(void)
{
    cout << "CircList<" << typeid(T).name() << "> : " ;

    this->m_last->m_link = NULL;

    SingleList<T>::output();

    this->m_last->m_link = this->m_first;
}

#endif //_CIRCLE_LIST_DEF_HPP_

