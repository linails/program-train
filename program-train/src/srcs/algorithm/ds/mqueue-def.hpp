/*
 * Progarm Name: mqueue-def.hpp
 * Created Time: 2017-01-06 15:53:54
 * Last modified: 2017-01-06 16:24:30
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MQUEUE_DEF_HPP_
#define _MQUEUE_DEF_HPP_

/* 
 * Note : 
 *
 *  队列是另一种限定存取位置的线性表，它只允许在表的一端插入，在另一端删除
 *
 *  允许插入的一端叫队尾(rear)，删除的一端叫对头(front)
 *
 *  队列所具有的这种特性叫做FIFO
 *
 * */

template <typename T>
class MQueue{
public:
    MQueue(){};
    virtual ~MQueue(){};
    virtual int  en_queue(T x) = 0;
    virtual int  de_queue(T &x) = 0;
    virtual int  is_empty(void) const = 0;
    virtual int  is_full(void) const = 0;
    virtual int  get_size(void) const = 0;
};

#endif //_MQUEUE_DEF_HPP_

