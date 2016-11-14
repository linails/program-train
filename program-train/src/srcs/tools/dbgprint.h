/*
 * Progarm Name: dbgprint.h
 * Created Time: 2016-10-30 00:02:19
 * Last modified: 2016-10-30 00:04:01
 */

#ifndef _DBGPRINT_H_
#define _DBGPRINT_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

#ifdef DEBUG
#define dprint(format, ...) printf(format, ##__VA_ARGS__)
#else
#define dprint(format, ...)
#endif

#ifdef __cplusplus
}
#endif
#endif //_DBGPRINT_H_

