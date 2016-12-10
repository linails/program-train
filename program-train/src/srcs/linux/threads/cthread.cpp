/*
 * Progarm Name: cthread.cpp
 * Created Time: 2016-12-07 11:26:43
 * Last modified: 2016-12-10 13:16:53
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

