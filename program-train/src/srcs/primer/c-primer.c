/*
 * Progarm Name: c-primer.c
 * Created Time: 2016-12-09 23:18:58
 * Last modified: 2016-12-10 00:18:26
 * @author: minphone.linails linails@foxmail.com 
 */

#include "c-primer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctest.h"

int  cprimer_main(void *cthis, int argc, char **argv)
{
    printf(" cprimer_main ...\n");

    int ret = 0;

    //((cPrimer_t *)cthis)->other_test();

    ((cPrimer_t *)cthis)->process_token();

    return ret;
}

int  destructor(struct cPrimer_ **pobj)
{
    if(NULL != *pobj){
        free(*pobj);
        return 0;
    }else{
        printf("[Error] destructor is failed , because *pobj is null\n");
        return -1;
    }
}

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


//----------------------------------------------------------------------------------------------

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

        cprimer->cprimer_main = cprimer_main;

        return cprimer;
    }
}


