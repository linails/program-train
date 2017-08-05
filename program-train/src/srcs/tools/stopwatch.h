/*
 * Progarm Name: stopwatch.h
 * Created Time: 2017-07-25 10:21:21
 * Last modified: 2017-07-25 17:26:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_
#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * used like this:
     *
     * sw_start(__FILE__);
     * sw_start(__FUNCTION__);
     * */
    extern int  sw_start(const char *name);

    /* 
     * used like this:
     *
     * | start           stamp   stop
     * +---^---+---+---+---^---+---^--
     * |      -3  -2  -1   0
     *
     * sw_stamp(__FUNCTION__, -1, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:100:000
     * sw_stamp(__FUNCTION__, -2, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:200:000
     * sw_stamp(__FUNCTION__, -3, __LINE__, ""); | [H:M:S:ms:us] 00:00:00:300:000
     *
     * 1. Default forward = -1
     * 2. if forward = 0, stamp() print out [H:M:S:ms:us] 00:00:00:000:000
     * */
    extern int  sw_stamp(const char *name, int forward, int line, const char *tag);

    /*
     * stop timing and release list
     *
     * used like this:
     *
     * sw_stop(__FILE__);
     * sw_stop(__FUNCTION__);
     * */
    extern int  sw_stop(const char *name);

#ifdef __cplusplus
}
#endif
#endif //_STOPWATCH_H_

