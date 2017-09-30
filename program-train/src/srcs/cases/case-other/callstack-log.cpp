/*
 * Progarm Name: callstack-log.cpp
 * Created Time: 2017-09-29 14:42:10
 * Last modified: 2017-09-30 11:44:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include "callstack-log.hpp"
#include <iostream>

using std::cout;
using std::endl;

void csl_func01(CallStackLog *csl)
{
    csl->add_call_func(__func__);
    csl_func02(csl->Fun(__func__));
    csl_func03(csl->Fun(__func__));
}

void csl_func02(CallStackLog *csl)
{
    csl->add_call_func(__func__);
    csl_func03(csl->Fun(__func__));
}

void csl_func03(CallStackLog *csl)
{
    csl->add_call_func(__func__);
}

CallStackLog::CallStackLog(const char *func)
{
    this->m_call_stack.push_back(func);
}

CallStackLog::~CallStackLog()
{
}

int  CallStackLog::add_call_func(const char *func)
{
    this->m_call_stack.push_back(func);
    return 0;
}

int  CallStackLog::disp_call_stack(void)
{
    cout << "CallStackLog::disp_call_stack() ..." << endl;

    for(auto &s : this->m_call_stack){
        cout << "Fn:" << s << endl;
    }

    return 0;
}

CallStackLog *CallStackLog::Fun(const char *func)
{
    cout << "Fun : " << func << endl;
    return this;
}


