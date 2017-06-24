/*
 * Progarm Name: cthread.cpp
 * Created Time: 2016-12-07 11:26:43
 * Last modified: 2017-06-24 23:12:59
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
pthread_mutex_t  cThread::m_mtx;

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

    //ret = this->deadlock_test_for_mutex();

    ret = this->normal_test_for_mutex();

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

void *cThread::odd_deadlock(void *arg)
{
    printf("cThread::odd_deadlock() ...\n");

    for(int i=1; ; i+= 2){
        pthread_mutex_lock(&m_mtx);
        printf("odd : %d\n", i);
        usleep(500 * 1000);
        pthread_mutex_unlock(&m_mtx);

        usleep(10);
    }

    pthread_exit((void *)"end odd_deadlock thread ...");
}

/* 
 * 运用两个宏函数就可以解决 deadlock_test_for_mutex() 中出现的一个线程异常退出后引起死锁的问题
 *  1> pthread_cleanup_push
 *  2> pthread_cleanup_pop | 这个对函数的作用类似于 atexit 函数
 *
 *  这两个宏函数，必须成对使用
 *
 *  // 会将参数 routine 所含的函数地址添加到调用线程的清理函数栈顶
 *  void pthread_cleanup_push(
 *      void (*routine)(void *),    //
 *      void *arg                   // 回调函数 routine 的参数
 *  );
 *
 *  void pthread_cleanup_pop(int execute);
 * */
void *cThread::odd_nornal(void *arg)
{
    printf("cThread::odd_nornal() ...\n");

    char *str = (char *)"msg from odd_nornal()";

    for(int i=1; ; i+= 2){

        pthread_cleanup_push(cThread::routine, (void *)str);

        pthread_mutex_lock(&m_mtx);
        printf("odd : %d\n", i);
        usleep(500 * 1000);
        pthread_mutex_unlock(&m_mtx);

        usleep(10);

        pthread_cleanup_pop(0);
    }

    pthread_exit((void *)"end odd_nornal thread ...");
}

void *cThread::even_deadlock(void *arg)
{
    printf("cThread::even_deadlock() ...\n");

    for(int i=0; ; i+= 2){
        pthread_mutex_lock(&m_mtx);
        printf("even : %d\n", i);
        usleep(500 * 1000);
        pthread_mutex_unlock(&m_mtx);

        usleep(10);
    }

    pthread_exit((void *)"end even_deadlock thread ...");
}

void *cThread::even_normal(void *arg)
{
    printf("cThread::even_normal() ...\n");

    for(int i=0; ; i+= 2){

        pthread_cleanup_push(cThread::routine, NULL);

        pthread_mutex_lock(&m_mtx);
        printf("even : %d\n", i);
        usleep(500 * 1000);
        pthread_mutex_unlock(&m_mtx);

        usleep(10);

        pthread_cleanup_pop(0);
    }

    pthread_exit((void *)"end even_normal thread ...");
}

int  cThread::deadlock_test_for_mutex(void)
{
    int ret = 0;

    printf("cThread::deadlock_test_for_mutex ...\n");
    {
        pthread_t odd_thread;
        pthread_t even_thread;

        void *tr0 = NULL;
        void *tr1 = NULL;

        pthread_mutex_init(&m_mtx, 0);

        if(0 != (ret = pthread_create(&odd_thread, NULL, cThread::odd_deadlock, NULL))){
            perror("odd-thread creation failed!");
            exit(EXIT_FAILURE);
        }

        if(0 != (ret = pthread_create(&even_thread, NULL, cThread::even_deadlock, NULL))){
            perror("even-thread creation failed!");
            exit(EXIT_FAILURE);
        }

        {
            printf("Start sleep ......................\n");
            sleep(2);
            printf("End sleep ......................\n");
        }


        /* 
         * 取消 odd_thread 线程 , 类似于外部强制停止 odd 线程
         * */
        pthread_cancel(odd_thread);


        /* 
         * Join ...
         * */
        if(0 != (ret = pthread_join(odd_thread, &tr0))){
            perror("odd_thread join failed!");
            exit(EXIT_FAILURE);
        }

        if(0 != (ret = pthread_join(even_thread, &tr1))){
            perror("even_thread join failed!");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_destroy(&m_mtx);
    }

    printf("-----------------------------------------\n");
    return ret;
}

int  cThread::normal_test_for_mutex(void)
{
    int ret = 0;

    printf("cThread::normal_test_for_mutex ...\n");
    {
        pthread_t odd_thread;
        pthread_t even_thread;

        void *tr0 = NULL;
        void *tr1 = NULL;

        pthread_mutex_init(&m_mtx, 0);

        if(0 != (ret = pthread_create(&odd_thread, NULL, cThread::odd_nornal, NULL))){
            perror("odd-thread creation failed!");
            exit(EXIT_FAILURE);
        }

        if(0 != (ret = pthread_create(&even_thread, NULL, cThread::even_normal, NULL))){
            perror("even-thread creation failed!");
            exit(EXIT_FAILURE);
        }

        {
            printf("Start sleep ......................\n");
            sleep(2);
            printf("End sleep ......................\n");
        }


        /* 
         * 取消 odd_thread 线程 , 类似于外部强制停止 odd 线程
         * */
        pthread_cancel(odd_thread);


        /* 
         * Join ...
         * */
        if(0 != (ret = pthread_join(odd_thread, &tr0))){
            perror("odd_thread join failed!");
            exit(EXIT_FAILURE);
        }

        if(0 != (ret = pthread_join(even_thread, &tr1))){
            perror("even_thread join failed!");
            exit(EXIT_FAILURE);
        }

        pthread_mutex_destroy(&m_mtx);
    }

    printf("-----------------------------------------\n");
    return ret;
}

void cThread::routine(void *d)
{
    printf("cThread::routine() exit and cleanup ...\n");
    {
        if(NULL != d){
            printf("routine() : msg = %s\n", (char *)d);
        }
    }

    pthread_mutex_unlock(&m_mtx);
}

