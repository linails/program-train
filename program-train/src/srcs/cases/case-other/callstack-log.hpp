/*
 * Progarm Name: callstack-log.hpp
 * Created Time: 2017-09-29 14:42:04
 * Last modified: 2017-09-30 11:42:24
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CALLSTACK_LOG_HPP_
#define _CALLSTACK_LOG_HPP_

#include <vector>
#include <string>

using std::vector;
using std::string;

class CallStackLog;

void csl_func01(CallStackLog *csl);
void csl_func02(CallStackLog *csl);
void csl_func03(CallStackLog *csl);

class CallStackLog{
public:
    CallStackLog(const char *func);
    ~CallStackLog();
    int  add_call_func(const char *func);
    int  disp_call_stack(void);
    CallStackLog *Fun(const char *func);
private:
    vector<string>  m_call_stack;
};

#endif //_CALLSTACK_LOG_HPP_

