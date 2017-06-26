/*
 * Progarm Name: container.cpp
 * Created Time: 2016-12-20 17:17:15
 * Last modified: 2017-06-26 10:26:28
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
#include <stack>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::list;
using std::tuple;
using std::make_pair;
using std::make_tuple;
using std::stack;

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

    ret = this->map_t(); assert(-1 != ret); 

    ret = this->stack_t(); assert(-1 != ret); 

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
    {
        vector<int> gids;
        gids.push_back(0);
        gids.push_back(0);
        gids.push_back(2);
        gids.push_back(4);
        gids.push_back(3);
        gids.push_back(5);
        gids.push_back(4);
        gids.push_back(1);
        gids.push_back(1);
        gids.push_back(5);
        gids.push_back(1);
        gids.push_back(2);
        gids.push_back(0);
        gids.push_back(3);
        gids.push_back(2);
        gids.push_back(5);
        gids.push_back(4);
        gids.push_back(1);
        gids.push_back(3);
        gids.push_back(5);

        auto print_gids = [](vector<int> &gids){
            cout << "gids :";
            for(auto i : gids) cout << " " << i;
            cout << endl;
        };

        print_gids(gids);

        sort(gids.begin(), gids.end()); print_gids(gids);

        auto iter = unique(gids.begin(), gids.end()); print_gids(gids);

        gids.resize(std::distance(gids.begin(), iter)); print_gids(gids);
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
    {
        list<char>  data_list;
        data_list.push_back('1');
        data_list.push_back('2');
        data_list.push_back('3');
        data_list.push_back('.');
        data_list.push_back('5');
        data_list.push_back('6');
        data_list.push_back('7');

        char forword = '.';

        /* 
         * 反向遍历的时候，不可以调用 erase 方法，因为这个时候的 iter 的类型和正向遍历的类型不一样
         * */
        //for(auto iter = data_list.rbegin(); iter!= data_list.rend();)
        for(auto iter = data_list.begin(); iter!= data_list.end();){

            if(*iter == forword){
                data_list.push_front(forword);

                iter = data_list.erase(iter);
                continue;
            }

            iter++;
        }

        cout << "data_list : ";
        for(auto iter = data_list.begin(); 
                 iter!= data_list.end(); iter++){
            cout << *iter << " ";
        }
        cout << endl;

    }
    cout << "-----------------------------------------" << endl;
    {
        typedef struct{
            int buf[10];
        }ArrayData_t;

        list<ArrayData_t> arrlist;

        ArrayData_t a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        ArrayData_t b = {10, 20, 30, 40, 50, 60, 70, 80, 90, 10};

        arrlist.push_back(a);
        arrlist.push_back(b);

        cout << "arrlist.size() : " << arrlist.size() << endl;

        for(auto &u : arrlist){
            cout << "u : ";
            for(int i=0; i<10; i++){
                cout << u.buf[i] << " ";
            }
            cout << endl;
        }
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::map_t(void)
{
    int ret = 0;

    {
        typedef map<string, list<tuple<int, string> > > BindDeviceSet_t;

        list<tuple<int, string> > li;
        BindDeviceSet_t binddev_set;

        li.push_back(make_tuple(1, "01"));
        li.push_back(make_tuple(2, "02"));
        li.push_back(make_tuple(3, "03"));

        binddev_set.insert(make_pair("g1", li));

        cout << "binddev_set.size() : " << binddev_set.size() << endl;

        auto iter = binddev_set.begin();

        for(auto &dev : iter->second){
            cout << "std::get<0>(dev) : " << std::get<0>(dev) << endl;
            cout << "std::get<1>(dev) : " << std::get<1>(dev) << endl;
        }
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::stack_t(void)
{
    int ret = 0;

    {
        auto stack_info = [](stack<int> &is){
            vector<int> copy;
            cout << "stack<int> : ";
            while(false == is.empty()){
                cout << is.top() << " ";
                copy.push_back(is.top());
                is.pop();
            }
            cout << endl;

            for(auto iter = copy.rbegin(); iter != copy.rend(); iter++) is.push(*iter);
        };

        stack<int> is;

        is.push(1);
        is.push(3);

        stack_info(is);
        stack_info(is);
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

