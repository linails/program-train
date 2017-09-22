/*
 * Progarm Name: clib-eg.h
 * Created Time: 2017-09-22 12:59:02
 * Last modified: 2017-09-22 13:02:34
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLIB_EG_H_
#define _CLIB_EG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "object-c-macro.h"

    typedef struct cLibEg_{
    cPrivate
    cPublic
        int  (*clibeg_main)(void *cthis, int argc, char **argv);
        int  (*destructor)(struct cLibEg_ **pobj);
    }cLibEg_t;

    extern cLibEg_t *clibeg_constructor(void);

    extern int  clibeg_constructor_safety(cLibEg_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_CLIB_EG_H_

