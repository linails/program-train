/*
 * Progarm Name: exception_test.cpp
 * Created Time: 2016-08-07 21:27:27
 * Last modified: 2016-12-01 07:14:16
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exception_test.h"
#include <iostream>
#include <cstdio>
#include <stdexcept>

using namespace std;

void exception_test(void)
{
    cout << "---------- exception_test ----------" << endl;

    {
        try{
            {
                /* 可以逐级向外层传递 */
                try{

                    int a;

                    cout << "please input a num : " << endl;
                    cin >> a;
                    if(a < 20){
                        cout << "before throw" << endl;
                        throw runtime_error("ERROR : a < 20");
                        cout << "after throw" << endl;
                    }
                }
                catch(runtime_error err){
                    cout << err.what() << endl;
                    throw runtime_error(err.what());
                }
            }

        }
        catch(runtime_error err){
            cout << "catch error !" << endl;
            cout << err.what() << endl;
        }
        catch(...){
        }
    }
}

/* 
 * 析构函数在栈展开的过程中执行，这一事实影响着我们编写析构函数的方式
 *
 * 析构函数得能够在本函数内处理异常，不能抛出异常
 *
 * 在实际的编程过程中，因为析构函数仅仅是释放资源，所以它不太可能抛出异常，所有标准库
 * 类型都能够确保它们的析构函数不会引发异常
 * */


