/*
 * Progarm Name: sync_queue.h
 * Created Time: 2016-07-29 22:49:09
 * Last modified: 2016-07-30 09:09:15
 */

#ifndef _SYNC_QUEUE_H_
#define _SYNC_QUEUE_H_

#include <mutex>
#include <thread>
#include <condition_variable>
#include <list>
#include <iostream>

/* 条件变量的使用过程：
 * 1.拥有条件变量的线程获取互斥量
 * 2.循环检查某个条件，如果条件不满足，则阻塞直到条件满足；
 *   如果条件满足，则向下执行
 * 3.某个线程满足条件执行完之后，调用notify_one(唤醒一个等待线程) / notify_all(唤醒所有等待线程)*/
template<typename T>
class SyncQueue{
public:
    SyncQueue(int maxSize):m_maxSize(maxSize){};
    ~SyncQueue();
    void put(const T& x){
        std::lock_guard<std::mutex> locker(this->m_mutex);
        while(IsFull()){
            std::cout << "cache is full , waiting ... " << std::endl;
            this->m_notFull.wait(this->m_mutex);
        }

        this->m_queue.push_back(x);
        this->m_notFull.notify_one();
    }
    void take(T& x){
        std::lock_guard<std::mutex> locker(this->m_mutex);
        while(IsEmpty()){
            std::cout << "cache is empty, waiting ..." << std::endl;
            this->m_notEmpty.wait(this->m_mutex);
        }

        x = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }
    bool empty(void){
        std::lock_guard<std::mutex> locker(this->m_mutex);
        return this->m_queue.empty();
    }
    bool full(void){
        std::lock_guard<std::mutex> locker(this->m_mutex);
        return this->m_queue.size() == this->m_maxSize;
    }
    size_t Size(void){
        std::lock_guard<std::mutex> locker(this->m_mutex);
        return this->m_queue.size();
    }
    int Count(void){
        return this->m_queue.size();
    }
private:
    bool IsFull(void) const{
        return m_queue.size() == this->m_maxSize;
    }
    bool IsEmpty(void) const{
        return m_queue.empty();
    }
private:
    std::list<T>    m_queue;
    std::mutex      m_mutex;
    std::condition_variable_any m_notEmpty;
    std::condition_variable_any m_notFull;
    int             m_maxSize;  /* sync queue max size */
};



#endif //_SYNC_QUEUE_H_

