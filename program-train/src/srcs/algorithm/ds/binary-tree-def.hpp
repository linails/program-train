/*
 * Progarm Name: bianry-tree-def.hpp
 * Created Time: 2017-01-09 14:42:41
 * Last modified: 2017-01-10 15:45:11
 * @author: minphone.linails linails@foxmail.com
 */

#ifndef _BINARY_TREE_DEF_HPP_
#define _BINARY_TREE_DEF_HPP_

/* 
 * 二叉树
 *
 * 一棵二叉树是结点的一个有限集合，该集合或者为空，或者是由一个根节点加上两棵分别称为
 * 左子树和右子树的、互不相交的二叉树组成
 *
 *      / Φ，          n = 0
 *   T = 
 *      \ {r, Tl, Tr}, n > 0
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 二叉树的性质：
 *  1> 在二叉树的第 i(i>=1) 层最多有 2^(i-1) 个结点
 *  2> 深度为 k(k>=0) 的二叉树最少有 k 个结点，最多有 2^k - 1 个结点
 *  3> 对任何一棵非空二叉树，如果其叶节点数为 n0，度为 2 的非叶节点数为 n2，则 n0 = n2 + 1
 *     > 满二叉树(full binary tree)
 *       深度为 k 的满二叉树是有 2^k - 1 个结点的二叉树，在满二叉树中，每一层结点都达到了最大个数
 *     > 完全二叉树(complete binary tree)
 *       如果一棵具有 n 个结点的深度为 k 的二叉树，它的每一个结点都与高度为 k 的满二叉树中编号
 *       为 1~n 的结点一一对应，则称这棵二叉树为完全二叉树
 *  4> 具有 n 个结点的完全二叉树的最小深度为「ln(n+1)/ln(2)
 *  5> 如果将一棵有 n 个结点的完全二叉树自顶向下，同一层自左向右连续给结点编号 1, 2, 3, ... n, 
 *     然后按此结点编号将树中结点顺序地存放于一个一维数组中，并简称编号为 i 的结点为结点 i(1<=i<=n)
 *     > 若 i == 1，则结点 i 为根，无父节点；若 i>1，则结点 i 的父节点为结点 i/2」
 *     > 若 2*i <= n，则结点 i 的左子女为结点２*i
 *     > 若结点编号 i 为奇数，且 i != 1，它处于右兄弟位置，则它的左兄弟为结点 i-1
 *     > 若结点编号 i 为偶数，且 i != n，它处于左兄弟位置，则它的右兄弟为结点 i+1
 *     > 结点 i 所在层次为 lni/ln2」 + 1
 *
 * */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <typeinfo>

using std::cout;
using std::endl;
using std::string;

template <typename T>
struct btNode{
    btNode():m_left(NULL), m_right(NULL){};
    btNode(T x, btNode<T> *l = NULL, btNode<T> *r = NULL) :m_left(l) ,m_right(r) ,m_data(x){};
    btNode<T> *m_left;
    btNode<T> *m_right;
    T          m_data;
};

template <typename T>
class BinaryTree{
public:
    BinaryTree();
    BinaryTree(T data);
    BinaryTree(const BinaryTree<T> &bt);
    BinaryTree<T> &operator=(const BinaryTree<T> &bt);
    virtual ~BinaryTree();
    virtual btNode<T> *get_parent(btNode<T> *current);
    virtual btNode<T> *get_leftchild(btNode<T> *current);
    virtual btNode<T> *get_rightchild(btNode<T> *current);
    virtual btNode<T> *get_root(void);
    virtual btNode<T> *find(T data);
    virtual int  height(void);
    virtual int  size(void);
    virtual int  isempty(void);
    virtual int  pre_order(int (*visit)(btNode<T> *pos));
    virtual int  in_order(int (*visit)(btNode<T> *pos));
    virtual int  post_order(int (*visit)(btNode<T> *pos));
    virtual int  level_order(int (*visit)(btNode<T> *pos));
    virtual int  insert(T data);
    virtual int  output(void);
private:
    int  destroy(btNode<T> *subtree);
    int  height(btNode<T> *subtree);
    int  size(btNode<T> *subtree);
    int  pre_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos));
    int  in_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos));
    int  post_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos));
    btNode<T> *get_parent(btNode<T> *subtree, btNode<T> *current);
    btNode<T> *find(btNode<T> *subtree, const T &data);
    btNode<T> *copy(btNode<T> *subtree);
protected:
    btNode<T>   *m_root;
};

//-----------------------------------------------------------------------------

template <typename T>
BinaryTree<T>::BinaryTree()
    :m_root(NULL)
{
}

template <typename T>
BinaryTree<T>::BinaryTree(T data)
{
    this->m_root = new btNode<T>(data);
    if(NULL == this->m_root){
        cout << "[Error] : this->m_root new failed !" << endl;
    }
}

/* 
 * 为了实现二叉树的复制构造函数，可以利用二叉树的前序遍历算法
 * */
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &bt)
{
    this->m_root = this->copy(bt.m_root);
}

template <typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree<T> &bt)
{
    /* 
     *  1. 检查自赋值
     *  2. 释放原有的内存资源
     *  3. 分配新的内存资源，并复制内容
     *  4. 返回本对象的引用
     * */
    if(this == &bt) return *this;

    this->destroy(this->m_root);

    this->m_root = this->copy(bt.m_root);

    return *this;
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    if(0 != this->destroy(this->m_root)){
        cout << "[Error] : destroy BinaryTree<T> failed !" << endl;
    }
}

