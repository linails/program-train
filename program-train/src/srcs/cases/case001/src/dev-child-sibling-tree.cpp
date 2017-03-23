/*
 * Progarm Name: dev-child-sibling-tree.cpp
 * Created Time: 2017-03-23 13:31:18
 * Last modified: 2017-03-23 18:13:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "dev-child-sibling-tree.hpp"
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

DevChildSiblingTree::DevChildSiblingTree()
{
}

DevChildSiblingTree::~DevChildSiblingTree()
{
    if(0 != this->destroy(this->m_root)){
        cout << "[Error] : destroy BinaryTree failed !" << endl;
    }
}

btNode *DevChildSiblingTree::get_parent(btNode *current)
{
    btNode *ret = nullptr;

    if(nullptr == this->m_root || this->m_root == current){
        ret = nullptr;
    }else{
        ret = this->get_parent(this->m_root, current);
    }

    return ret;
}

btNode *DevChildSiblingTree::get_leftchild(btNode *current)
{
    btNode *ret = nullptr;

    if(nullptr != current) ret = current->m_left;

    return ret;
}

btNode *DevChildSiblingTree::get_rightchild(btNode *current)
{
    btNode *ret = nullptr;

    if(nullptr != current) ret = current->m_right;

    return ret;
}

btNode *DevChildSiblingTree::get_root(void)
{
    return this->m_root;
}

int  DevChildSiblingTree::height(void)
{
    return this->height(this->m_root);
}

int  DevChildSiblingTree::size(void)
{
    return this->size(this->m_root);
}

int  DevChildSiblingTree::isempty(void)
{
    return this->m_root == nullptr ? 0: -1;
}

int  DevChildSiblingTree::insert_child(key_t parent, device_tsl_t &child, int time)
{
    int ret     = 0;
    btNode *pos = nullptr;

    if(0 == this->find(pos, parent, this->m_root)){

        /* 
         * m_left  is child
         * m_right is sibling
         * */
        if(nullptr == pos->m_left){
            /* 
             * as pos's child | pos->child
             * */
            btNode *node = new btNode(child.id, time, child.status);
            if(nullptr != node){
                pos->m_left  = node;
            }else{
                cout << "[Error] new btNode failed !" << endl;
                ret = -1;
            }
        }else{
            /* 
             * as pos's child's sibling | pos->child->sibling
             * */

            btNode *sibling = pos->m_left;
            while(nullptr != sibling->m_right) sibling = sibling->m_right;

            btNode *node = new btNode(child.id, time, child.status);
            if(nullptr != node){
                sibling->m_right = node;
            }else{
                cout << "[Error] new btNode failed !" << endl;
                ret = -1;
            }
        }

    }else{
        cout << "[Error] line = " << __LINE__ << endl;
        ret = -1;
    }

    return ret;
}

int  DevChildSiblingTree::insert_sibling(key_t sibling, device_tsl_t &node, int time)
{
    int ret     = 0;
    btNode *pos = nullptr;

    if(nullptr != this->m_root){
        if(0 == this->find(pos, sibling, this->m_root)){

            while(nullptr != pos->m_right) pos = pos->m_right;

            btNode *inode = new btNode(node.id, time, node.status);
            if(nullptr != inode){
                pos->m_right = inode;
            }else{
                cout << "[Error] new btNode failed !" << endl;
                ret = -1;
            }

        }else{
            cout << "[Error] line = " << __LINE__ << endl;
            ret = -1;
        }
    }else{
        this->m_root = new btNode(node.id, time, node.status);
        if(nullptr == this->m_root){
            cout << "[Error] new btNode failed !" << endl;
            ret = -1;
        }
    }

    return ret;
}

int  DevChildSiblingTree::pre_order(std::function<int (btNode *)> visit)
{
    stack<btNode *> node_stack;
    btNode *node = this->m_root;

    node_stack.push(nullptr);
    while(nullptr != node){
        visit(node);
        if(nullptr != node->m_right) node_stack.push(node->m_right);
        if(nullptr != node->m_left)  node = node->m_left;
        else{
            node = node_stack.top();
            node_stack.pop();
        }
    }

    return 0;
}

int  DevChildSiblingTree::find(btNode *&pos, key_t node, btNode *subtree)
{
    int ret = -1;

    if(nullptr != subtree){
        if(subtree->m_key == node){
            pos = subtree;
            return 0;
        }else{
            if(0 == (ret = this->find(pos, node, subtree->m_left)))  return ret;
            if(0 == (ret = this->find(pos, node, subtree->m_right))) return ret;
        }
    }

    return ret;
}

int  DevChildSiblingTree::destroy(btNode *subtree)
{
    if(nullptr != subtree){
        this->destroy(subtree->m_left);
        this->destroy(subtree->m_right);
        delete subtree;
    }
    return 0;
}

int  DevChildSiblingTree::height(btNode *subtree)
{
    int ret = 0;

    if(nullptr != subtree){
        int lh = this->height(subtree->m_left);
        int rh = this->height(subtree->m_right);
        ret = lh > rh ? lh + 1 : rh + 1;
    }

    return ret;
}

int  DevChildSiblingTree::size(btNode *subtree)
{
    int ret = 0;

    if(nullptr != subtree){
        ret = 1 + this->size(subtree->m_left) + this->size(subtree->m_right);
    }

    return ret;
}

btNode *DevChildSiblingTree::get_parent(btNode *subtree, btNode *current)
{
    if(nullptr == subtree) return nullptr;
    if(subtree->m_left == current || subtree->m_right == current) return subtree;

    btNode *ret = nullptr;

    if(nullptr == (ret = this->get_parent(subtree->m_left, current))){
        ret = this->get_parent(subtree->m_right, current);
    }

    return ret;
}

