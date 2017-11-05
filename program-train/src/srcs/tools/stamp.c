/*
 * Progarm Name: stamp.c
 * Created Time: 2017-11-02 11:26:21
 * Last modified: 2017-11-05 16:53:28
 * @author: minphone.linails linails@foxmail.com 
 */

#include "stamp.h"
#include <stdio.h>
#include <sys/time.h>   //for gettimeofday()
#include <string.h>

int  stamp(const char *file, const char *func, int line, const char *tag)
{
    char *HEAD          = "STAMP : [H:M:S:ms:us] ";
    char *TIME_FORMAT   = "%.2d:%.2d:%.2d:%.3d:%.3d";
    char buf_time[128]  = {0, };
    char buf_total[1024]= {0, };
    char buf_fn[512]    = {0, };
    char buf_func[256]  = {0, };
    char buf_tag[256]   = {0, };

    struct timeval  stamp;
    gettimeofday(&stamp, NULL);

    unsigned usec = stamp.tv_sec * 1000 * 1000 + stamp.tv_usec;
    unsigned sec, msec;
    unsigned hour, min;

    msec  = usec/1000;
    usec -= msec * 1000;

    sec   = msec / 1000;
    msec -= sec * 1000;
    min   = sec/60;
    sec  -= min*60;
    hour  = min/60;
    min  -= hour*60;

    sprintf(buf_time, TIME_FORMAT ,hour, min, sec, msec, usec);

    if(NULL != file){
        char *begin = strrchr(file, '/');
        if(NULL != begin){

            if(*++begin == '\0'){ begin--; }

            sprintf(buf_fn, "[File]: \"%s\" | ", begin);
        }else{
            sprintf(buf_fn, "[File]: \"%s\" | ", file);
        }
    }

    if(NULL != func)sprintf(buf_func, "[Fn]: %s() | ", func);
    if(NULL != tag) sprintf(buf_tag, " | [Tag] %s ", tag);

    sprintf(buf_total, "%s%s | %s%s[Line]: %d%s" , HEAD, buf_time, buf_fn, buf_func, line, buf_tag);

    printf("%s\n", buf_total);

    return 0;
}