template <typename T>
btNode<T> *BinaryTree<T>::get_parent(btNode<T> *current)
{
    btNode<T> *ret = NULL;

    if(NULL == this->m_root || this->m_root == current){
        ret = NULL;
    }else{
        ret = this->get_parent(this->m_root, current);
    }

    return ret;
}

template <typename T>
btNode<T> *BinaryTree<T>::get_leftchild(btNode<T> *current)
{
    btNode<T> *ret = NULL;

    if(NULL != current) ret = current->m_left;

    return ret;
}

template <typename T>
btNode<T> *BinaryTree<T>::get_rightchild(btNode<T> *current)
{
    btNode<T> *ret = NULL;

    if(NULL != current) ret = current->m_right;

    return ret;
}

template <typename T>
btNode<T> *BinaryTree<T>::get_root(void)
{
    return this->m_root;
}

/* 
 * 二叉搜索树
 * */
template <typename T>
btNode<T> *BinaryTree<T>::find(T data)
{
    return NULL;
}

template <typename T>
int  BinaryTree<T>::height(void)
{
    return this->height(this->m_root);
}

template <typename T>
int  BinaryTree<T>::size(void)
{
    return this->size(this->m_root);
}

template <typename T>
int  BinaryTree<T>::isempty(void)
{
    return this->m_root == NULL ? 0: -1;
}

/* 
 * 二叉树是最基本的树形结构，在二叉树上所有可用的操作中，遍历是最常用的操作
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 规定先左后右，则有3种遍历规则: V - visit() ; L - left ; R - right
 *  1> VLR(前序遍历)
 *  2> LVR(中序遍历)
 *  3> LRV(后序遍历)
 *
 * */
template <typename T>
int  BinaryTree<T>::pre_order(int (*visit)(btNode<T> *pos))
{
    return this->pre_order(this->m_root, visit);
}

template <typename T>
int  BinaryTree<T>::in_order(int (*visit)(btNode<T> *pos))
{
    return this->in_order(this->m_root, visit);
}

template <typename T>
int  BinaryTree<T>::post_order(int (*visit)(btNode<T> *pos))
{
    return this->post_order(this->m_root, visit);
}

template <typename T>
int  BinaryTree<T>::level_order(int (*visit)(btNode<T> *pos))
{
    return 0;
}

/* 
 * 二叉搜索树
 * */
template <typename T>
int  BinaryTree<T>::insert(T data)
{
    return 0;
}

template <typename T>
int  BinaryTree<T>::output(void)
{
    cout << "BinaryTree<" << typeid(T).name() << "> " ;

    auto visit = [](btNode<T> *pos){
        cout << pos->m_data << " ";
        return 0;
    };

    this->pre_order(visit);
    cout << endl;

    return 0;
}

template <typename T>
int  BinaryTree<T>::destroy(btNode<T> *subtree)
{
    if(NULL != subtree){
        this->destroy(subtree->m_left);
        this->destroy(subtree->m_right);
        delete subtree;
    }
    return 0;
}

template <typename T>
int  BinaryTree<T>::height(btNode<T> *subtree)
{
    int ret = 0;

    if(NULL != subtree){
        int lh = this->height(subtree->m_left);
        int rh = this->height(subtree->m_right);
        ret = lh > rh ? lh + 1 : rh + 1;
    }

    return ret;
}

template <typename T>
int  BinaryTree<T>::size(btNode<T> *subtree)
{
    int ret = 0;

    if(NULL != subtree){
        ret = 1 + this->size(subtree->m_left) + this->size(subtree->m_right);
    }

    return ret;
}

template <typename T>
int  BinaryTree<T>::pre_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos))
{
    if(NULL != subtree){
        visit(subtree);
        this->pre_order(subtree->m_left, visit);
        this->pre_order(subtree->m_right, visit);
    }
    return 0;
}

template <typename T>
int  BinaryTree<T>::in_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos))
{
    if(NULL != subtree){
        this->in_order(subtree->m_left, visit);
        visit(subtree);
        this->in_order(subtree->m_right, visit);
    }
    return 0;
}

template <typename T>
int  BinaryTree<T>::post_order(btNode<T> *subtree, int (*visit)(btNode<T> *pos))
{
    if(NULL != subtree){
        this->post_order(subtree->m_left, visit);
        this->post_order(subtree->m_right, visit);
        visit(subtree);
    }
    return 0;
}

template <typename T>
btNode<T> *BinaryTree<T>::get_parent(btNode<T> *subtree, btNode<T> *current)
{
    if(NULL == subtree) return NULL;
    if(subtree->m_left == current || subtree->m_right == current) return subtree;

    btNode<T> *ret = NULL;

    if(NULL == (ret = this->get_parent(subtree->m_left, current))){
        ret = this->get_parent(subtree->m_right, current);
    }

    return ret;
}

/* 
 * 二叉搜索树
 * */
template <typename T>
btNode<T> *BinaryTree<T>::find(btNode<T> *subtree, const T &data)
{
    return NULL;
}

template <typename T>
btNode<T> *BinaryTree<T>::copy(btNode<T> *subtree)
{
    btNode<T> *ret = NULL;

    if(NULL != subtree){
        ret = new btNode<T>(subtree->m_data);
        if(NULL == ret){
            cout << "[Error] : new failed !" << endl;
        }

        ret->m_left  = this->copy(subtree->m_left);
        ret->m_right = this->copy(subtree->m_right);
    }

    return ret;
}

#endif //_BINARY_TREE_DEF_HPP_

