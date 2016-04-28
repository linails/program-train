/*
 * Progarm Name: function_test.h
 * Created Time: 2016-01-26 09:36:58
 * Last modified: 2016-01-26 14:27:46
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#ifndef _FUNCTION_TEST_H_
#define _FUNCTION_TEST_H_
#include <string>
using std::string;

/*find char test 1*/
extern bool find_char1(string &s , char c);

/*find char test 2*/
extern bool find_char2(const string &s , char c);

class TestClass{
public:
    TestClass();
    ~TestClass();
    void print(void);
private:
};

extern void Print(TestClass &r_tc);
extern void Print(const TestClass &r_tc);
extern void const_test(void);

#endif //_FUNCTION_TEST_H_

