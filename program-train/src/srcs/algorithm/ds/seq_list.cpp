/*
 * Progarm Name: seq_list.cpp
 * Reference : <<数据结构：用面向对象方法与C++语言描述>>
 * Created Time: 2016-08-27 08:43:55
 * Last modified: 2016-08-28 10:34:09
 * @author: minphone.linails linails@foxmail.com 
 */

#include "seq_list.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

template <typename T>
SeqList<T>::SeqList(int sz)
{
    if(sz > 0){
        this->last      = -1;
        this->max_size  = sz;

        this->data      = new T[this->max_size];
        if(NULL == this->data){
            cout << "new T[max_size] err!" << endl;
            exit(1);
        }
    }
}

template <typename T>
SeqList<T>::SeqList(SeqList<T> &L)
{
    this->max_size  = L.size();
    this->last      = L.length() - 1;

    this->data      = new T[this->max_size];
    if(NULL == this->data){
        cout << "new T[max_size] err !" << endl;
        exit(1);
    }

    for(int i=0; i<L.length(); i++){
        this->data[i] = L.get_data(i);
    }
}


