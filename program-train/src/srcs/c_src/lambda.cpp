/*
 * Progarm Name: lambda.cpp
 * Created Time: 2016-03-28 20:57:04
 * Last modified: 2016-07-04 12:53:23
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "lambda.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

void lambda_test(void)
{
    cout << "-----------------------------------------" << endl;
    {
        vector<int> c {1,2,3,4,5,6,7};
        int x = 5;
        c.erase(remove_if(c.begin(),c.end(),[x](int n){return n < x;}),c.end());

        cout << "c : ";
        for(auto i : c){
            cout << i << ' ';
        }
        cout << endl;

        auto func1 = [](int i){return i + 4;};
        cout << "func 1 : " << func1(6) << endl;

        function<int(int)> func2 = [](int i){return i + 4;};
        cout << "func 2 : " << func2(6) << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        /* lambda 表达式的语法形式简单归纳如下：
         *
         *  [ capture ]( params ) opt -> ret { body ;};
         *
         *  capture : 是捕获列表
         *  params  : 是参数表
         *  opt     : 是函数选项
         *  ret     : 是返回值类型
         *  body    : 函数体
         * */

        auto f = [](int a) -> int {return a + 1;};

        cout << "f(1) = " << f(1) << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        auto f = [](int a){return a + 1;};
        cout << "f(1) = " << f(1) << endl;

        auto f1 = [](int a){return a * 2;};
        cout << "f1 = " << f1(2) << endl;

        auto f2 = [](int a){return a + 2;};
        cout << "f2 = " << f2(3) << endl;

        /* 表示无参数的lambda表达式 */
        auto f3 = []{return 2; };
        cout << "f3 = " << f3() << endl;

        auto f4 = [](){return 3;};
        cout << "f4 = " << f4() << endl;

        /* 捕获列表总结：
         * 1.[] 不捕获任何变量
         * 2.[&] 捕获外部作用域中所有变量，并作为引用在函数体中使用(按引用捕获)
         * 3.[=] 捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)
         * 4.[=,&foo] 按值捕获外部作用域中所有变量，并按引用捕获foo变量
         * 5.[bar] 按值捕获bar变量，同时不捕获其他变量
         * 6.[this] 捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数通用的访问权限
         * */
    }
    cout << "-----------------------------------------" << endl;
    {
        int a = 10;
        int b = 12;

        auto c = [=]{return a + b;};
        cout << "c = " << c() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        int a = 1;
        auto f = [=]{return a;};
        a++;
        cout << "f = " << f() << endl;
        cout << "a = " << a << endl;
    }
}


