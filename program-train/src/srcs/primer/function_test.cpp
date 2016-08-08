/*
 * Progarm Name: function_test.cpp
 * Created Time: 2016-01-26 09:36:52
 * Last modified: 2016-07-28 17:47:16
 * @author: minphone.linails linails@foxmail.com 
 */

#include "function_test.h"
#include <cstdio>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

/*find char test 1
 *不能够直接如此调用：find_char1("hello",'e');*/
bool find_char1(string &s , char c)
{
    for(string::size_type i = 0; i < s.size(); i++){
        if(s[i] == c){
            cout << "find char 1" << endl;
            return true;
        }
    }
    return false;
}

/*find char test 2*/
bool find_char2(const string &s , char c)
{
    for(string::size_type i = 0; i < s.size(); i++){
        if(s[i] == c){
            cout << "find char 2" << endl;
            return true;
        }
    }
    return false;
}

/*default constructor*/
TestClass::TestClass()
{
    cout << "TestClass default constructor" << endl;
}

/*destructor*/
TestClass::~TestClass()
{
    cout << "TestClass destructor" << endl;
}

/*test print*/
void TestClass::print(void)
{
    cout << "TestClass print" << endl;
}

void Print(TestClass &r_tc)
{
    cout << "Print" << endl;
}

void Print(const TestClass &r_tc)
{
    cout << "const Print " << endl;
}

void const_test(void)
{
    const TestClass ctc;
    TestClass tc;
    Print(ctc);
    Print(tc);
    void (*pf)(TestClass &) = Print;
    typedef void (*PF)(const TestClass &);
    void (*cpf)(const TestClass &) = Print;
    cpf(tc);
    cpf = (PF)pf;
    cpf(tc);
}

