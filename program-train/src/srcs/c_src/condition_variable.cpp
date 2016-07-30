/*
 * Progarm Name: condition_variable.cpp
 * Created Time: 2016-07-30 09:40:53
 * Last modified: 2016-07-30 22:07:29
 */

#include "condition_variable.h"
#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <chrono>
#include <unistd.h>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void do_print_id(int id)
{
#if 1
    unique_lock<mutex> locker(mtx);
    int i = 0;

    while(false == ready){
        cout << "while " << i++ << endl;
        /* 进入wait 状态后，线程就相当于是被挂起等待，
         * 不消耗cpu资源
         * 相比于不断的进行轮询，对cpu的利用效率提升很多*/
        cv.wait(locker);
    }
#else
    while(false == ready){}
#endif
    cout << "thread " << id << " - " << ready << endl;
}

void go(void)
{
#if 1
    unique_lock<mutex> locker(mtx);

    ready = true;

    /* wake up all threads */
    cv.notify_all();

    //cv.notify_one();
#else
    ready = true;
#endif
}

/* std::once_flag */
once_flag flag;

void do_once(void)
{
    call_once(flag, []{cout << "called once" << endl;});
}

void do_multi(void)
{
    cout << "multi..." << endl;
}

void cv_main(void)
{
    {
        thread threads[10];
        for(int i=0; i<10; i++){
            threads[i] = thread(do_print_id, i);
        }

        cout << "10 threads ready to race..." << endl;

        /* C++11 sleep */
        this_thread::sleep_for(chrono::seconds(2));
        //sleep(2);

        go();

        for(auto &th : threads) th.join();
    }
    cout << "----------------------------" << endl;
    {
        thread ths[5];
        for(auto &th: ths)  th = thread(do_multi);
        for(auto &th: ths)  th.join();
    }
    cout << "----------------------------" << endl;
    {
        thread ths[10];
        for(auto &th: ths)  th = thread(do_once);
        for(auto &th: ths)  th.join();
    }
}

