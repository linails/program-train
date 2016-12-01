/*
 * Progarm Name: exception_test.cpp
 * Created Time: 2016-08-07 21:27:27
 * Last modified: 2016-12-01 18:01:10
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exception_test.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>

using namespace std;

void exception_test(void)
{
    cout << "---------- exception_test ----------" << endl;

    {
#if 0
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
#endif
    }
    {
        Excep excep("e1");

        excep.base();

        excep.base_outof_excep();
    }
}

Excep::Excep(string s)
{
    cout << "excep name : " << s << endl;
}

Excep::~Excep()
{
}

void Excep::base(void)
{
    cout << "Excep::base ..." << endl;

    char *str1 = (char *)"123";
    char *str2 = NULL;

    int num1;
    int num2;

    try{

        #if 1

        num1 = this->parse_number(str1);
        num2 = this->parse_number(str2);

        #else

        /* atoi 不抛出异常 */
        num1 = atoi(str1);
        num2 = atoi(str2);

        #endif

    }
    catch(illgalNumberExcep){
        cout << "catch illgalNumberExcep" << endl;
    }
    catch(...){
        cout << "catch error" << endl;
    }

    cout << "num1 : " << num1 << endl;
    cout << "num2 : " << num2 << endl;
}

void Excep::base_outof_excep(void)
{
    cout << "Excep::base_outof_excep ..." << endl;

    try{
        this->outof_excep();
    }
    catch(int){
        cout << "catch int" << endl;
    }
    catch(...){
        cout << "catch ..." << endl;
    }
}

int Excep::number_check(char *str)
{
    if(NULL == str)
        return -1;
    else
        return 0;
}

int Excep::parse_number(char *str) throw(illgalNumberExcep)
{
    if(-1 == this->number_check(str)){
        cout << "throw illgalNumberExcep" << endl;
        throw illgalNumberExcep();
    }
    return atoi(str);
}

int Excep::outof_excep(void) throw(int, char)
{
    /*
     * 这个函数可以抛出的异常是 int, char
     * 超出这个范围的异常，将导致abort()
     * */
    #if 0
    double a = 10;
    #else
    int a = 10;
    #endif

    throw a;
    //throw int(); //这种方式也可以，上面一种方式也可以

    return 0;
}

/* 
 * 总结：
 *      1> void f(int a) throw(e1, e2);
 *          表示 f() 只能抛出两个异常 e1, e2 以及这些类型派生的异常，但不会抛出其他异常
 *          如果抛出e3,那么函数在抛出异常时，会转换为一个std::unexpected()调用，默认调用std::terminate()
 *          则abort()
 *      2> void f(void)
 *          这种函数不带抛出异常描述的，表示可能抛出任何异常
 *      3> void f(void) throw()
 *          这种函数表示不抛出任何异常
 *
 *      4> 捕获异常的代码
 *          try{
 *              throw E();
 *          }
 *          catch (H h){
 *              ...
 *              可以进入此处的条件，或者可被捕获条件
 *              (1) 如果 H 和 E 是相同的类型
 *              (2) 如果 H 是 E 的基类
 *              (3) 如果 H 和 E 都是指针类型，且符合(1)||(2)
 *              (4) 如果 H 和 E 都是引用类型，且符合(1)||(2)
 *              (5) 如果 H 是 E 的基类，那么捕获的时候，会类似class一样进行切割，丢失继承部分的信息
 *          }
 * */


