/*
 * Progarm Name: data-structure.c
 * Created Time: 2016-12-12 20:54:47
 * Last modified: 2016-12-12 21:25:51
 * @author: minphone.linails linails@foxmail.com 
 */

#include "data-structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static
int  cdatastruct_main(void *cthis, int argc, char **argv)
{
    int ret = 0;

    return ret;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(struct cDataStruct_ **pobj)
{
    int ret = 0;

    if(NULL != *pobj){
        free(*pobj);
        *pobj = NULL;
    }else{
        printf("[Error] destructor is failed , because *pobj is null\n");
        ret = -1;
    }

    return ret;
}

cDataStruct_t *cds_constructor(void)
{
    cDataStruct_t * cds = (cDataStruct_t *)malloc(sizeof(cDataStruct_t));

    if(NULL == cds){
        printf("[Error] malloc failed\n");
    }else{

        /* 
         * Loading all functions here !
         * */

        cds->cdatastruct_main = cdatastruct_main;

        cds->destructor = destructor;
    }

    return cds;
}

int  cds_constructor_safety(cDataStruct_t **pobj)
{
    int ret = 0;

    if(NULL == *pobj){
        *pobj = (cDataStruct_t *)malloc(sizeof(cDataStruct_t));

        if(NULL == *pobj){
            printf("[Error] constructor -> malloc failed\n");
            ret = -1;
        }else{

            /* 
             * Loading all functions here !
             * */

            (*pobj)->cdatastruct_main = cdatastruct_main;

            (*pobj)->destructor = destructor;
        }

    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}

