/*
 * Progarm Name: circle-queue-def.hpp
 * Created Time: 2017-01-06 16:51:43
 * Last modified: 2017-01-12 13:37:47
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CIRCLE_QUEUE_DEF_HPP_
#define _CIRCLE_QUEUE_DEF_HPP_

#include "mqueue-def.hpp"
#include <iostream>
#include <cassert>
#include "seq-list-def.hpp"

using std::cout;
using std::endl;

/* 
 * 队列的存储表示也有两种方式：
 *  1> 基于数组的存储表示
 *  2> 基于链表的存储表示
 * */
template <typename T>
class CircQueue : public MQueue<T>{
public:
    CircQueue(int size = 100);
    ~CircQueue();
    int  en_queue(T x);
    int  de_queue(T &x);
    int  is_empty(void) const;
    int  is_full(void) const;
    int  get_size(void) const;
    int  output(void) const;
private:
    int  m_size;
    int  m_rear;
    int  m_front;
    int  m_rear_used;
    T   *m_data;
};

//-----------------------------------------------------------------------------

template <typename T>
CircQueue<T>::CircQueue(int size)
    :m_size(size)
    ,m_rear(0)
    ,m_front(0)
    ,m_rear_used(-1)
    ,m_data(NULL)
{
    this->m_data = new T[this->m_size];
    if(NULL == this->m_data){
        cout << "[Error] : new T[] failed !" << endl;
    }
}

template <typename T>
CircQueue<T>::~CircQueue()
{
    if(NULL != this->m_data){
        delete [] this->m_data;
    }
}

template <typename T>
int  CircQueue<T>::en_queue(T x)
{
    int ret = 0;

    if(0 != this->is_full()){
        if(this->m_rear > this->m_front){
            this->m_data[this->m_rear] = x;
            this->m_rear++;

            if(this->m_rear == this->m_size){
                if(0 != this->m_front) this->m_rear = 0;
                else{
                    this->m_rear--;
                    this->m_rear_used = 0;
                }
            }
        }else{
            this->m_data[this->m_rear] = x;
            this->m_rear++;

            if(this->m_rear == this->m_front){
                this->m_rear--;
                this->m_rear_used = 0;
            }
        }
    }else{
        ret = -1;
        cout << "queue is full !" << endl;
    }

    return ret;
}

template <typename T>
int  CircQueue<T>::de_queue(T &x)
{
    int ret = 0;

    if(0 != this->is_empty()){
        if(this->m_rear > this->m_front){
            if(0 == this->m_rear_used){
            }else{
                x = this->m_data[this->m_front];
                this->m_front++;
            }
        }else{
            if(0 == this->m_rear_used){
            }else{
            }
        }
    }else{
        ret = -1;
        cout << "queue is empty !" << endl;
    }

    return ret;
}

template <typename T>
int  CircQueue<T>::is_empty(void) const
{
    return this->m_rear == this->m_front ? 0 : -1;
}

template <typename T>
int  CircQueue<T>::is_full(void) const
{
    int ret = -1;

    if(this->m_rear > this->m_front){
        if((this->m_rear == this->m_size - 1) 
            && (0 == this->m_front)
            && (0 == this->m_rear_used))
            ret = 0;
    }else{
        if((1 == (this->m_front - this->m_rear))
            && (0 == this->m_rear_used))
            ret = 0;
    }

    return ret;
}

template <typename T>
int  CircQueue<T>::get_size(void) const
{
    return this->m_size;
}

template <typename T>
int  CircQueue<T>::output(void) const
{
    cout << "circle-queue<" << typeid(T).name() << "> : ";
    cout << "this->m_front = " << this->m_front << " - ";
    cout << "this->m_rear = " << this->m_rear << endl;

    cout << "size : " << this->m_size << " - [ ";
    for(int i=0; i<this->m_size; i++){
        cout << this->m_data[i] << " ";
    }
    cout << " ]" << endl;

    return 0;
}

#endif //_CIRCLE_QUEUE_DEF_HPP_

