/*
 * Description: 
 * Copyright (C),2015-201x, minphone.linails
 * This program is protected by copyright laws
 * Progarm Name: object_c.h
 * Created Time: 2015-12-06 09:53:28
 * Last modified: 2015-12-06 10:05:00
 * @author: minphone.linails linails@foxmail.com 
 * @version 1.0
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

