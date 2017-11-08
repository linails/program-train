/*
 * Progarm Name: clib-eg-linux.c
 * Created Time: 2017-09-24 07:46:29
 * Last modified: 2017-11-07 18:31:47
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

    /* 
     * getopt() / getopt_long() 不能在同一个程序中一块运行，否则会有错误
     * 两者只能运行其中一个
     * */
    {
        #if 0
        ret = cthis->test_for_getopt(cthis); assert(-1 != ret); printf("-------------------------------------\n");
        #else
        ret = cthis->test_for_getopt_long(cthis); assert(-1 != ret); printf("-------------------------------------\n");
        #endif
    }

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
    char *optstring = "a:b:c:d"; // 如果选项带参数，则必须在选项后面加 ":" | 这里的 d 就表示后面不带参数

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

static
int  test_for_getopt_long(cLibEgLinux_t *cthis)
{
    /*
     * getopt_long/getopt_long_only 是 getopt 的泛集，getopt是getopt_long 的一个子集
     * getopt支持的所有特性，getopt_long 都支持
     *
     * getopt_long 比 getopt 增加了长选项的解析
     *
     * getopt_long 与 getopt_long_only 的区别在于 getopt_long 仅仅只能将 "--" 开始的选项视为长选项
     *   getopt_long_only 将 "-" 开头的选项也会视为长选项，当长选项列表均不满足的时候，且短选项满足的时候，作为短选项进行解析
     * */

    /*
     * 如果 getopt_long 只想接受短选项，则 longopts 为 NULL; 如果只想接受长选项，则 optstring 为 NULL
     *
     * 长选项的参数格式： --arg=param / --arg param / --a=param / --a param
     * */


    /*
     * struct option {
     *    const char *name;  : 长选项名
     *    int has_arg;       : 是否带参数标志
     *          #define no_argument       0
     *          #define required_argument 1
     *          #define optional_argument 2
     *
     *    int *flag;         : flag 和 val 相关，如果 flag = NULL , 函数返回 val 的值 \
     *    int val;           : 否则 val 写入 flag 指针指向的变量中
     *                         这里的函数指 getopt_long() 解析比如读到的 read ，返回 r
     * }
     *
     * */
    struct option long_options[] = {
        {"read", 0, NULL, 'r'},
        {"dst", 1, NULL, 'd'},
        {"src", 1, NULL, 's'},
    };

    int opt = -1;
    char *optstring = "rd:s:"; // 如果选项带参数，则必须在选项后面加 ":"
    int option_index = 0;

    char *sargv[] = {
        "exe",
        "--read",
        "--src",
        "200",
        "--dst",
        "300"
    };

    while(-1 != (opt = getopt_long(sizeof(sargv)/sizeof(sargv[0]), sargv, optstring, long_options, &option_index))){
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
            (*pobj)->test_for_getopt_long = test_for_getopt_long;

        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}


