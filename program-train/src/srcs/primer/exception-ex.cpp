/*
 * Progarm Name: exception-ex.cpp
 * Created Time: 2017-11-17 10:18:44
 * Last modified: 2017-11-17 10:33:10
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exception-ex.hpp"
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

ExceptionEx::ExceptionEx()
{
}

ExceptionEx::~ExceptionEx()
{
}

int  ExceptionEx::main(void)
{
    cout << "Fn : ExceptionEx::" << __func__ << endl;

    /*
     * 只能捕捉到 throw 出来的
     * 如果没有 throw，则没有什么可以 catch 的
     *
     * try-catch 可以认为是一种错误处理措施
     * */
    try{
        int *p = nullptr;

        // *p = 10 | 直接运行此句，就捕捉不到

        if(nullptr == p){
            throw p;
        }else{
            *p = 10;
        }
    }
    catch (std::exception &e){
        cout << "e.what() : " << e.what() << endl;
    }
    catch (...){
        cout << "catch ..." << endl;
    }

    return 0;
}

