/*
 * Progarm Name: jump.cpp
 * Created Time: 2017-03-30 11:00:19
 * Last modified: 2017-03-30 12:25:49
 * @author: minphone.linails linails@foxmail.com 
 */

#include "jump.hpp"
#include <iostream>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <assert.h>

using std::cout;
using std::endl;

Jumper::Jumper()
{
}

Jumper::~Jumper()
{
}

int  Jumper::main(int argc, char **argv)
{
    int ret = 0;

    cout << "---------------- Jumper C++ ----------------" << endl;
    {
        ret = this->case_01(); assert(-1 != ret);

        ret = this->case_02(); assert(-1 != ret);
    }

    return ret;
}

int  Jumper::case_01(void)
{
    auto visit = [](int d) -> int{
        cout << "d = " << d << endl;
        if(10 == d){
            return -1;
        }
        return 0;
    };

    this->cb_user(visit);

    return 0;
}

int  Jumper::case_02(void)
{
    jmp_buf jmp;

    /* 
     * Note :
     *  setjmp 与 longjmp 结合使用时，必须有严格的先后执行顺序
     *  01. 先调用 setjmp 函数，保存 "程序执行点"
     *  02. 调用 longjmp 函数，跳转
     * */
    if(1 == setjmp(jmp)){
        cout << "from jmp val = 1" << endl;
        return 0;
    }

    auto visit = [&jmp](int d) -> int{
        cout << "d = " << d << endl;
        if(10 == d){
            cout << "longjmp()" << endl;
            longjmp(jmp, 1); // jump
        }
        return 0;
    };

    this->cb_user(visit);

    return 0;
}

int  Jumper::cb_user(std::function<int (int)> visit)
{
    for(int i=0; i<100; i++){
        if(0 != visit(i)) return -1;
    }
    return 0;
}

