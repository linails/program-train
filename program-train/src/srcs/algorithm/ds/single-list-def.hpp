/*
 * Progarm Name: single-list-def.hpp
 * Created Time: 2017-01-03 14:13:51
 * Last modified: 2017-01-04 15:42:07
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
#include <typeinfo>

using std::string;
using std::vector;
using std::cout;
using std::endl;

template <typename T>
struct LinkNode{
    LinkNode(LinkNode<T> *ptr = NULL):m_link(ptr){m_data = (m_link == NULL ? 0 : ptr->m_data);}
    LinkNode(const T &data, LinkNode<T> *ptr = NULL):m_data(data), m_link(ptr){}
    LinkNode(LinkNode<T> &node){ this->m_data = node.m_data; this->m_link = node.m_link;}
    T            m_data;
    LinkNode<T> *m_link;
};

template <typename T>
class SingleList{
public:
    SingleList();
    SingleList(const T &data);
    SingleList(SingleList<T> &list);
    ~SingleList();
    int  length(void) const;
    int  make_empty(void);
    LinkNode<T> *get_head(void) const;
    int  set_head(LinkNode<T> *p);
    LinkNode<T> *search(T& x) const;
    LinkNode<T> *locate(int index) const;
    T   *get_data(int i) const;
    int  set_data(int i, T& x);
    int  insert(int i, T& x);
    int  remove(int i, T& x);
    int  sort(void);
    int  input(T x);
    void output(void);
    SingleList<T> &operator=(SingleList<T> &sl);
protected:
    LinkNode<T> *m_first;
    int  m_flag_first;
};

//-----------------------------------------------------------------------------

template<typename T>
SingleList<T>::SingleList()
{
    this->m_first = new LinkNode<T>;
    if(NULL == this->m_first){
        cout << "[Error] : LinkNode<T> new failed !" << endl;
    }

    /* 
     * m_first->m_data 赋值标记
     * */
    this->m_flag_first = -1;
}

template<typename T>
SingleList<T>::SingleList(const T &data)
{
    this->m_first = new LinkNode<T>(data);
    if(NULL == this->m_first){
        cout << "[Error] : LinkNode<T> new failed !" << endl;
    }

    this->m_flag_first = 0;
}

template<typename T>
SingleList<T>::SingleList(SingleList<T> &list)
{
    LinkNode<T> *sptr = list.get_head();
    LinkNode<T> *dptr = new LinkNode<T>(sptr);
    if(NULL != dptr){
        dptr->m_link = NULL;
        this->m_first = dptr;

        while(NULL != sptr->m_link){
            T data;
            data = sptr->m_link->m_data;
            dptr->m_link = new LinkNode<T>(data);
            if(NULL != dptr->m_link){
                dptr = dptr->m_link;
                sptr = sptr->m_link;
            }else
                cout << "[Error] : LinkNode<T> new failed !" << endl;
        }
    }else
        cout << "[Error] : LinkNode<T> new failed !" << endl;
}

template<typename T>
SingleList<T>::~SingleList()
{
    if(0 != this->make_empty()){
        cout << "[Error] : SingleList makeempty failed !" << endl;
    }
}

template<typename T>
int  SingleList<T>::length(void) const
{
    int ret = 1;

    if(NULL != this->m_first->m_link){
        LinkNode<T> *p = this->m_first->m_link;
        while(NULL != p){
            p = p->m_link;
            ret++;
        }
    }

    return ret;
}

template<typename T>
int  SingleList<T>::make_empty(void)
{
    while(NULL != this->m_first->m_link){
        LinkNode<T> *p = NULL;

        p = this->m_first->m_link;
        this->m_first->m_link = p->m_link;

        delete p;
    }

    delete this->m_first;

    return 0;
}

template<typename T>
LinkNode<T> *SingleList<T>::get_head(void) const
{
    return (LinkNode<T> *)this->m_first;
}

