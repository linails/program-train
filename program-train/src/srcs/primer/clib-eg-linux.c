/*
 * Progarm Name: clib-eg-linux.c
 * Created Time: 2017-09-24 07:46:29
 * Last modified: 2017-09-24 07:52:13
 * @author: minphone.linails linails@foxmail.com 
 */

#include "clib-eg-linux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static
int  clibegLinux_main(void *cthis, int argc, char **argv)
{
    return 0;
}

//----------------------------------------------------------------------------------------------

static
int  destructor(struct cLibEgLinux_ **pobj)
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

cLibEgLinux_t *clibeg_linux_constructor(void)
{
    cLibEgLinux_t *clibegLinux = (cLibEgLinux_t *)malloc(sizeof(cLibEgLinux_t));
    if(NULL == clibegLinux){
        printf("[Error] malloc failed\n");
        return NULL;
    }else{

        /* 
         * Loading all functions here !
         * */

        clibegLinux->destructor = destructor;

        clibegLinux->clibegLinux_main = clibegLinux_main;

        return clibegLinux;
    }
}

int  clibeg_linux_constructor_safety(cLibEgLinux_t **pobj)
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
        }
    }else{
        printf("[Error] constructor -> *pobj is not NULL !\n");
        ret = -1;
    }

    return ret;
}


