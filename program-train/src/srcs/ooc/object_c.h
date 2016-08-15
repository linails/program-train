/*
 * Progarm Name: object_c.h
 * Created Time: 2015-12-06 09:53:28
 * Last modified: 2016-08-14 23:20:21
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _OBJECT_C_H_
#define _OBJECT_C_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "cenum.h"

typedef struct _ObjectString{
    void (*copy_string)(void *cthis,const char *string);
}ObjectString_t;


#ifdef __cplusplus
}
#endif
#endif //_OBJECT_C_H_

