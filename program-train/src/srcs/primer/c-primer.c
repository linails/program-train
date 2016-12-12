/*
 * Progarm Name: c-primer.c
 * Created Time: 2016-12-09 23:18:58
 * Last modified: 2016-12-12 21:26:58
 * @author: minphone.linails linails@foxmail.com 
 */

#include "c-primer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctest.h"
#include <stdarg.h>

static
int  cprimer_main(void *cthis, int argc, char **argv)
{
    printf(" cprimer_main ...\n");

    int ret = 0;

    if(NULL != cthis){

        //((cPrimer_t *)cthis)->other_test();

        ((cPrimer_t *)cthis)->process_token();

        ((cPrimer_t *)cthis)->para_uncertainty(cthis);

    }else{
        ret = -1;
        printf("[Warning] cthis is NULL !\n");
    }
    return ret;
}

static
int  process_token(void)
{
    printf("process_token ...\n");

    /* 
     * "##" 运算符在宏定义中是构造特定的 "预处理单词" 的用途
     *
     *  #define XY x##y             : 被展开成 xy
     *  #define HASH_HASH # ## #    : 被展开成 ##, 两边的空格是必须的
     *  #define S(a,b) a##b         : S(1,2) -> 12 ; S(x,y) -> xy
     * */

    #define S(x,y) x##y

    printf("S(1,2) : %d\n", S(1,2));

    return 0;
}

static
int  para_uncertainty(void *cthis)
{
    /* 
     * 可变参数类型
     *  eg. #include <stdio.h>
     *      int printf(const char*, ...);
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  "..." 这个标点符号只用于函数声明和定义(此处还用于宏)
     *        它的作用是让编译器对出现在这部分的实参与形参不做类型与个数的检查
     *
     *  [注意：如果有其他参数，则 ... 只能用于指定最后面的参数]
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  为了保证不确定参数函数代码的可移植性，C语言标准库提供了一套宏
     *
     *  #include <stdarg.h>
     *  1> va_list ap   : 这个 ap 用于遍历各个"..."中的参数
     *  2> va_start(ap, 最后一个确定参数的类型) : 这是让 ap 获得初始值，即指向第一个可变参数
     *  3> va_arg(ap, 可变参数类型) : 求取当前可变参数的值，并把 ap 移至下一个可变参数
     *  4> va_copy(dst, src)    : C99内容，可以复制一个 ap 的副本，在src被改变的情况下，还可以重新从前面读取参数
     *  5> va_end(ap)   : 清理工作
     * */
    int ret = 0;

    printf("para_uncertainty ...\n");

    ret = ((cPrimer_t *)cthis)->pu_fun(1, 10);

    ret = ((cPrimer_t *)cthis)->pu_fun(2, 10, 20);

    return ret;
}

static
int  pu_fun(int n, ...)
{
    printf("call ... function \n");

    int ret = 0;

    printf("\nva_start ... \n");
    {
        int para = 0;

        va_list ap;
        va_start(ap, n);
        for(int i=0; i<n; i++){
            para = va_arg(ap, int);
            printf("para[%d] = %d\n", i, para);
        }
        va_end(ap);
    }
    printf("\nva_end ... \n");

    return ret;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(struct cPrimer_ **pobj)
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

cPrimer_t *cprimer_constructor(void)
{
    cPrimer_t *cprimer = (cPrimer_t *)malloc(sizeof(cPrimer_t));
    if(NULL == cprimer){
        printf("[Error] malloc failed\n");
        return NULL;
    }else{

        /* 
         * Loading all functions here !
         * */

        //cprimer->other_test = other_test;

        cprimer->destructor = destructor;

        cprimer->process_token = process_token;

        cprimer->para_uncertainty = para_uncertainty;

        cprimer->pu_fun = pu_fun;

        cprimer->cprimer_main = cprimer_main;

        return cprimer;
    }
}

int  cprimer_constructor_safety(cPrimer_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cPrimer_t *)malloc(sizeof(cPrimer_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */

            //cprimer->other_test = other_test;

            (*pobj)->destructor = destructor;

            (*pobj)->process_token = process_token;

            (*pobj)->para_uncertainty = para_uncertainty;

            (*pobj)->pu_fun = pu_fun;

            (*pobj)->cprimer_main = cprimer_main;
        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}

