/*
 * Progarm Name: dev-avl-tree.cpp
 * Created Time: 2017-03-27 09:12:17
 * Last modified: 2017-04-12 10:10:08
 * @author: minphone.linails linails@foxmail.com 
 */

#include "dev-avl-tree.hpp"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

DevAVLTree::DevAVLTree()
{
}

DevAVLTree::~DevAVLTree()
{
    if(0 != this->destroy(this->m_root)){
        cout << "[Error] : destroy BinaryTree failed !" << endl;
    }
}

int  DevAVLTree::insert(device_tsl_t &node, int time)
{
    if(nullptr == this->m_root){
        this->m_root = this->insert(this->m_root, node, time);
    }else{
        this->m_root = this->insert(this->m_root, node, time);
    }

    return 0;
}

int  DevAVLTree::in_order(std::function<int (avlNode *)> visit)
{
    if(nullptr != this->m_root){
        return this->in_order(this->m_root, visit);
    }

    return -1;
}

int  DevAVLTree::in_order(std::function<int (map<int, device_tsl_t> &)> visit)
{
    if(nullptr != this->m_root){
        return this->in_order(this->m_root, visit);
    }

    return -1;
}

int  DevAVLTree::in_order(avlNode *root, std::function<int (avlNode *)> visit)
{
    if(nullptr != root){
        this->in_order(root->m_left, visit);
        visit(root);
        this->in_order(root->m_right, visit);
    }

    return 0;
}

int  DevAVLTree::in_order(avlNode *root, std::function<int (map<int, device_tsl_t> &)> visit)
{
    if(nullptr != root){
        this->in_order(root->m_left, visit);

        map<int, device_tsl_t> map_td;
        device_tsl_t    tsl;
        int             time = -1;

        tsl.id          = root->m_key;

        for(auto &u : root->m_ts){
            time            = u.first;
            tsl.status      = u.second;
            map_td.insert(make_pair(time, tsl));
        }

        visit(map_td);

        this->in_order(root->m_right, visit);
    }

    return 0;
}

int  DevAVLTree::search(key_t key, map<int, device_tsl_t> &nodes) // key = device_tsl_t.id
{
    int ret = -1;

    if(nullptr != this->m_root){

        avlNode *pnode = this->m_root;

        do{
            if(key == pnode->m_key){

                int          time = -1;
                device_tsl_t node;

                node.id     = pnode->m_key;

                for(auto &u : pnode->m_ts){
                    time            = u.first;
                    node.status     = u.second;
                    nodes.insert(make_pair(time, node));
                }

                ret         = 0;
                break;
            }else if(key > pnode->m_key){
                pnode = pnode->m_right;
            }else{
                pnode = pnode->m_left;
            }
        }while(nullptr != pnode);

    }

    return ret;
}

int  DevAVLTree::search(key_t key, std::function<int (avlNode *)> visit)
{
    int ret = -1;

    if(nullptr != this->m_root){

        avlNode *pnode = this->m_root;

        do{
            if(key == pnode->m_key){
                visit(pnode);
                ret         = 0;
                break;
            }else if(key > pnode->m_key){
                pnode = pnode->m_right;
            }else{
                pnode = pnode->m_left;
            }
        }while(nullptr != pnode);

    }

    return ret;
}

int  DevAVLTree::search(key_t key, std::function<int (map<int, device_tsl_t> &)> visit)
{
    int ret = -1;

    if(nullptr != this->m_root){

        avlNode *pnode = this->m_root;

        do{
            if(key == pnode->m_key){
                map<int, device_tsl_t> map_td;
                int          time = -1;
                device_tsl_t node;

                node.id     = pnode->m_key;

                for(auto &u : pnode->m_ts){
                    time            = u.first;
                    node.status     = u.second;
                    map_td.insert(make_pair(time, node));
                }

                visit(map_td);

                ret         = 0;
                break;
            }else if(key > pnode->m_key){
                pnode = pnode->m_right;
            }else{
                pnode = pnode->m_left;
            }
        }while(nullptr != pnode);

    }

    return ret;
}

int  DevAVLTree::destroy(avlNode *subtree)
{
    if(nullptr != subtree){
        this->destroy(subtree->m_left);
        this->destroy(subtree->m_right);
        delete subtree;
    }
    return 0;
}

int  DevAVLTree::height(avlNode *node)
{
    return (nullptr == node) ? -1 : node->m_height;
}

avlNode *DevAVLTree::insert(avlNode *root, device_tsl_t &node, int time)
{
    /*
     * insert node
     * */
    if(nullptr == root){
        root = new avlNode(node.id, time, node.status);
        if(nullptr == root){
            cout << "[Error] : new avlNode() failed ! " << endl;
        }
        return root;
    }else if(node.id < root->m_key){
        root->m_left  = this->insert(root->m_left , node, time);
    }else if(node.id > root->m_key){
        root->m_right = this->insert(root->m_right, node, time);
    }else{
        root->push_time_status(time, node.status);
    }


    /* 
     * rotate
     * */
    root->m_height = this->max(this->height(root->m_left), this->height(root->m_right)) + 1;
    if(2 == (this->height(root->m_left) - this->height(root->m_right))){
        if(node.id < root->m_left->m_key)   root = this->rr_rotate(root);
        else                                root = this->lr_rotate(root);
    }else if(2 == (this->height(root->m_right) - this->height(root->m_left))){
        if(node.id < root->m_right->m_key)  root = this->rl_rotate(root);
        else                                root = this->ll_rotate(root);
    }

    return root;
}
 
avlNode *DevAVLTree::del(avlNode *root, device_tsl_t &node, int time)
{
    return nullptr;
}

avlNode *DevAVLTree::rr_rotate(avlNode *k2)
{
    avlNode *k1  = k2->m_left;
    k2->m_left   = k1->m_right;
    k1->m_right  = k2;
    k2->m_height = this->max(this->height(k2->m_left), this->height(k2->m_right)) + 1;
    k1->m_height = this->max(this->height(k1->m_left), k2->m_height) + 1;
    return k1;
}

avlNode *DevAVLTree::ll_rotate(avlNode *k2)
{
    avlNode* k1  = k2->m_right;
    k2->m_right  = k1->m_left;
    k1->m_left   = k2;
    k2->m_height = this->max(this->height(k2->m_left), this->height(k2->m_right)) + 1;
    k1->m_height = this->max(this->height(k1->m_right), k2->m_height) + 1;
    return k1;
}

avlNode *DevAVLTree::lr_rotate(avlNode *k3)
{
    k3->m_left= this->ll_rotate(k3->m_left); return this->rr_rotate(k3);
}

avlNode *DevAVLTree::rl_rotate(avlNode *k3)
{
    k3->m_right = this->rr_rotate(k3->m_right); return this->ll_rotate(k3);
}


