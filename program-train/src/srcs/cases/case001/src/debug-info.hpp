/*
 * Progarm Name: debug-info.hpp
 * Created Time: 2017-04-10 15:30:36
 * Last modified: 2017-04-11 17:18:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DEBUG_INFO_HPP_
#define _DEBUG_INFO_HPP_

#include "conflict-check.hpp"
#include <iostream>
#include <cstdio>
#include <map>

using std::cout;
using std::endl;
using std::map;
using std::pair;

#define     DEBUG_ON    1

void dprint_scene_tsl(map<int, device_t> &tsl_set, scene_tsl_t &tsl, size_t line)
{
    #if DEBUG_ON
    map<string, list<device_tsl_t> > crr = {
        {"con", tsl.conditions},
        {"res", tsl.results},
        {"rec", tsl.recovers}
    };

    printf("[debug] tsl scene : id(%d) - %s - time(%d) :  --Line(%d) \n",
            tsl.id,
            tsl.timetype ==1 ? "timing" : "delay",
            tsl.time,
            (int)line);

    for(auto u : crr){
        printf("[debug] %s(cnt|%d) :\n", u.first.c_str(),(int)u.second.size());
        for(auto &dtsl : u.second){
            printf("[debug]         %4.d - %s - dev(%4.d)\n",
                    dtsl.id,
                    dtsl.status.c_str(),
                    tsl_set[dtsl.id].id);
        }
    }

    cout << "----------------------------" << endl;
    #endif
}

void dprint_dev_tsl(device_tsl_t &tsl, size_t line)
{
    #if DEBUG_ON
    printf("[debug] tsl dev : id(%4.d) - %s  --Line(%d) \n",
            tsl.id,
            tsl.status.empty() == true ? "status is null" : tsl.status.c_str(),
            (int)line);

    cout << "----------------------------" << endl;
    #endif
}

void dprint_cs_tree(DevChildSiblingTree *tree, size_t line)
{
    #if DEBUG_ON
    if(nullptr != tree){
        auto visit = [](btNode *pos) -> int{
            cout << pos->m_key << " ";
            return 0;
        };

        printf("[debug] tree : ");
        tree->pre_order(visit);
        printf("  --Line(%d) \n", (int)line);
    }else{
        printf("[debug] Error - tree is nullptr  --Line(%d) \n", (int)line);
    }

    cout << "----------------------------" << endl;
    #endif
}

void dprint_avl_tree(DevAVLTree *avltree , size_t line)
{
    #if DEBUG_ON
    auto visit = [&line](avlNode *node) -> int{
        #if 0
        cout << "visit : " << node->m_key << endl;
        #else
        printf("[debug] avl-tree --Line(%d)\n", (int)line);
        printf("[debug] key: %d height: %d ", node->m_key, node->m_height);
        if(nullptr != node->m_left)  printf("[debug] left child: %d ", node->m_left->m_key);
        if(nullptr != node->m_right) printf("[debug] right child: %d ", node->m_right->m_key); printf("\n");
        #endif
        return 0;
    };

    if(nullptr != avltree){
        avltree->in_order(visit);
    }else{
        printf("[debug] Error - tree is nullptr  --Line(%d) \n", (int)line);
    }

    cout << "----------------------------" << endl;
    #endif
}

void dprint_tsl_time(pair<device_tsl_t *, int> &tsl_time, size_t line)
{
    #if DEBUG_ON
    if(nullptr != tsl_time.first){
        printf("[debug] tsl dev : id(%4.d) - Time(%4.d) - %s  --Line(%d) \n",
                tsl_time.first->id,
                tsl_time.second,
                tsl_time.first->status.empty() == true ? "status is null" : tsl_time.first->status.c_str(),
                (int)line);
    }else{
        printf("[debug] tsl_time.{device_tsl_t *} is null  --Line(%d) \n", (int)line);
    }

    cout << "----------------------------" << endl;
    #endif
}

#endif //_DEBUG_INFO_HPP_

