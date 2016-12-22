/*
 * Progarm Name: jump.h
 * Created Time: 2016-12-21 21:17:34
 * Last modified: 2016-12-21 21:22:11
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _JUMP_H_
#define _JUMP_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "object-c-macro.h"

    typedef struct cJumper_{
    cPrivate
        int  (*jumper_goto)(void);
        int  (*jumper_nonlocal)(void);
    cPublic
        int  (*cjumper_main)(void *cthis, int argc, char **argv);
        int  (*destructor)(struct cJumper_ **pobj);
    }cJumper_t;

    extern cJumper_t *cjumper_constructor(void);

    extern int  cjumper_constructor_safety(cJumper_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_JUMP_H_

