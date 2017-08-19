/*
 * Progarm Name: mbacktrace.h
 * Created Time: 2017-08-19 18:09:19
 * Last modified: 2017-08-19 19:09:18
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MBACKTRACE_H_
#define _MBACKTRACE_H_
#ifdef __cplusplus
extern "C" {
#endif

    #define M_BACKTRACE_DEPTH   32

    /* 
     * open backtrace 
     *  -> if you want to use backtrace , just use this function
     * */
    extern int  mbacktrace_open(void);

    /* 
     * close backtrace
     *  -> used for other Test | only used for Test
     * */
    extern int  mbacktrace_close(void);

#ifdef __cplusplus
}
#endif
#endif //_MBACKTRACE_H_

