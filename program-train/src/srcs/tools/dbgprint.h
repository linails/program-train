/*
 * Progarm Name: dbgprint.h
 * Created Time: 2016-10-30 00:02:19
 * Last modified: 2017-04-14 17:21:04
 */

#ifndef _DBGPRINT_H_
#define _DBGPRINT_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#ifdef DEBUG

#define dprint(format, ...) printf(format, ##__VA_ARGS__)

/* 
 * reference : <<代码大全 第二版>>
 * */
#define ASSERT( condition, message) { \
    if( !(condition) ){               \
        dprint("Assertion failed : ", \
                #condition, message); \
                                      \
        exit(EXIT_FAILURE);           \
    }                                 \
}

#else

#define dprint(format, ...)
#define ASSERT( condition, message) {}

#endif

#ifdef __cplusplus
}
#endif
#endif //_DBGPRINT_H_

