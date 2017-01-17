/*
 * Progarm Name: mstack.cpp
 * Created Time: 2016-12-30 15:11:39
 * Last modified: 2017-01-06 16:01:52
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mstack.hpp"
#include "mstack-def.hpp"
#include "linked-stack-def.hpp"
#include "seq-stack-def.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::vector;

mStack::mStack()
{
}

mStack::~mStack()
{
}

int  mStack::stack_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->seq_stack(); assert(-1 != ret);

    ret = this->linked_stack(); assert(-1 != ret);

    ret = this->fibnacci_app(); assert(-1 != ret);

    return ret;
}

int  mStack::seq_stack(void)
{
    cout << "--------------------------------------" << endl;

    int a;
    SeqStack<int> ss;

    cout << "ss.get_size() : " << ss.get_size() << endl;
    ss.output();

    ss.push(10);
    ss.output();

    ss.push(10);
    ss.output();

    ss.pop(a);
    ss.output();

    ss.pop(a);
    ss.output();

    ss.pop(a);
    ss.output();

    return 0;
}

int  mStack::linked_stack(void)
{
    cout << "--------------------------------------" << endl;

    int a;
    LinkedStack<int> ls;
    cout << "ls.get_size() : " << ls.get_size() << endl;

    ls.output();

    assert(-1 != ls.push(10));
    ls.output();

    assert(-1 != ls.push(20));
    ls.output();
    assert(-1 != ls.push(30));
    ls.output();
    assert(-1 != ls.push(40));
    ls.output();

    cout << "ls.pop(a) : -------- " << endl;
    assert(-1 != ls.pop(a)); cout << "a = " << a << endl;
    ls.output();

    ls.pop(a); cout << "a = " << a << endl;
    ls.output();
    ls.pop(a); cout << "a = " << a << endl;
    ls.output();
    ls.pop(a); cout << "a = " << a << endl;
    ls.output();

    return 0;
}

/* 
 *         / n,                    n = 0 / 1
 * fib(n) =  
 *         \ fib(n-1) + fib(n-2) , n>= 2
 * */
int  mStack::fibnacci_app(void)
{
    cout << "--------------------------------------" << endl;
    {
        cout << "this->fibnacci(10) : " << this->fibnacci(10) << endl;
    }
    {
        cout << "this->fibnacci_stack(10) : " << this->fibnacci_stack(10) << endl;
    }
    {
        cout << "this->fibnacci_iter(10) : " << this->fibnacci_iter(10) << endl;
    }
    return 0;
}

int  mStack::fibnacci(int n)
{
    if(n <= 1) return n;
    else return fibnacci(n-1) + fibnacci(n-2);
}

int  mStack::fibnacci_stack(int n)
{
    return 0;
}

int  mStack::fibnacci_iter(int n)
{
    return 0;
}

