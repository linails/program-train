/*
 * Progarm Name: cthread.hpp
 * Created Time: 2016-12-07 11:26:51
 * Last modified: 2017-06-24 23:05:25
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CTHREAD_HPP_
#define _CTHREAD_HPP_

#include "timer.h"
#include <pthread.h>

/* 
 * 为了保持多进程的优点，同时在一定程度上克服其缺点，引入了线程
 *
 * 这是为了将进程的各种劣势降至最低限度而设计的一种 “轻量级进程”
 *
 * 线程相比于进程具有如下优点:
 *  1> 线程的创建和上下文切换比进程的创建和上下文切换更快
 *  2> 线程间交换数据时无需特殊技术
 * */
class cThread{
public:
    cThread();
    ~cThread();
    int cthread_main(int argc, char **argv);
private:
    int  timing_create_thread(void);
    int  deadlock_test_for_mutex(void);
    int  normal_test_for_mutex(void);
    static void *child(void *arg);
    static void *odd_deadlock(void *arg);
    static void *even_deadlock(void *arg);
    static void *odd_nornal(void *arg);
    static void *even_normal(void *arg);
    static void routine(void *d);
private:
    static Timer    timer0;
    static Timer    timer1;
    static pthread_mutex_t  m_mtx;
};

#endif //_CTHREAD_HPP_

