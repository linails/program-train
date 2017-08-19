/*
 * Progarm Name: backtrace.cpp
 * Created Time: 2017-08-18 23:25:08
 * Last modified: 2017-08-19 20:53:00
 * @author: minphone.linails linails@foxmail.com 
 */

#include "backtrace.hpp"
#include <iostream>

#include <execinfo.h>   // for backtrace()
#include <signal.h>     // for signal

using std::cout;
using std::endl;

Backtrace::Backtrace()
{
    signal(SIGSEGV, Backtrace::bt_dump);
}

Backtrace::~Backtrace()
{
}

void Backtrace::bt_dump(int signo)
{
    int         nptrs   = 0;
    char      **strings = nullptr;
    void       *btbuffer[BT_DEPTH] = {nullptr, };

    cout << "catpure signal : " << signo << endl;

    nptrs = backtrace(btbuffer, BT_DEPTH);
    printf("nptrs = %d\n", nptrs);

    strings = backtrace_symbols(btbuffer, nptrs);
    if (nullptr == strings) {
        perror("backtrace_symbols");
        exit(1);
    }

    for (int i = 0; i < nptrs; ++i) {
        printf(" [%02d] %s\n", i, strings[i]);
    }

    free(strings);


    /* 
     * 恢复信号默认处理
     * */
    signal(signo, SIG_DFL);
    raise(signo);
}

int  Backtrace::segmentfault_test(void)
{
    int ret = 0;

    int *p = nullptr;

    /* 
     * 此处是用于引发系统 segment fault 的测试
     * */
    *p = 10;

    return ret;
}

