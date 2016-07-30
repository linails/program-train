/*
 * Progarm Name: condition_variable.cpp
 * Created Time: 2016-07-30 09:40:53
 * Last modified: 2016-07-30 10:05:04
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

    while(false == ready){
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

void cv_main(void)
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

