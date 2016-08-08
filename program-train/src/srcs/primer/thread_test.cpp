/*
 * Progarm Name: thread_test.cpp
 * Created Time: 2016-07-14 19:20:23
 * Last modified: 2016-07-30 22:42:09
 * @author: minphone.linails linails@foxmail.com 
 */

#include "thread_test.h"
#include "sync_queue.h"
#include "condition_variable.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <mutex>
#include <typeinfo>

/* 
 * C++11 thread 
 * */
#include <thread>

using namespace std;

vector<thread> g_list;
vector<shared_ptr<thread> > g_list2;


void thread_test(void)
{
    cout << "func : " << __FUNCTION__ << endl;
#if 0
    {
        void func(void);

        thread t(func);

        /* join函数将会阻塞线程，直到线程函数执行结束，
         * 如果线程函数有返回值，返回值将被忽略*/
        t.join();

        cout << "thread.join()" << endl;
    }
    cout << "----------------------------" << endl;
    {
        /* 如果不希望线程被阻塞执行，可以用线程的detach()方法，
         * 将线程和线程对象分离
         * 则分离出来的线程将独立运行*/

        void func(void);

        thread t(func);

        t.detach();

        cout << "thread.detach() " << endl;
    }
#endif
    cout << "----------------------------" << endl;
    {
        void func1(int a, int b, string s);

        /* 涉及到传参数的时候，特别需要注意join，否则会
         * 引起 core dumped */
        thread t(func1, 1, 2, "nice");

        t.join();
    }
    cout << "----------------------------" << endl;
    {
        void func1(int a, int b, string s);
        thread t(func1, 1, 2, "nice");
        thread t1(move(t));

        /* 线程被移走后，原来的 t 对象就不代表任何线程 */
        //t.join();
        t1.join();
    }
    cout << "----------------------------" << endl;
    {
        void create_thread(void);
        create_thread();

        for(auto &thread : g_list){
            thread.join();
        }

        for(auto &thread : g_list2){
            thread->join();
        }
    }
    cout << "----------------------------" << endl;
    {
        void func(void);
        thread t(func);

        cout << "ID : " << t.get_id() << endl;
        cout << "获取CPU核数：" << thread::hardware_concurrency() << endl;

        t.join();
    }
    cout << "----------------------------" << endl;
    {
        /* C++11提供了4种互斥锁
         * std::mutex:独占的互斥锁，不能递归使用
         * std::timed_mutex:带超时的独占互斥锁，不能递归使用
         * std::recursive_mutex:递归互斥锁，不带超时功能
         * std::recursive_timed_mutex:带超时的递归互斥锁*/

        void func2(void);

        thread t1(func2);
        thread t2(func2);
        thread t3(func2);

        t1.join();
        t2.join();
        t3.join();
    }
    cout << "----------------------------" << endl;
    {

        /* recursive_mutex
         * 递归锁，允许同一线程多次获得该互斥锁，
         * 可以用来解决同一线程需要多次获取互斥量时死锁的问题*/

        #define RECURSIVE_ONOFF 1

        struct Comples{
            #if(RECURSIVE_ONOFF)
            recursive_mutex mux;
            #else
            mutex   mux;
            #endif
            int i;

            Comples(void): i(0){}
            void mul(int x){
                cout << "func : " << __FUNCTION__ << endl;
                #if(RECURSIVE_ONOFF)
                lock_guard<recursive_mutex> lock(mux);
                #else
                lock_guard<mutex> lock(mux);
                #endif
                i *= x;
            }

            void div(int x){
                cout << "func : " << __FUNCTION__ << endl;
                #if(RECURSIVE_ONOFF)
                lock_guard<recursive_mutex> lock(mux);
                #else
                lock_guard<mutex> lock(mux);
                #endif
                i /= x;
            }

            void both(int x, int y){
                cout << "func : " << __FUNCTION__ << endl;
                #if(RECURSIVE_ONOFF)
                lock_guard<recursive_mutex> lock(mux);
                #else
                lock_guard<mutex> lock(mux);
                #endif
                mul(x);
                div(y);
            }
        };

        Comples comples;
        comples.both(32, 23);
        /* 递归锁 用于函数调用同一个深度的资源互斥使用
         * 1）需要用到递归锁的多线程互斥处理往往本身就是可以简化的
         * 2）递归锁比起非递归锁，效率会低一些*/
    }
    cout << "----------------------------" << endl;
    {
        /* 条件变量是c++11提供的另外一个用于等待的同步机制，
         * 它能阻塞一个或多个线程，
         * 直到收到另外一个线程发出的通知或者超时，
         * 才会唤醒当前阻塞的线程
         *
         * 条件变量需要和互斥量配合使用
         *
         * 1.condition_variable,配合unique_lock<mutex> 进行wait操作
         * 2.condition_variable_any,和任意带有lock,unlock语义的mutex配合使用，
         *   比较灵活，但效率比condition_variable差一些*/
        cv_main();
    }
    cout << "----------------------------" << endl;
    {
        chrono::duration<double, ratio<9, 7>> d1(3);
        chrono::duration<double, ratio<6, 5>> d2(1);

        auto d3 = d1 - d2;
        cout << typeid(d3).name() << endl;
        cout << d3.count() << endl;
    }



    cout << "----------------------------" << endl;
    {
#if 0
        cout << "sleep 10 seconds" << endl;
        sleep(10);
        cout << "return" << endl;
#endif
    }
}

void func(void)
{
    cout << " ---->thread func : ";
    cout << "do some work " << endl;

    //sleep(1);

    /* C++11 sleep */
    this_thread::sleep_for(chrono::seconds(1));

    cout << " ---->exit" << endl;
}

void func1(int a, int b, string s)
{
    cout << "---->thread func1 : ";
    cout << "a = " << a << " b = " << b << " s = " << s << endl;
}


void create_thread(void)
{
    thread t(func);
    g_list.push_back(move(t));

    g_list2.push_back(make_shared<thread>(func));
}

mutex g_lock;

void func2(void)
{
    g_lock.lock();

    cout << "entered thread " << this_thread::get_id() << endl;
    
    this_thread::sleep_for(chrono::seconds(1));
    cout << "leaving thread " << this_thread::get_id() << endl;

    g_lock.unlock();
}

void func3(void)
{
    /* lock_guard 可以简化 lock/unlock 的写法，同时也更安全 
     *
     * lock_guard 在构造时，会自动锁定互斥量，
     *  退出作用域后会进行析构进行自动解锁*/
    lock_guard<mutex> locker(g_lock);

    cout << "entered thread " << this_thread::get_id() << endl;
    
    this_thread::sleep_for(chrono::seconds(1));
    cout << "leaving thread " << this_thread::get_id() << endl;
}




