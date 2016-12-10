/*
 * Progarm Name: cthread.hpp
 * Created Time: 2016-12-07 11:26:51
 * Last modified: 2016-12-10 13:08:28
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CTHREAD_HPP_
#define _CTHREAD_HPP_

#include "timer.h"

class cThread{
public:
    cThread();
    ~cThread();
    int cthread_main(int argc, char **argv);
private:
    int  timing_create_thread(void);
    static void *child(void *arg);
private:
    static Timer    timer0;
    static Timer    timer1;
};

#endif //_CTHREAD_HPP_

