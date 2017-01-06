/*
 * Progarm Name: mstack-def.hpp
 * Created Time: 2017-01-06 10:05:21
 * Last modified: 2017-01-06 15:34:28
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSTACK_DEF_HPP_
#define _MSTACK_DEF_HPP_

/* 
 * 栈是一种最常用和最重要的数据结构，它的用途非常广泛
 *
 * 栈可定义为只允许在表的末端进行插入和删除的线性表
 *  1> 允许插入和删除的一端叫做栈顶(top)
 *  2> 不允许插入和删除的一端叫做栈底(bottom)
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 栈的抽象数据类型有两种典型的存储表示，基于数组的存储表示和基于链表的存储表示
 *  1> 基于数组的存储表示实现的栈称为顺序栈
 *  2> 基于链表的存储表示实现的栈称为链式栈
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 在计算机中执行算术表达式的计算是通过栈来实现的
 * 算术表达式的3种表示: 
 *  1>中缀(infix)表示     : A+B
 *  2>前缀(prefix)表示    : +AB
 *  3>后缀(postfix)表示   : AB+
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * 对于递归过程，可以利用栈将它改为非递归过程
 *
 * */

template <typename T>
class MStack{
public:
    MStack(){};
    virtual ~MStack(){};
    virtual int  push(T x) = 0;
    virtual int  pop(T &x) = 0;
    virtual int  is_empty(void) const = 0;
    virtual int  is_full(void) const = 0;
    virtual int  get_size(void) const = 0;
};

#endif //_MSTACK_DEF_HPP_

