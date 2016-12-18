/*
 * Progarm Name: lambda.cpp
 * Created Time: 2016-03-28 20:57:04
 * Last modified: 2016-12-18 12:33:16
 */

#include "lambda.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

mLambda::mLambda()
{
}

mLambda::~mLambda()
{
}

int  mLambda::mlambda_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->mlambda_test();

    ret = this->mlambda_cb();

    return ret;
}

int  mLambda::mlambda_test(void)
{
    int ret = 0;

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

    return ret;
}

int  mLambda::mlambda_cb(void)
{
    int ret = 0;

    cout << "-----------------------------------------" << endl;
    {
        auto f = [](int (*pf)(char *s)){
            string s = "mLambda::callback is running ...";

            pf((char *)s.c_str());
        };

        f(mLambda::callback);
    }
    cout << "-----------------------------------------" << endl;
    {
        string sa = "this is sa";

        auto f = [&sa](int (*pf)(char *s)){
            pf((char *)sa.c_str());
        };

        f(mLambda::callback);
    }
    cout << "-----------------------------------------" << endl;
    {
        string sa = "this is sa";

        auto f = [&sa](int (*pf)(char *s)){
            pf((char *)sa.c_str());
        };

        auto cb = [](char *s) -> int{
            int ret = 0;
            cout << "cb : " << s << endl;
            return ret;
        };

        f(cb);
    }
    cout << "-----------------------------------------" << endl;
    {
#if 0
        /*
         * Warning : 错误用法
         *    这种用法是错误的，lambda表达式中如果包含捕获，则通过普通的回调函数指针赋值传递为语法错误
         * */

        string sa = "this is sa";
        string sb = "this is sb";

        auto f = [&sa](int (*pf)(char *s)){
            pf((char *)sa.c_str());
        };

        auto cb = [&sb](char *s) -> int{
            int ret = 0;
            cout << "cb : " << s << endl;
            cout << "sb : " << sb << endl;
            return ret;
        };

        f(cb);
#endif
    }
    cout << "-----------------------------------------" << endl;
    {
        string sa = "this is sa";
        string sb = "this is sb";

        /* 
         * Warning : 正确用法
         *   lambda 表达式有捕获功能的时候作为回调函数，则需要通过函数包装器进行传递
         * */
        auto f = [&sa](function<int (char *)> pf){
            pf((char *)sa.c_str());
        };

        auto cb = [&sb](char *s) -> int{
            int ret = 0;
            cout << "cb : " << s << endl;
            cout << "sb : " << sb << endl;
            return ret;
        };

        function<int(char *)> fr = cb;

        f(fr);
    }

    return ret;
}

int  mLambda::callback(char *s)
{
    int ret = 0;

    cout << "cb : " << s << endl;

    return ret;
}

