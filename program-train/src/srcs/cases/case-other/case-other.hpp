/*
 * Progarm Name: case-other.hpp
 * Created Time: 2017-07-25 15:20:34
 * Last modified: 2017-09-29 14:38:37
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CASE_OTHER_HPP_
#define _CASE_OTHER_HPP_

#define COMPILE_FLAG_Other_stopwatch    0
#define COMPILE_FLAG_Other_callstacklog 1

class CaseOther{
public:
    CaseOther();
    ~CaseOther();
    int  main(int argc, char **argv);
private:
    int  stopwatch_test(void);
    int  func01(void);
    int  func02(void);
private:
    int  callstack_log(void);
};

#endif //_CASE_OTHER_HPP_

