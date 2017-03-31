/*
 * Progarm Name: tester-case001.cpp
 * Created Time: 2017-03-23 17:10:37
 * Last modified: 2017-03-31 13:37:16
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

    //ret = this->infinite_loops(); assert(-1 != ret);

    ret = this->child_sibling(); assert(-1 != ret);

    ret = this->avl(); assert(-1 != ret);

    ret = this->conflict(); assert(-1 != ret);

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

int  TesterCase001::conflict(void)
{
    int ret = 0;

    return ret;
}

