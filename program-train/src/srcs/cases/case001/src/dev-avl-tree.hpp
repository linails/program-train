/*
 * Progarm Name: dev-avl-tree.hpp
 * Created Time: 2017-03-22 18:01:25
 * Last modified: 2017-03-27 13:39:30
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DEV_AVL_TREE_HPP_
#define _DEV_AVL_TREE_HPP_

#include "conflict-check.hpp"
#include "dev-child-sibling-tree.hpp"
#include "conflict-common.hpp"
#include <functional>

typedef int key_t;

struct avlNode : public btNode{
    avlNode():btNode(), m_left(NULL), m_right(NULL), m_height(0){};
    avlNode(key_t key, int time, string &status, int h = 0, avlNode *l = NULL, avlNode *r = NULL)
        :btNode(key, time, status), m_left(l) ,m_right(r) ,m_height(h){};
public:
    avlNode    *m_left   = nullptr;
    avlNode    *m_right  = nullptr;
    int         m_height;
};

class DevAVLTree {
public:
    DevAVLTree();
    ~DevAVLTree();
    int  insert(device_tsl_t &node, int time);
    int  in_order(std::function<int (avlNode *)> visit = nullptr);
    int  in_order(std::function<int (device_tsl_t &, int)> visit = nullptr);
    int  search(key_t key, device_tsl_t &node, int &time); // key = device_tsl_t.id
    int  search(key_t key, std::function<int (avlNode *)> visit = nullptr);
    int  search(key_t key, std::function<int (device_tsl_t &, int)> visit = nullptr);
private:
    int  destroy(avlNode *subtree = nullptr);
    int  height(avlNode *node = nullptr);
    int  max(int a, int b){ return a > b ? a : b; };
    int  in_order(avlNode *root, std::function<int (avlNode *)> visit = nullptr);
    int  in_order(avlNode *root, std::function<int (device_tsl_t &, int)> visit = nullptr);
    avlNode *insert(avlNode *root, device_tsl_t &node, int time);
    avlNode *del(avlNode *root, device_tsl_t &node, int time);
    avlNode *rr_rotate(avlNode *k2);
    avlNode *ll_rotate(avlNode *k2);
    avlNode *lr_rotate(avlNode *k3);
    avlNode *rl_rotate(avlNode *k3);
private:
    avlNode      *m_root = nullptr;
};

#endif //_DEV_AVL_TREE_HPP_

