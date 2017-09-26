/*
 * Progarm Name: worker-thread.hpp
 * Created Time: 2017-02-16 15:47:40
 * Last modified: 2017-02-16 16:06:49
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _WORKER_THREAD_HPP_
#define _WORKER_THREAD_HPP_

#include <string>
#include <vector>
#include <thread>

using std::thread;
using std::string;
using std::vector;

class WorkerThread{
public:
    WorkerThread();
    ~WorkerThread();
    int  init(void);
    int  uninit(void);
private:
private:
    thread     *m_thread = nullptr;
};

#endif //_WORKER_THREAD_HPP_

