/*
 * Progarm Name: clib-eg.c
 * Created Time: 2017-09-22 12:58:57
 * Last modified: 2017-09-22 13:10:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include "clib-eg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static
int  clibeg_main(void *cthis, int argc, char **argv)
{
    return 0;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(struct cLibEg_ **pobj)
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

cLibEg_t *clibeg_constructor(void)
{
    cLibEg_t *clibeg = (cLibEg_t *)malloc(sizeof(cLibEg_t));
    if(NULL == clibeg){
        printf("[Error] malloc failed\n");
        return NULL;
    }else{

        /* 
         * Loading all functions here !
         * */

        clibeg->destructor = destructor;

        clibeg->clibeg_main = clibeg_main;

        return clibeg;
    }
}

int  clibeg_constructor_safety(cLibEg_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cLibEg_t *)malloc(sizeof(cLibEg_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */

            (*pobj)->destructor = destructor;

            (*pobj)->clibeg_main = clibeg_main;
        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}


