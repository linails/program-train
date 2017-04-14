/*
 * Progarm Name: dev-child-sibling-tree.hpp
 * Created Time: 2017-03-22 18:28:09
 * Last modified: 2017-03-23 18:13:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DEV_CHILD_SIBLING_TREE_HPP_
#define _DEV_CHILD_SIBLING_TREE_HPP_

#include "conflict-check.hpp"
#include "conflict-common.hpp"
#include <string>
#include <functional>

using std::string;

/*
 * same as btree
 * */

class DevChildSiblingTree{
public:
    DevChildSiblingTree();
    ~DevChildSiblingTree();
public:
    btNode *get_parent(btNode *current);
    btNode *get_leftchild(btNode *current);
    btNode *get_rightchild(btNode *current);
    btNode *get_root(void);
    int  height(void);
    int  size(void);
    int  isempty(void);
    int  insert_child(key_t parent, device_tsl_t &child, int time);
    int  insert_sibling(key_t sibling, device_tsl_t &node, int time);
    int  pre_order(std::function<int (btNode *)> visit);
private:
    int  find(btNode *&pos, key_t node, btNode *subtree);
    int  destroy(btNode *subtree);
    int  height(btNode *subtree);
    int  size(btNode *subtree);
    btNode *get_parent(btNode *subtree, btNode *current);
private:
    btNode      *m_root = nullptr;
};

#endif //_DEV_CHILD_SIBLING_TREE_HPP_

