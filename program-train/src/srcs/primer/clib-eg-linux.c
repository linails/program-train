/*
 * Progarm Name: clib-eg-linux.c
 * Created Time: 2017-09-24 07:46:29
 * Last modified: 2017-10-22 12:34:38
 * @author: minphone.linails linails@foxmail.com 
 */

#include "clib-eg-linux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>

static
int  clibegLinux_main(cLibEgLinux_t *cthis, int argc, char **argv)
{
    printf("File: %s | Fn: %s\n", __FILE__, __func__);

    int ret = 0;

    ret = cthis->test_for_getopt(cthis); assert(-1 != ret); printf("-------------------------------------\n");

    return ret;
}

static
int  test_for_getopt(cLibEgLinux_t *cthis)
{
    printf("Fn : %s\n", __func__);

    /*
     * 在 Linux 中，常用 getopt / getopt_long / getopt_long_only 来进行对命令行参数进行处理
     *
     * Note : 
     *
     *  #include <unistd.h>
     *  int getopt(int argc, char *const argv[], 
     *             const char *optstring);
     *
     *  extern char *optarg;
     *  extern int optind, opterr, optopt;
     *
     *  #include <getopt.h>
     *  int getopt_long(ing argc, char *const argv[],
     *                  const char *optstring,
     *                  const struct option *longopts, int *longindex);
     *
     *  int getopt_long_only(ing argc, char *const argv[],
     *                       const char *optstring,
     *                       const struct option *longopts, int *longindex);
     * */

    char *sargv[] = {
        "exe",
        "-a",
        "100",
        "-b",
        "200",
        "-c",
        "300"
    };

    int opt = -1;
    char *optstring = "a:b:c:d";

    while(-1 != (opt = getopt(sizeof(sargv)/sizeof(sargv[0]), sargv, optstring))){
        /*
         * opt 获得到 各个参数 a, b, c, d 
         * */
        printf("opt = %c\n", opt);

        printf("optarg = %s\n", optarg); // 参数值 100 , 200 , 300

        /*
         * optind 表示在下一个将要被处理的参数在 argv 中的下标值
         * */
        printf("optind = %d\n", optind);
    }

    return 0;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(cLibEgLinux_t **pobj)
{
    if(NULL != *pobj){
        free(*pobj);
        *pobj = NULL;
        return 0;
    }else{
        printf("[Error] destructor is failed , because *pobj is null\n");
        return -1;
    }
}

int  cLibEg_linux_constructor_safety(cLibEgLinux_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cLibEgLinux_t *)malloc(sizeof(cLibEgLinux_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */
            (*pobj)->destructor = destructor;
            (*pobj)->clibegLinux_main = clibegLinux_main;
            (*pobj)->test_for_getopt = test_for_getopt;

        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}


