/*
 * Progarm Name: data-structure.h
 * Created Time: 2016-12-12 20:54:51
 * Last modified: 2017-05-31 17:35:53
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DATA_STRUCTURE_H_
#define _DATA_STRUCTURE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "object-c-macro.h"

    typedef struct cDataStruct_{
    cPrivate
        int  (*bubble_sort)(void *cthis);
    cPublic
        int  (*cdatastruct_main)(void *cthis, int argc, char **argv);
        int  (*destructor)(struct cDataStruct_ **pobj);
    }cDataStruct_t;

    extern cDataStruct_t *cds_constructor(void);

    extern int  cds_constructor_safety(cDataStruct_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_DATA_STRUCTURE_H_

