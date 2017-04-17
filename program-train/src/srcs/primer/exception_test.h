/*
 * Progarm Name: exception_test.h
 * Created Time: 2016-08-07 21:27:39
 * Last modified: 2016-12-01 17:46:55
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _EXCEPTION_TEST_H_
#define _EXCEPTION_TEST_H_

extern void exception_test(void);

#include <string>

using std::string;

/* 这个是定义的一个异常类 */
class illgalNumberExcep{
};

struct Excep{
    Excep(string s);
    ~Excep();
    void base(void);
    void base_outof_excep(void);
public:
    int number_check(char *str);
    int parse_number(char *str) throw(illgalNumberExcep);
    int outof_excep(void) throw(int, char);
};

#endif //_EXCEPTION_TEST_H_

