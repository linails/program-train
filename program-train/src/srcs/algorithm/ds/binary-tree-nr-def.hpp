/*
 * Progarm Name: binary-tree-nr-def.hpp
 * Created Time: 2017-01-10 15:11:10
 * Last modified: 2017-01-12 09:50:26
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _BINARY_TREE_NR_DEF_HPP_
#define _BINARY_TREE_NR_DEF_HPP_

#include "binary-tree-def.hpp"
#include "linked-stack-def.hpp"

enum lrtag{L, R};

/* 
 * 后序遍历使用
 * */
template <typename T>
struct stkNode{
    btNode<T> *ptr;
    lrtag      tag;
    stkNode(btNode<T> *node = NULL):ptr(node), tag(L){}
};

/* 
 * 为了把一个递归过程改为非递归过程，一般需要利用一个工作栈，记录遍历时的回退路径
 * */
template <typename T>
class sBinaryTree : public BinaryTree<T>{
public:
    sBinaryTree();
    sBinaryTree(T data);
    sBinaryTree(const sBinaryTree<T> &bt);
    sBinaryTree<T> &operator=(const sBinaryTree<T> &bt);
    ~sBinaryTree();
    int  pre_order(int (*visit)(btNode<T> *pos));
    int  in_order(int (*visit)(btNode<T> *pos));
    int  post_order(int (*visit)(btNode<T> *pos));
    int  level_order(int (*visit)(btNode<T> *pos));
};

//-----------------------------------------------------------------------------

template <typename T>
sBinaryTree<T>::sBinaryTree()
{
}

template <typename T>
sBinaryTree<T>::sBinaryTree(T data)
{
    this->m_root = new btNode<T>(data);
    if(NULL == this->m_root){
        cout << "[Error] : this->m_root new failed !" << endl;
    }
}

template <typename T>
sBinaryTree<T>::sBinaryTree(const sBinaryTree<T> &bt)
{
}

template <typename T>
sBinaryTree<T> &sBinaryTree<T>::operator=(const sBinaryTree<T> &bt)
{
    return *this;
}

template <typename T>
sBinaryTree<T>::~sBinaryTree()
{
}

template <typename T>
int  sBinaryTree<T>::pre_order(int (*visit)(btNode<T> *pos))
{
    LinkedStack<btNode<T> *>  stack;
    btNode<T> *node = this->m_root;

    stack.push(NULL);
    while(NULL != node){
        visit(node);
        if(NULL != node->m_right) stack.push(node->m_right);
        if(NULL != node->m_left) node = node->m_left;
        else stack.pop(node);
    }

    return 0;
}

template <typename T>
int  sBinaryTree<T>::in_order(int (*visit)(btNode<T> *pos))
{
    LinkedStack<btNode<T> *>  stack;
    btNode<T> *node = this->m_root;

    if(NULL != node) stack.push(node);

    while(NULL != node){
        if(NULL != node->m_left){
            stack.push(node->m_left);
            node = node->m_left;
        }else{
            stack.pop(node);
            visit(node);
            if(NULL != node->m_right) stack.push(node->m_right);
        }
    }

    return 0;
}

/*  
 * 后序遍历比前序遍历和中序遍历的情况复杂
 *  1> 在遍历完左子树时还不能访问根结点，需要再遍历右子树
 *  2> 右子树遍历完才访问根节点
 *  */
template <typename T>
int  sBinaryTree<T>::post_order(int (*visit)(btNode<T> *pos))
{
    stkNode<T>                w;
    LinkedStack<stkNode<T> >  stack;

    btNode<T> *node = this->m_root;

    /* 
     * post-order ...
     * */
    do{
        /* 
         * push all left child node and root
         * */
        while(NULL != node){
            w.ptr = node;
            w.tag = L;
            stack.push(w);

            node = node->m_left;
        }

        /* 
         * -> most important !!!
         * */
        bool branch_travl = false;
        while(!branch_travl && !stack.is_empty()){
            stack.pop(w);
            node = w.ptr;

            if(L == w.tag){
                w.tag = R;
                stack.push(w);
                branch_travl = true;
                node = node->m_right;
            }else if(R == w.tag){
                visit(node);
            }
        }

    }while(!stack.is_empty());

    return 0;
}

template <typename T>
int  sBinaryTree<T>::level_order(int (*visit)(btNode<T> *pos))
{
    return 0;
}

#endif //_BINARY_TREE_NR_DEF_HPP_