template<typename T>
int  SingleList<T>::set_head(LinkNode<T> *p)
{
    this->m_first = p;
    return 0;
}

template<typename T>
LinkNode<T> *SingleList<T>::search(T& x) const
{
    LinkNode<T> *p = this->m_first;
    while(NULL != p){
        if(x == p->m_data) break;
        else    p = p->m_link;
    }

    return p;
}

template<typename T>
LinkNode<T> *SingleList<T>::locate(int index) const
{
    LinkNode<T> *p = NULL;

    if(0 <= index){
        p = this->m_first;

        while(index > 0){
            if(NULL == (p = p->m_link)) break;
            index--;
        }
    }

    return p;
}

template<typename T>
T   *SingleList<T>::get_data(int i) const
{
    LinkNode<T> *p = this->locate(i);
    if(NULL != p){
        return &p->m_data;
    }else
        return NULL;
}

template<typename T>
int  SingleList<T>::set_data(int i, T& x)
{
    int ret = 0;
    LinkNode<T> *p = NULL;

    if(NULL != (p = this->locate(i))){
        p->m_data = x;
    }else
        ret = -1;

    return ret;
}

template<typename T>
int  SingleList<T>::insert(int i, T& x)
{
    int ret = 0;
    LinkNode<T> *p = NULL;

    if(NULL != (p = this->locate(i))){
        LinkNode<T> *np = new LinkNode<T>(x);
        if(NULL != np){
            np->m_link = p->m_link;
            p->m_link  = np;
        }else
            cout << "[Error] : LinkNode<T> new failed !" << endl;
    }else
        ret = -1;

    return ret;
}

template<typename T>
int  SingleList<T>::remove(int i, T& x)
{
    int ret = 0;
    LinkNode<T> *p = NULL;

    if(NULL != (p = this->locate(i-1))){
        x = p->m_link->m_data;

        LinkNode<T> *dp = p->m_link;
        p->m_link = p->m_link->m_link;

        delete dp;
    }else
        ret = -1;

    return ret;
}

template<typename T>
int  SingleList<T>::sort(void)
{
    return 0;
}

template<typename T>
int  SingleList<T>::input(T x)
{
    int ret = 0;

    if(0 == this->m_flag_first){
        LinkNode<T> *p = this->m_first;

        while(NULL != p->m_link) p = p->m_link;

        p->m_link = new LinkNode<T>(x);
        if(NULL == p->m_link){
            ret = -1;
        }
    }else{
        this->m_flag_first = 0;
        this->m_first->m_data = x;
    }
    return ret;
}

template<typename T>
void SingleList<T>::output(void)
{
    cout << "SingleList<" << typeid(T).name() << "> : " ;
    
    LinkNode<T> *p = this->m_first;

    while(NULL != p){
        cout << p->m_data << " ";
        p = p->m_link;
    }

    cout << endl;
}

template<typename T>
SingleList<T> &SingleList<T>::operator=(SingleList<T> &sl)
{
    /* 
     *  1. 检查自赋值
     *  2. 释放原有的内存资源
     *  3. 分配新的内存资源，并复制内容
     *  4. 返回本对象的引用
     * */

    if(this == &sl){
        cout << "[Error] : this = &sl" << endl;
        return *this;
    }

    this->make_empty();


    LinkNode<T> *sptr = sl.get_head();

    this->m_first = new LinkNode<T>(sptr->m_data);
    LinkNode<T> *cptr = this->m_first;

    this->m_first->m_data = sptr->m_data;

    while(NULL != sptr->m_link){

        LinkNode<T> *p = new LinkNode<T>(sptr->m_link->m_data);
        if(NULL == p) cout << "[Error] : new failed ..." << endl;

        cptr->m_link = p;
        cptr = p;
        sptr = sptr->m_link;
    }

    return *this;
}

#endif //_SINGLE_LIST_DEF_HPP_

