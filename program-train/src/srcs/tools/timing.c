/*
 * Progarm Name: timing.c
 * Created Time: 2016-04-29 22:44:41
 * Last modified: 2016-04-29 23:09:24
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "timing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>   //for gettimeofday()
#include "cenum.h"

static struct timeval start,stop;

static ebool timingflag = EFALSE;

/*start_timing*/
static void start_timing(void)
{
    if(timingflag == EFALSE){
        gettimeofday(&start,NULL);
        timingflag = ETRUE;
    }
}

/*stop_timing : return diffval time*/
static char *stop_timing(void)
{
    if(timingflag == ETRUE){
        gettimeofday(&stop,NULL);
        timingflag = EFALSE;
    }

    unsigned sec,msec,usec;
    sec  = stop.tv_sec - start.tv_sec;
    usec = stop.tv_usec - start.tv_usec;
    usec = stop.tv_usec > start.tv_usec ?
           stop.tv_usec - start.tv_usec :
           start.tv_usec - stop.tv_usec;
    msec = usec/1000;
    usec -= msec*1000;

    unsigned hour,min;
    min = sec/60;
    sec -= min*60;
    hour = min/60;
    min -= hour*60;

    static char buf[128];
    sprintf(buf,"[H:M:S:ms:us] %.2d:%.2d:%.2d:%.3d:%.3d"
            ,hour,min,sec,msec,usec);
    return buf;
}

/*ctiming ...*/
void ctiming(void)
{
    if(timingflag == EFALSE){
        start_timing();
    }else{
        char *diff = stop_timing();
        printf("Timing stop ! : %s\n",diff);
    }
}

