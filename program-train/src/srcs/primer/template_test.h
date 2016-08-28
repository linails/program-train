/*
 * Progarm Name: template_test.h
 * Created Time: 2016-02-02 16:38:46
 * Last modified: 2016-08-27 07:40:15
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TEMPLATE_TEST_H_
#define _TEMPLATE_TEST_H_

#include <string>
#include <iostream>
#include <cstdio>
#include <typeinfo>

using std::string;
using std::cout;
using std::endl;

/* 如果函数参数为引用类型，而函数的实参则为数组或函数类型，
 * 那么将不会进行任何隐式转换*/
template <typename T>
inline string const mmax(T const &a,T const &b)
{
    cout << "template<typename T>" << endl;

    cout << "typeid(a).name() = " << typeid(a).name() << endl;
    cout << "typeid(string).name() = " << typeid(string).name() << endl;

#if 0
    if(typeid(a) == typeid(string)){
        cout << "The same typeid" << endl;
    }else
        printf("a(0x%x) - b(0x%x) \n", a, b);
#endif

#if 0
    if(typeid(a) != typeid(string))
        printf("a(0x%x) - b(0x%x) \n", a, b);
#endif

    if(a < b) return "<";
    if(b < a) return ">";
    return "><";
}

#if 1
/* 模板特化 */
template<>
inline string const mmax<const char*>(const char * const &a, const char * const &b)
{
    cout << "template<>" << endl;
    if(a < b) return "<";
    if(b < a) return ">";
    return "><";
}
#endif

extern void template_test(void);

#endif //_TEMPLATE_TEST_H_

