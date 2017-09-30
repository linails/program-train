/*
 * Progarm Name: case-other.cpp
 * Created Time: 2017-07-25 15:20:38
 * Last modified: 2017-09-30 11:44:44
 * @author: minphone.linails linails@foxmail.com 
 */

#include "case-other.hpp"
#include <iostream>
#include <cassert>
#include "stopwatch.h"
#include <unistd.h>
#include "callstack-log.hpp"

using std::cout;
using std::endl;

CaseOther::CaseOther()
{
}

CaseOther::~CaseOther()
{
}

int  CaseOther::main(int argc, char **argv)
{
    int ret = 0;

    cout << "-------------------------------------" << endl;
    cout << "CaseOther::main() ..." << endl;
    {
        #if COMPILE_FLAG_Other_stopwatch
        ret = this->stopwatch_test(); assert(-1 != ret);
        #endif
    }
    cout << "-------------------------------------" << endl;
    {
        #if COMPILE_FLAG_Other_callstacklog
        ret = this->callstack_log(); assert(-1 != ret);
        #endif
    }
    cout << "-------------------------------------" << endl;

    return ret;
}

int  CaseOther::stopwatch_test(void)
{
    int ret = 0;

    sw_start(__FUNCTION__);
    cout << "CaseOther::main() ..." << endl;
    usleep(100 * 1000);
    sw_stamp(__FUNCTION__, -1, __LINE__, "");

    this->func02();
    this->func01();

    usleep(100 * 1000);
    sw_stamp(__FUNCTION__, -2, __LINE__, "");
    usleep(100 * 1000);
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    this->func02();

    sw_stop(__FUNCTION__);

    return ret;
}

int  CaseOther::func01(void)
{
    sw_start(__FUNCTION__);
    usleep(100 * 1000);
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");

    this->func02();

    sw_stop(__FUNCTION__);
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    return 0;
}

int  CaseOther::func02(void)
{
    sw_start(__FUNCTION__);
    usleep(100 * 1000);
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");
    sw_stamp(__FUNCTION__, -1, __LINE__, "");

    sw_stop(__FUNCTION__);
    return 0;
}

int  CaseOther::callstack_log(void)
{
    cout << "CaseOther::callstack_log() ..." << endl;

    CallStackLog csl(__func__);

    csl_func01((&csl)->Fun(__func__));

    csl.disp_call_stack();

    return 0;
}

