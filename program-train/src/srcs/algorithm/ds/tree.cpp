/*
 * Progarm Name: tree.cpp
 * Created Time: 2016-12-30 14:57:10
 * Last modified: 2017-01-11 13:28:50
 * @author: minphone.linails linails@foxmail.com 
 */

#include "tree.hpp"
#include "tree-def.hpp"
#include <iostream>
#include "binary-tree-def.hpp"
#include "binary-tree-nr-def.hpp"

using std::cout;
using std::endl;

tTree::tTree()
{
}

tTree::~tTree()
{
}

int  tTree::tree_main(int argc, char **argv)
{
    int ret = 0;
    {
        cout << "... tTree main ..." << endl;

        BinaryTree<int> bt(10);

        cout << "bt.size() : " << bt.size() << endl;
        bt.output();
    }
    cout << "--------------------------------------" << endl;
    {
    }

    return ret;
}


