/*
 * Progarm Name: dev-avl-tree.hpp
 * Created Time: 2017-03-22 18:01:25
 * Last modified: 2017-03-23 14:14:19
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DEV_AVL_TREE_HPP_
#define _DEV_AVL_TREE_HPP_

#include "conflict-check.hpp"
#include "dev-child-sibling-tree.hpp"
#include "conflict-common.hpp"

typedef int key_t;

class DevAVLTree {
public:
    DevAVLTree();
    ~DevAVLTree();
private:
    btNode      *m_root = nullptr;
};

#endif //_DEV_AVL_TREE_HPP_

