/*
 * Progarm Name: test-avl-tree.cpp
 * Created Time: 2017-03-23 14:20:51
 * Last modified: 2017-03-30 15:58:59
 * @author: minphone.linails linails@foxmail.com 
 */

#include "test-avl-tree.hpp"
#include <iostream>
#include "dev-avl-tree.hpp"
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include <cstdio>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::tuple;
using std::make_pair;
using std::make_tuple;

TesterAVLTree::TesterAVLTree()
{
}

TesterAVLTree::~TesterAVLTree()
{
}

int  TesterAVLTree::insert(void)
{
    auto set_val = [](device_tsl_t &tsl, int &time, int key, string status, int time_val){
        tsl.id      = key;
        tsl.status  = status;
        time        = time_val;
    };

    auto visit = [](avlNode *node) -> int{
        #if 0
        cout << "visit : " << node->m_key << endl;
        #else
        printf("key: %d height: %d ", node->m_key, node->m_height);
        if(nullptr != node->m_left)  printf("left child: %d ", node->m_left->m_key);
        if(nullptr != node->m_right) printf("right child: %d ", node->m_right->m_key); printf("\n");
        #endif
        return 0;
    };

    cout << "--------------------------------------------" << endl;
    {
        cout << "avl-tree insert" << endl;

        DevAVLTree tree;
        device_tsl_t tsl;
        int          time = 2017;

        {
            set_val(tsl, time, 15, "string 15", 15); tree.insert(tsl, time);
            set_val(tsl, time,  6, "string  6",  6); tree.insert(tsl, time);
            set_val(tsl, time, 18, "string 18", 18); tree.insert(tsl, time);
            set_val(tsl, time,  3, "string  3",  3); tree.insert(tsl, time);
            set_val(tsl, time,  7, "string  7",  7); tree.insert(tsl, time);
            set_val(tsl, time, 17, "string 17", 17); tree.insert(tsl, time);
            set_val(tsl, time, 20, "string 20", 20); tree.insert(tsl, time);
            set_val(tsl, time,  2, "string  2",  2); tree.insert(tsl, time);
            set_val(tsl, time,  4, "string  4",  4); tree.insert(tsl, time);
            set_val(tsl, time, 13, "string 13-1", 2013); tree.insert(tsl, time);
            set_val(tsl, time, 13, "string 13-2", 2017); tree.insert(tsl, time);
            set_val(tsl, time, 13, "string 13-3", 2018); tree.insert(tsl, time);

            tree.in_order(visit);

            {
                map<int, device_tsl_t> nodes;
                int n = 13;
                if(-1 != tree.search(n, nodes)){ // key = device_tsl_t.id
                    cout << endl;
                    cout << "search(n) | n = " << n << endl;
                    cout << "tsl.id = " << tsl.id << endl;
                    for(auto &u : nodes){
                        printf("status -> time : ( %s -> %d )\n", u.second.status.c_str(), u.first);
                    }
                }else{
                    printf("search(%d) | return -1\n", n);
                }
            }
            {
                map<int, device_tsl_t> nodes;
                int n = 16;
                if(-1 != tree.search(n, nodes)){ // key = device_tsl_t.id
                    cout << endl;
                    cout << "search(n) | n = " << n << endl;
                    cout << "tsl.id = " << tsl.id << endl;
                    for(auto &u : nodes){
                        printf("status -> time : ( %s -> %d )\n", u.second.status.c_str(), u.first);
                    }
                }else{
                    cout << "[Warning] search(16) | return -1" << endl;
                }
            }
        }

    }
    cout << "--------------------------------------------" << endl;
    return 0;
}

