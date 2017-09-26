/*
 * Progarm Name: tester-case001.cpp
 * Created Time: 2017-03-23 17:10:37
 * Last modified: 2017-04-13 14:40:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include "tester-case001.hpp"
#include <iostream>
#include <cassert>
#include "test_main.h"
#include "test-child-sibling-tree.hpp"
#include "test-avl-tree.hpp"
#include "test-conflict-check.hpp"
#include <gtest/gtest.h>

using std::cout;
using std::endl;

TesterCase001::TesterCase001()
{
}

TesterCase001::~TesterCase001()
{
}

int  TesterCase001::main(int argc, char **argv)
{
    int ret = 0;

    ret = this->infinite_loops(); assert(-1 != ret);

    ret = this->child_sibling(); assert(-1 != ret);

    ret = this->avl(); assert(-1 != ret);

    ret = this->convert(); assert(-1 != ret);

    return ret;
}

int  TesterCase001::infinite_loops(void)
{
    test_main(); return 0;
}

int  TesterCase001::child_sibling(void)
{
    int ret = 0;

    TesterChildSiblingTree tree;

    ret = tree.TestTree_insert_sibling(); assert(-1 != ret);

    ret = tree.TestTree_insert_child(); assert(-1 != ret);

    return ret;
}

int  TesterCase001::avl(void)
{
    int ret = 0;

    TesterAVLTree tree;

    ret = tree.insert(); assert(-1 != ret);

    return ret;
}

int  TesterCase001::convert(void)
{
    cout << "convert ..." << endl;

    int ret = 0;

    ret = this->convert_case01(); assert(-1 != ret);

    ret = this->convert_case02(); assert(-1 != ret);

    return ret;
}

int  TesterCase001::convert_case01(void)
{
    int ret = 0;

    DevAVLTree *avltree = new DevAVLTree();
    DevChildSiblingTree *cstree = new DevChildSiblingTree();

    {
        /* 
         * create tree :
         *          5
         *         / \
         *        4   6
         * --------------------
         *  out : 5 4 6
         * */

        int time = 100;
        {
            /* 
             * insert root node
             * */
            key_t parent = -1;
            device_tsl_t tsl = {
                5,
                "string 5"
            };

            if(0 == cstree->insert_child(parent, tsl, time)){
                cout << "cstree->insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 5;
            device_tsl_t tsl = {
                4,
                "string 4"
            };

            cstree->insert_child(parent, tsl, time);
        }

        {
            key_t sibling = 5;
            device_tsl_t tsl = {
                6,
                "string 6"
            };

            cstree->insert_sibling(sibling, tsl, time);
        }

        this->print_tree(cstree);
    }

    this->convert_cs2avl_tree(avltree, cstree);

    avltree->in_order(visit);

    /* 
     * free
     * */
    {
        delete avltree;
        delete cstree;
    }

    cout << "--------------------------------------------" << endl;

    return ret;
}

int  TesterCase001::convert_case02(void)
{
    int ret = 0;

    DevAVLTree *avltree = new DevAVLTree();
    DevChildSiblingTree *cstree = new DevChildSiblingTree();

    {
        /* 
         * create tree :
         *          4
         *         / \
         *        5   6
         * --------------------
         *  out : 4 5 6
         * */

        int time = 100;
        {
            /* 
             * insert root node
             * */
            key_t parent = -1;
            device_tsl_t tsl = {
                4,
                "string 4"
            };

            if(0 == cstree->insert_child(parent, tsl, time)){
                cout << "cstree->insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 4;
            device_tsl_t tsl = {
                5,
                "string 5"
            };

            cstree->insert_child(parent, tsl, time);
        }

        {
            key_t sibling = 4;
            device_tsl_t tsl = {
                6,
                "string 6"
            };

            cstree->insert_sibling(sibling, tsl, time);
        }

        this->print_tree(cstree);
    }

    this->convert_cs2avl_tree(avltree, cstree);

    avltree->in_order(visit);

    /* 
     * free
     * */
    {
        delete avltree;
        delete cstree;
    }

    cout << "--------------------------------------------" << endl;

    return ret;
}

int  TesterCase001::convert_cs2avl_tree(DevAVLTree *avltree, DevChildSiblingTree *cstree)
{
    auto set_val = [](device_tsl_t &tsl, int &time, int key, string status, int time_val){
        tsl.id      = key;
        tsl.status  = status;
        time        = time_val;
    };

    auto visit = [&avltree, &set_val](btNode *pos) -> int{

        int time = -1;
        device_tsl_t tsl;

        set_val(tsl, time, pos->m_key, pos->m_status, pos->m_time);

        avltree->insert(tsl, time);

        return 0;
    };

    cstree->pre_order(visit);

    return 0;
}

void TesterCase001::print_tree(DevChildSiblingTree *tree)
{
    auto visit = [](btNode *pos) -> int{
        cout << pos->m_key << " ";
        return 0;
    };

    cout << "tree : ";
    tree->pre_order(visit);
    cout << endl;
}

int  TesterCase001::visit(avlNode *node)
{
    printf("key: %d height: %d ", node->m_key, node->m_height);

    if(nullptr != node->m_left)  printf("left child: %d ", node->m_left->m_key);
    if(nullptr != node->m_right) printf("right child: %d ", node->m_right->m_key); printf("\n");

    return 0;
}

