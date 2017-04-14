/*
 * Progarm Name: jump.c
 * Created Time: 2016-12-21 21:17:27
 * Last modified: 2016-12-21 21:37:04
 * @author: minphone.linails linails@foxmail.com 
 */

#include "jump.h"
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <assert.h>

static 
int  cjumper_main(void *cthis, int argc, char **argv)
{
    printf(" cjumper_main ...\n");

    int ret = 0;

    if(NULL != cthis){

        ret = ((cJumper_t *)cthis)->jumper_goto();

        assert(-1 != ret);
        ret = ((cJumper_t *)cthis)->jumper_nonlocal();

    }else{
        ret = -1;
        printf("[Warning] cthis is NULL !\n");
    }

    return ret;
}

static 
int  jumper_goto(void)
{
    int ret = 0;

    return ret;
}

static 
int  jumper_nonlocal(void)
{
    int ret = 0;

    return ret;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(struct cJumper_ **pobj)
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

cJumper_t *cjumper_constructor(void)
{
    cJumper_t *cjumper = (cJumper_t *)malloc(sizeof(cJumper_t));
    if(NULL == cjumper){
        printf("[Error] malloc failed\n");
        return NULL;
    }else{

        /* 
         * Loading all functions here !
         * */

        cjumper->jumper_goto = jumper_goto;

        cjumper->jumper_nonlocal = jumper_nonlocal;

        cjumper->destructor = destructor;

        cjumper->cjumper_main = cjumper_main;

        return cjumper;
    }
}

int  cjumper_constructor_safety(cJumper_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cJumper_t *)malloc(sizeof(cJumper_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */
            (*pobj)->jumper_goto = jumper_goto;

            (*pobj)->jumper_nonlocal = jumper_nonlocal;

            (*pobj)->destructor = destructor;

            (*pobj)->cjumper_main = cjumper_main;
        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}

