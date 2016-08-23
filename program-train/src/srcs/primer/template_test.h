/*
 * Progarm Name: template_test.h
 * Created Time: 2016-02-02 16:38:46
 * Last modified: 2016-08-23 14:01:33
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TEMPLATE_TEST_H_
#define _TEMPLATE_TEST_H_

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template <typename T>
inline string const mmax(T const &a,T const &b)
{
    cout << "template<typename T>" << endl;
    if(a < b) return "<";
    if(b < a) return ">";
    return "><";
}

#if 0
template<>
inline string const mmax<const char*>(const char * a, const char * b)
{
    cout << "template<>" << endl;
    if(a < b) return "<";
    if(b < a) return ">";
    return "><";
}
#endif

extern void template_test(void);

#endif //_TEMPLATE_TEST_H_

