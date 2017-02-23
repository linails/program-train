/*
 * Progarm Name: container.cpp
 * Created Time: 2016-12-20 17:17:15
 * Last modified: 2017-02-23 09:32:10
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
using std::tuple;
using std::make_pair;
using std::make_tuple;

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

