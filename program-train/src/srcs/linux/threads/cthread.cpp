/*
 * Progarm Name: cthread.cpp
 * Created Time: 2016-12-07 11:26:43
 * Last modified: 2016-12-07 12:29:31
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cthread.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <pthread.h>

using std::cout;
using std::endl;
using std::string;

cThread::cThread()
{
    cout << " cThread init ..." << endl;
}

cThread::~cThread()
{
}

int cThread::cthread_main(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

