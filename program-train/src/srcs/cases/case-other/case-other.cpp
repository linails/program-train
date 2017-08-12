/*
 * Progarm Name: case-other.cpp
 * Created Time: 2017-07-25 15:20:38
 * Last modified: 2017-07-25 18:17:02
 * @author: minphone.linails linails@foxmail.com 
 */

#include "case-other.hpp"
#include <iostream>
#include <cassert>
#include "stopwatch.h"
#include <unistd.h>

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

    ret = this->stopwatch_test();

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

