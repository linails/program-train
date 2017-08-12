/*
 * Progarm Name: timer.cpp
 * Created Time: 2016-02-04 09:30:42
 * Last modified: 2017-07-26 09:36:51
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.3
 */

#include "timer.h"
#include <sys/time.h>   //for gettimeofday()
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

/*default constructor*/
Timer::Timer()
    :timingflag(false)
{
    start.tv_sec = 0;
    start.tv_usec = 0;
    stop.tv_sec = 0;
    stop.tv_usec = 0;
}

/*default destructor*/
Timer::~Timer()
{
}

/*timing : stop / start : toggle*/
void Timer::timing(void)
{
    if(timingflag == false){
        this->start_timing();
    }else{
        std::string diff(this->stop_timing());
        std::cout << "Timing stop ! : " << diff << std::endl;
    }
}

/*start_timing*/
void Timer::start_timing(void)
{
    if(timingflag == false){
        gettimeofday(&this->start,NULL);
        timingflag = true;
    }
}

/*stop_timing : return diffval time*/
std::string Timer::stop_timing(void)
{
    if(timingflag == true){
        gettimeofday(&this->stop,NULL);
        timingflag = false;
    }

    unsigned sec, msec, usec;
    unsigned hour, min;

    unsigned usec_start = start.tv_sec * 1000 * 1000 + start.tv_usec;
    unsigned usec_stop  = stop.tv_sec * 1000 * 1000 + stop.tv_usec;

    usec = usec_stop - usec_start;

    msec = usec/1000;
    usec -= msec * 1000;

    sec  = msec / 1000;
    msec -= sec * 1000;
    min = sec/60;
    sec -= min*60;
    hour = min/60;
    min -= hour*60;

    char buf[128];
    sprintf(buf,"[H:M:S:ms:us] %.2d:%.2d:%.2d:%.3d:%.3d"
            ,hour,min,sec,msec,usec);
    return buf;
}


