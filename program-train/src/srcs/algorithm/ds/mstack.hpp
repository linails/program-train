/*
 * Progarm Name: mstack.hpp
 * Created Time: 2016-12-30 15:11:52
 * Last modified: 2017-01-06 15:59:55
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSTACK_HPP_
#define _MSTACK_HPP_

class mStack{
public:
    mStack();
    ~mStack();
    int  stack_main(int argc, char **argv);
private:
    int  seq_stack(void);
    int  linked_stack(void);
    int  fibnacci_app(void);
    int  fibnacci(int n);
    int  fibnacci_stack(int n);
    int  fibnacci_iter(int n);
};

/* 
 * Note : 
 *  
 *  一般对尾递归或单向递归的情形，都可以利用迭代的方法，将递归过程改为非递归过程
 *
 *  1> 所谓单向递归就是如求解斐波那契数列这样的问题
 *
 *  2> 尾递归则是单向递归的特例，是递归语句只有一句，且放在过程的最后，当递归调用
 *     返回时，返回到上一层递归调用语句的下一语句，这个位置正好是程序的末尾
 *
 * */

#endif //_MSTACK_HPP_

