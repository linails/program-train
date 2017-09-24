/*
 * Progarm Name: dbgprint.h
 * Created Time: 2016-10-30 00:02:19
 * Last modified: 2017-09-24 08:16:22
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

//----------------------------------------------------------------------------------


/* 
 * ascii code 的颜色值
 *
 * 字背景色颜色范围：40 ~ 49    |   字颜色：30 ~ 39
 *          40: 黑                    30：黑
 *          41: 深红                  31：红
 *          42: 绿                    32：绿
 *          43: 黄色                  33：黄
 *          44: 蓝色                  34：蓝色
 *          45: 紫色                  35：紫色
 *          46: 深绿                  36：深绿
 *          47: 白色                  37：白色
 *
 *---------------------------------------------------------------
 *
 * __LINE__ 在源代码中插入当前源文件行号
 * __FILE__ 在源文件中插入当前源文件名
 * __DATE__ 在源文件插入当前的编译日期
 * __TIME__ 在源文件中插入当前的编译时间
 * __STDC__ 当前程序严格遵循 ANSI C 标准时，该标志被置为 1
 *
 * */

#ifdef DEBUG

#define F_OUT printf("%s:", __FUNCTION__); fflush(stdout);
#define L_OUT printf("%s:%d:", __FILE__, __LINE__); fflush(stdout);
#define A_OUT printf("%s:%d:%s", __FILE__, __LINE__, __FUNCTION__); fflush(stdout);
#define D_OUT printf("DEBUG:"); fflush(stdout);

#define dprintf(fmt, arg...)   D_OUT printf(fmt, ##arg)
#define dprintf_f(fmt, arg...) F_OUT printf(fmt, ##arg)
#define dprintf_l(fmt, arg...) L_OUT printf(fmt, ##arg)
#define dprintf_a(fmt, arg...) A_OUT printf(fmt, ##arg)

#else

#define F_OUT
#define L_OUT
#define A_OUT
#define D_OUT

#define dprintf(fmt, arg...)
#define dprintf_f(fmt, arg...)
#define dprintf_l(fmt, arg...)
#define dprintf_a(fmt, arg...)

#endif

#ifdef __cplusplus
}
#endif
#endif //_DBGPRINT_H_

