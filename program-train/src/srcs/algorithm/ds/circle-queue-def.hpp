/*
 * Progarm Name: circle-queue-def.hpp
 * Created Time: 2017-01-06 16:51:43
 * Last modified: 2017-01-06 16:59:39
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CIRCLE_QUEUE_DEF_HPP_
#define _CIRCLE_QUEUE_DEF_HPP_

#include "mqueue-def.hpp"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

template <typename T>
class CircQueue : public MQueue<T>{
public:
    CircQueue();
    ~CircQueue();
    int  en_queue(T x);
    int  de_queue(T &x);
    int  is_empty(void) const;
    int  is_full(void) const;
    int  get_size(void) const;
private:
};

#endif //_CIRCLE_QUEUE_DEF_HPP_

