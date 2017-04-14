/*
 * Progarm Name: cthread.cpp
 * Created Time: 2016-12-07 11:26:43
 * Last modified: 2016-12-16 22:07:45
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cthread.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "timer.h"

using std::cout;
using std::endl;
using std::string;

Timer cThread::timer0;
Timer cThread::timer1;

/* 
 * #include <pthread.h>
 *
 * int pthread_create(
 *     pthread_t *restrict thread, const pthread_attr_t *restrict attr,
 *     void *(* start_routine)(void *), void *restrict arg
 * );
 *  -> 成功返回0， 失败返回其他值
 *  -- thread   : 保存新创建线程 ID 的变量地址值，线程与进程相同，也需要用于区分不同线程的ID
 *  -- attr     : 用于传递线程属性的参数，传递NULL时，创建默认属性的线程
 *  -- start_routine : 相当于线程 main 函数的、在单独执行流中执行的函数地址值(函数指针)
 *  -- arg      : 通过第三个参数传递调用函数时包含传递参数信息的变量地址值
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 销毁线程的3种方法
 *  1> 调用 pthread_join
 *      这个函数在线程终止前，会进入阻塞状态
 *
 *  2> 调用 pthread_detach
 *      #include <pthread.h>
 *
 *      int pthread_detach(pthread_t thread);
 *          -> 成功返回0，失败返回其他值
 *          -- thread : 终止的同时需要销毁的线程ID
 *
 *          调用此函数不会引起线程终止或进入阻塞状态，可以通过该函数引导销毁线程创建的内存空间
 *
 * */
cThread::cThread()
{
    cout << " cThread init ..." << endl;
}

cThread::~cThread()
{
}

int cThread::cthread_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->timing_create_thread();

    return ret;
}

/* 
 * 用于粗略检测创建线程所需要的时间 
 *  
 *  本机测试创建线程需要 300-2000us 的时间
 * */
int  cThread::timing_create_thread(void)
{
    int ret = 0;

    /* Timing ... */
    timer0.timing();
    timer1.timing();

    pthread_t   child_thread;
    void       *thread_result;

    if(0 != (ret = pthread_create(&child_thread, NULL, cThread::child, (void *)"child - thread 001"))){
        perror("child-thread creation failed!");
        exit(EXIT_FAILURE);
    }

    /* Timing Stop ... For created process successed */
    cout << endl;
    cout << "parent thread : " ;
    timer0.timing();

    if(0 != (ret = pthread_join(child_thread, &thread_result))){
        perror("child_thread join failed!");
        exit(EXIT_FAILURE);
    }

    return ret;
}

void *cThread::child(void *arg)
{
    cout << endl;
    cout << "child thread : " ;
    timer1.timing();

    if(NULL != arg){
        cout << "child arg : " << string((char *)arg) << endl;
    }else{
        cout << "child arg is null" << endl;
    }

    pthread_exit((void *)"end child thread ...");
}


