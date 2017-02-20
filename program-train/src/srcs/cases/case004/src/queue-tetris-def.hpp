/*
 * Progarm Name: queue-tetris-def.hpp
 * Created Time: 2017-02-17 10:26:04
 * Last modified: 2017-02-20 17:25:39
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
    int  pop(T &x, bool flag = true);
    int  pop(T &expec, T &x, bool flag = true);
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
    int  is_empty(int tid) const;
    int  push_left(int &dev, T &left);
    int  push_right(int &tid, T &right);
    int  push_left(pair<int, int> &indicate, T &left); /* <tid, dev> */
    int  error_check(pair<int, int> &err_pair) const;
private:
    int  decrease(int tid); /* clear buttom layer */
    int  check_tid_left_status(int tid, int status); /* same return 0 */
    int  check_tid_right_status(int tid, int &status);
private:
    map<int, int>                                       m_devs_tid;
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
int  QueueTetris<T>::pop(T &x, bool flag)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        x = this->m_data.front();
        if(true == flag){
            this->m_data.pop_front();
        }
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  QueueTetris<T>::pop(T &expec, T &x, bool flag)
{
    int ret = 0;

    if(false == this->m_data.empty()){
        auto iter = find(this->m_data.begin(), this->m_data.end(), expec);
        if(iter != this->m_data.end()){
            x = *iter;
            if(true == flag)
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
    for(auto iter = this->m_tid_devs.begin();
             iter!= this->m_tid_devs.end(); iter++){
        for(auto ui : iter->second){
            this->m_devs_tid[ui] = iter->first;
        }
    }
}

template <typename T>
Tetris<T>::~Tetris()
{
}

template <typename T>
int  Tetris<T>::add_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(data.first);

    if(iter != this->m_tid_devs.end()){
        vector<int> old_members = this->m_tid_devs[data.first];

        this->m_tid_devs[data.first] = data.second;

        for(auto u : old_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        for(auto u : this->m_tid_devs[data.first]){
            this->m_devs_tid[u] = data.first;
        }
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::update_tid(pair<int, vector<int> > &data) /* pair<tid - <devs>> */
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(data.first);

    if(iter != this->m_tid_devs.end()){
        vector<int> old_members = this->m_tid_devs[data.first];

        this->m_tid_devs[data.first] = data.second;

        for(auto u : old_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        for(auto u : this->m_tid_devs[data.first]){
            this->m_devs_tid[u] = data.first;
        }
        // todo
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::del_tid(int tid)
{
    int ret = 0;
    auto iter = this->m_tid_devs.find(tid);

    if(iter != this->m_tid_devs.end()){
        vector<int> del_members = this->m_tid_devs[tid];

        for(auto u : del_members){
            auto iter_u = this->m_devs_tid.find(u);
            if(iter_u != this->m_devs_tid.end()){
                this->m_devs_tid.erase(iter_u);
            }else{
                cout << "[Error] Line = " << __LINE__ << endl;
            }
        }

        this->m_tid_devs.erase(iter);
    }else
        ret = -1;

    return ret;
}

template <typename T>
int  Tetris<T>::is_empty(void) const
{
    if(true != this->m_queue_tetris.empty()){
        return -1;
    }
    return 0;
}

template <typename T>
int  Tetris<T>::is_empty(int tid) const
{
    int ret = 0;

    vector<int> members = this->m_tid_devs[tid];

    for(auto u : members){
        if(0 != std::get<0>(this->m_queue_tetris[u]).is_empty()){
            ret = -1;
            break;
        }
        if(0 != std::get<1>(this->m_queue_tetris[u]).is_empty()){
            ret = -1;
            break;
        }
    }

    return ret;
}

template <typename T>
int  Tetris<T>::push_left(int &dev, T &left)
{
#if 0
    this->error_check();

    while(-1 != this->decrease()){
    }

#endif
    return 0;
}

template <typename T>
int  Tetris<T>::push_right(int &tid, T &right)
{
    vector<int> members = this->m_tid_devs[tid];

    for(auto u : members){
        auto iter = this->m_queue_tetris.find(u);
        if(iter != this->m_queue_tetris.end()){
            std::get<1>(*iter).push(right);
        }else{
            QueueTetris<T> qleft;
            QueueTetris<T> qright;

            qright.push(right);

            this->m_queue_tetris.insert(make_pair(u, make_tuple(qleft, qright)));
        }
    }

    return 0;
}

template <typename T>
int  Tetris<T>::push_left(pair<int, int> &indicate, T &left) /* <tid, dev> */
{
    return 0;
}

template <typename T>
int  Tetris<T>::error_check(pair<int, int> &err_pair) const
{
    return 0;
}

template <typename T>
int  Tetris<T>::decrease(int tid) /* clear buttom layer */
{
    int status_right;
    int status_left;

    if(-1 != this->check_tid_right_status(tid, status_right)){
        if(-1 != this->check_tid_left_status(tid, status_right)){
            vector<int> members = this->m_tid_devs[tid];
            for(auto u : members){
                if(0 != std::get<1>(this->m_queue_tetris[u]).pop(status_right)){
                    cout << "[Error] Line = " << __LINE__ << endl;
                    return -1;
                }
                if(0 != std::get<0>(this->m_queue_tetris[u]).pop(status_right, status_left)){
                    cout << "[Error] Line = " << __LINE__ << endl;
                    return -1;
                }
            }
        }
    }else
        return -1;

    return 0;
}

template <typename T>
int  Tetris<T>::check_tid_left_status(int tid, int status) /* same return 0 */
{
    vector<int> members = this->m_tid_devs[tid];

    if(0 > members.size()){
        cout << "[Error] Line = " << __LINE__ << " - tid-devs size() = 0 " << endl;
        return -1;
    }

    int ret = 0;

    for(auto u : members){
        int status_tmp = 0;
        if(0 != std::get<0>(this->m_queue_tetris[u]).pop(status, status_tmp, false)){
            ret = -1;
            break;
        }
    }

    return ret;
}

template <typename T>
int  Tetris<T>::check_tid_right_status(int tid, int &status)
{
    vector<int> members = this->m_tid_devs[tid];

    if(0 < members.size()){
        if(0 != std::get<1>(this->m_queue_tetris[members[0]]).pop(status, false)){
            cout << "[Error] Line = " << __LINE__ << endl;
            status = -1;
            return -1;
        }
    }else{
        cout << "[Error] Line = " << __LINE__ << " - tid-devs size() = 0 " << endl;
        return -1;
    }

    for(auto u : members){
        int status_tmp = 0;
        if(-1 != std::get<1>(this->m_queue_tetris[u]).pop(status_tmp, false)){
            if(status_tmp != status){
                cout << "[Error] Line = " << __LINE__ << endl;
                status = -1;
                return -1;
            }
        }
    }

    return 0;
}

#endif //_QUEUE_TETRIS_DEF_HPP_

