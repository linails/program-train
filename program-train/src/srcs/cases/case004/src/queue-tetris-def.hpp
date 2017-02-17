/*
 * Progarm Name: queue-tetris-def.hpp
 * Created Time: 2017-02-17 10:26:04
 * Last modified: 2017-02-17 17:26:43
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _QUEUE_TETRIS_DEF_HPP_
#define _QUEUE_TETRIS_DEF_HPP_

#include <list>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using std::list;
using std::tuple;
using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

template <typename T>
class QueueTetris{
public:
    QueueTetris();
    ~QueueTetris();
    int  push(T x);
    int  pop(T &x);
    int  pop(T &expec, T &x);
    int  is_empty(void) const;
    int  size(void) const;
private:
    list<T>     m_data;
};

template <typename T>
class Tetris{
public:
    Tetris(map<int, vector<int> > &data); /* map<tid - <devs>> */
    ~Tetris();
    int  add_tid(pair<int, vector<int> > &data); /* pair<tid - <devs>> */
    int  update_tid(pair<int, vector<int> > &data); /* pair<tid - <devs>> */
    int  del_tid(int tid);
    int  is_empty(void) const;
    int  push_left(pair<int, int> &indicate, T &left);
    int  push_right(pair<int, int> &indicate, T &right);
    int  error_check(pair<int, int> &err_pair) const;
private:
    int  decrease(void); /* clear buttom layer */
private:
    map<int, vector<int> >                              m_tid_devs;
    map<int, tuple<QueueTetris<T>, QueueTetris<T> > >   m_queue_tetris;
};

//-----------------------------------------------------------------------------

template <typename T>
QueueTetris<T>::QueueTetris()
{
}

template <typename T>
QueueTetris<T>::~QueueTetris()
{
}

template <typename T>
int  QueueTetris<T>::push(T x)
{
    this->m_data.push_back(x);
    return 0;
}

template <typename T>
int  QueueTetris<T>::pop(T &x)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        x = this->m_data.front();
        this->m_data.pop_front();
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  QueueTetris<T>::pop(T &expec, T &x)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        auto iter = find(this->m_data.begin(), this->m_data.end(), expec);
        if(iter != this->m_data.end()){
            x = *iter;
            this->m_data.erase(iter);
        }else
            ret = -1;
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  QueueTetris<T>::is_empty(void) const
{
    return this->m_data.empty() ? 0 : -1;
}

template <typename T>
int  QueueTetris<T>::size(void) const
{
    return this->m_data.size();
}

template <typename T>
Tetris<T>::Tetris(map<int, vector<int> > &data) /* map<tid - <devs>> */
    :m_tid_devs(data)
{
}

template <typename T>
Tetris<T>::~Tetris()
{
}

template <typename T>
int  Tetris<T>::add_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    return 0;
}

template <typename T>
int  Tetris<T>::update_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    return 0;
}

template <typename T>
int  Tetris<T>::del_tid(int tid)
{
    return 0;
}

template <typename T>
int  Tetris<T>::is_empty(void) const
{
    return 0;
}

template <typename T>
int  Tetris<T>::push_left(pair<int, int> &indicate, T &left)
{
    return 0;
}

template <typename T>
int  Tetris<T>::push_right(pair<int, int> &indicate, T &right)
{
    return 0;
}

template <typename T>
int  Tetris<T>::error_check(pair<int, int> &err_pair) const
{
    return 0;
}

#endif //_QUEUE_TETRIS_DEF_HPP_

