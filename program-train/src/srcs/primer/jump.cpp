/*
 * Progarm Name: jump.cpp
 * Created Time: 2017-03-30 11:00:19
 * Last modified: 2017-03-30 14:05:29
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

jmp_buf Jumper::jmp;

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

        ret = this->case_03(); assert(-1 != ret);
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
    /* 
     * Note :
     *  setjmp 与 longjmp 结合使用时，必须有严格的先后执行顺序
     *  01. 先调用 setjmp 函数，保存 "程序执行点"
     *  02. 调用 longjmp 函数，跳转
     * */
    if(1 == setjmp(Jumper::jmp)){
        cout << "from jmp val = 1" << endl;
        return 0;
    }

    #if 0
    /* 
     * Note :
     *  使用 lambda 的方式来进行函数间调整，会引起内存泄漏
     *
     * 原因分析 :
     *  编译器会把一个 lambda 表达式生成一个匿名类的匿名对象，并在类中重载函数运算符
     *  直接从里面 longjmp() 相当于是没有运行析构函数，因而引起内存泄漏
     *  示例参见 ：this->case_03()
     * */
    auto visit = [&jmp](int d) -> int{
        cout << "d = " << d << endl;
        if(10 == d){
            cout << "longjmp()" << endl;
            longjmp(jmp, 1); // jump
        }
        return 0;
    };
    #endif

    this->cb_user(this->visit_global);

    return 0;
}

int  Jumper::case_03(void)
{
    jmp_buf jmp;

    if(1 == setjmp(jmp)){
        cout << "from jmp val = 1" << endl;
        return 0;
    }

    auto visit = VisitClass(jmp);

    #if 1
    /* 
     * 直接 longjmp 后，没有运行析构函数
     * */
    this->cb_user(visit);
    #else
    /* 
     * 有进行释放 , 运行了析构函数
     * */
    visit(1);
    #endif

    return 0;
}

int  Jumper::cb_user(std::function<int (int)> visit)
{
    for(int i=0; i<100; i++){
        if(0 != visit(i)) return -1;
    }
    return 0;
}

int  Jumper::visit_global(int d)
{
    cout << "d = " << d << endl;
    if(10 == d){
        cout << "longjmp()" << endl;
        longjmp(Jumper::jmp, 1); // jump
    }

    return 0;
}

VisitClass::VisitClass(jmp_buf &jmp)
    :m_jmp(jmp)
{
}

VisitClass::~VisitClass()
{
    cout << "~VisitClass()" << endl;
}

int  VisitClass::operator()(int d) const
{
    cout << "d = " << d << endl;
    if(10 == d){
        cout << "longjmp()" << endl;
        longjmp(this->m_jmp, 1); // jump
    }

    return 0;
}

