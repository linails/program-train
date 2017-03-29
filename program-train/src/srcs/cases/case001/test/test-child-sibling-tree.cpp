/*
 * Progarm Name: test-child-sibling-tree.cpp
 * Created Time: 2017-03-23 14:20:38
 * Last modified: 2017-03-29 17:24:27
 * @author: minphone.linails linails@foxmail.com 
 */

#include "test-child-sibling-tree.hpp"
#include <iostream>
#include "conflict-common.hpp"
#include "dev-child-sibling-tree.hpp"
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

TesterChildSiblingTree::TesterChildSiblingTree()
{
}

TesterChildSiblingTree::~TesterChildSiblingTree()
{
}

int  TesterChildSiblingTree::TestTree_insert_child(void)
{
    auto print_tree = [](DevChildSiblingTree &tree){
        auto visit = [](btNode *pos) -> int{
            cout << pos->m_key << " ";
            //cout << "node key = " << pos->m_key << endl;
            return 0;
        };

        cout << "tree : ";
        tree.pre_order(visit);
        cout << endl;
    };

    //int  insert_child(key_t parent, device_tsl_t &child, int time);
    {
        DevChildSiblingTree tree;

        map<key_t, tuple<device_tsl_t, int> > devices;

        for(int i=0; i<10; i++){
            int time = 2017 + i + 1;
            device_tsl_t tsl = {
                i+2,
                "string "
            };
            devices.insert(make_pair(i+1, make_tuple(tsl, time)));
        }

        key_t sibling = 2;
        device_tsl_t tsl = {
            1,
            "string 1"
        };
        int time = 2017;

        if(0 == tree.insert_sibling(sibling, tsl, time)){
            cout << "tree.insert_sibling successed !" << endl;
        }

        bool toggle = true;
        for(auto &u : devices){
            if(false == toggle){
                if(0 == tree.insert_sibling(u.first, std::get<0>(u.second), std::get<1>(u.second))){
                    printf("tree.insert_sibling successed [ %d - %d ]\n", u.first, std::get<0>(u.second).id);
                }
                toggle = true;
            }else{
                if(0 == tree.insert_child(u.first, std::get<0>(u.second), std::get<1>(u.second))){
                    printf("tree.insert_child successed   [ %d - %d ]\n", u.first, std::get<0>(u.second).id);
                }
                toggle = false;
            }
        }
        print_tree(tree);
    }
    cout << "--------------------------------------------" << endl;
    {
        DevChildSiblingTree tree;

        int time = 2017;
        {
            /* 
             * insert root node
             * */
            key_t sibling = 3;
            device_tsl_t tsl = {
                1,
                "string 1"
            };

            if(0 == tree.insert_sibling(sibling, tsl, time)){
                cout << "tree.insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 1;
            device_tsl_t tsl = {
                2,
                "string 2"
            };

            tree.insert_child(parent, tsl, time);
        }
        print_tree(tree);

        {
            key_t sibling = 1;
            device_tsl_t tsl = {
                3,
                "string 3"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);
    }
    cout << "--------------------------------------------" << endl;
    {
        DevChildSiblingTree tree;

        int time = 2017;
        {
            /* 
             * insert root node
             * */
            key_t sibling = 2;
            device_tsl_t tsl = {
                1,
                "string 1"
            };

            if(0 == tree.insert_sibling(sibling, tsl, time)){
                cout << "tree.insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 1;
            device_tsl_t tsl = {
                3,
                "string 3"
            };

            tree.insert_child(parent, tsl, time);
        }
        print_tree(tree);

        {
            key_t sibling = 1;
            device_tsl_t tsl = {
                2,
                "string 2"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);
    }
    cout << "--------------------------------------------" << endl;
    {
        /* 
         * create tree :
         *          3
         *         / \
         *        1   6
         *           / \
         *          4   7
         *         / \
         *        2   5
         * --------------------
         *  out : 3 1 6 4 2 5 7
         * */
        DevChildSiblingTree tree;

        int time = 2017;
        {
            /* 
             * insert root node
             * */
            key_t sibling = 6;
            device_tsl_t tsl = {
                3,
                "string 3"
            };

            if(0 == tree.insert_sibling(sibling, tsl, time)){
                cout << "tree.insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 3;
            device_tsl_t tsl = {
                1,
                "string 1"
            };

            tree.insert_child(parent, tsl, time);
        }
        print_tree(tree);

        {
            key_t sibling = 3;
            device_tsl_t tsl = {
                6,
                "string 6"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);


        {
            key_t parent = 6;
            device_tsl_t tsl = {
                4,
                "string 4"
            };

            tree.insert_child(parent, tsl, time);
        }
        {
            key_t parent = 4;
            device_tsl_t tsl = {
                2,
                "string 2"
            };

            tree.insert_child(parent, tsl, time);
        }
        {
            key_t sibling = 4;
            device_tsl_t tsl = {
                5,
                "string 5"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        {
            key_t sibling = 6;
            device_tsl_t tsl = {
                7,
                "string 7"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);
    }
    cout << "--------------------------------------------" << endl;
    {
        /* 
         * create tree :
         *          3
         *         / \
         *        1   6
         *           / \
         *          4   7
         *         / \
         *        2   5
         * --------------------
         *  out : 3 1 6 4 2 5 7
         * */
        DevChildSiblingTree tree;

        int time = 2017;
        {
            /* 
             * insert root node
             * */
            key_t parent = 6;
            device_tsl_t tsl = {
                3,
                "string 3"
            };

            if(0 == tree.insert_child(parent, tsl, time)){
                cout << "tree.insert_sibling successed - root" << endl;
            }
        }
        {
            /* 
             * insert first child of root
             * */
            key_t parent = 3;
            device_tsl_t tsl = {
                1,
                "string 1"
            };

            tree.insert_child(parent, tsl, time);
        }
        print_tree(tree);

        {
            key_t sibling = 3;
            device_tsl_t tsl = {
                6,
                "string 6"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);


        {
            key_t parent = 6;
            device_tsl_t tsl = {
                4,
                "string 4"
            };

            tree.insert_child(parent, tsl, time);
        }
        {
            key_t parent = 4;
            device_tsl_t tsl = {
                2,
                "string 2"
            };

            tree.insert_child(parent, tsl, time);
        }
        {
            key_t sibling = 4;
            device_tsl_t tsl = {
                5,
                "string 5"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        {
            key_t sibling = 6;
            device_tsl_t tsl = {
                7,
                "string 7"
            };

            tree.insert_sibling(sibling, tsl, time);
        }
        print_tree(tree);
    }

    return 0;
}

int  TesterChildSiblingTree::TestTree_insert_sibling(void)
{
    DevChildSiblingTree tree;

    auto print_tree = [](DevChildSiblingTree &tree){
        auto visit = [](btNode *pos) -> int{
            cout << pos->m_key << " ";
            //cout << "node key = " << pos->m_key << endl;
            return 0;
        };

        cout << "tree : ";
        tree.pre_order(visit);
        cout << endl;
    };

    {
        map<key_t, tuple<device_tsl_t, int> > devices;

        for(int i=0; i<10; i++){
            int time = 2017 + i + 1;
            device_tsl_t tsl = {
                i+2,
                "string "
            };
            devices.insert(make_pair(i+1, make_tuple(tsl, time)));
        }

        key_t sibling = 2;
        device_tsl_t tsl = {
            1,
            "string 1"
        };
        int time = 2017;

        if(0 == tree.insert_sibling(sibling, tsl, time)){
            cout << "tree.insert_sibling successed !" << endl;
        }

        print_tree(tree);

        for(auto &u : devices){
            if(0 == tree.insert_sibling(u.first, std::get<0>(u.second), std::get<1>(u.second))){
                cout << "tree.insert_sibling successed !" << endl;
            }
        }
        print_tree(tree);
    }
    cout << "--------------------------------------------" << endl;

    return 0;
}

