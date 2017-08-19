/*
 * Progarm Name: mbacktrace.c
 * Created Time: 2017-08-19 18:09:15
 * Last modified: 2017-08-19 20:52:34
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mbacktrace.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <execinfo.h>   // for backtrace()
#include <signal.h>     // for signal

static void bt_dump(int signo);

void bt_dump(int signo)
{
    int         nptrs   = 0;
    char      **symbols = NULL;
    void       *btbuffer[M_BACKTRACE_DEPTH] = {NULL, };

    printf("[backtrace] Fn : %s() - Line : %d | catpure signal : %d\n", __FUNCTION__, __LINE__, signo);

    nptrs = backtrace(btbuffer, M_BACKTRACE_DEPTH);
    printf("nptrs = %d\n", nptrs);

    symbols = backtrace_symbols(btbuffer, nptrs);
    if (NULL == symbols) {
        perror("backtrace_symbols");
        exit(1);
    }

    for (int i = 0; i < nptrs; ++i) {
        printf(" [%02d] %s\n", i, symbols[i]);
    }

    free(symbols);


    /* 
     * restore signal to default processing
     * */
    signal(signo, SIG_DFL);
    raise(signo);
}

/* 
 * open backtrace 
 *  -> if you want to use backtrace , just use this function
 * */
int  mbacktrace_open(void)
{
    #if 0
    /*
     * reference : sigaction() and ANSI C
     * --------------------------------
     * because sigaction is a POSIX system call.
     *
     * compile error free:
     *  gcc xxx.c -std=gnu99
     *  gcc xxx.c -std=gnu9x
     *
     * compile error :
     *  gcc xxx.c -std=c99
     * */
    struct sigaction act;

    act.sa_handler  = bt_dump;
    sigemptyset(&act.sa_mask);
    act.sa_flags    = 0;

    sigaction(SIGSEGV, &act, 0);
    #else
    signal(SIGSEGV, bt_dump);
    #endif

    return 0;
}

/* 
 * close backtrace
 *  -> used for other Test | only used for Test
 * */
int  mbacktrace_close(void)
{
    return 0;
}

