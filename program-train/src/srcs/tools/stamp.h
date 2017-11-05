/*
 * Progarm Name: stamp.h
 * Created Time: 2017-11-02 11:26:24
 * Last modified: 2017-11-05 16:24:11
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _STAMP_H_
#define _STAMP_H_
#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * used like this:
     *
     * stamp(__FILE__, __FUNCTION__, __LINE__, "xxxx");
     * stamp(__FILE__, __FUNCTION__, __LINE__, NULL);
     * stamp(NULL , __FUNCTION__, __LINE__, NULL);
     * stamp(NULL , NULL, __LINE__, NULL);
     *
     * */
    extern int  stamp(const char *file, const char *func, int line, const char *tag);

#ifdef __cplusplus
}
#endif
#endif //_STAMP_H_

