/*
 * Progarm Name: container.cpp
 * Created Time: 2016-12-20 17:17:15
 * Last modified: 2017-01-02 19:53:57
 * @author: minphone.linails linails@foxmail.com 
 */

#include "container.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <map>
#include <typeinfo>
#include <bitset>
#include <list>
#include <queue>
#include <deque>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::list;

Container::Container()
{
}

Container::~Container()
{
}

int  Container::container_main(int argc, char **argv)
{
    int ret = 0;

    //ret = this->container_test(); assert(-1 == ret);
    
    ret = this->vector_t(); assert(-1 != ret);
    
    ret = this->list_t(); assert(-1 != ret);

    return ret;
}

int  Container::vector_t(void)
{
    int ret = 0;

    {
        auto fp = [](vector<int> iv){
            cout << "iv : ";
            for(auto id : iv) {
                cout << id << " ";
            }
            cout << endl;
        };

        vector<int> iv;

        iv.push_back(1);
        iv.push_back(2);
        iv.push_back(3);
        iv.push_back(4);
        iv.push_back(5);

        fp(iv);

        auto iter = find(iv.begin(), iv.end(), 3);
        if(iter != iv.end()){
            cout << "find it and delete it" << endl;

            /* 
             * iterator erase(iterator it)  : 删除向量中某一个元素
             * iterator erase(iterator first, iterator last)  : 删除向量[first, last)
             * */
            iv.erase(iter);
            fp(iv);
        }
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::list_t(void)
{
    int ret = 0;

    {
        auto fp = [](list<int> &li){
            cout << "li : ";
            for(auto id : li) {
                cout << id << " ";
            }
            cout << endl;
        };

        list<int> li;
        li.push_back(1);
        li.push_back(2);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(4);
        li.push_back(5);

        fp(li);

        /* 
         *  <<STL源码剖析>>
         *  iterator list<>::erase(iterator position){
         *      ...
         *      return iterator(next_node);
         *  }
         * */
        #if 1
        for(auto iter = li.begin();
                 iter!= li.end();){
            if(*iter == 3) {
                iter = li.erase(iter);
            }else{
                iter++;
            }
        }
        #else
        auto iter = li.begin();

        while(iter != li.end()){
            if(*iter == 3){
                iter = li.erase(iter);
            }else{
                iter++;
            }
        }
        #endif

        fp(li);
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

