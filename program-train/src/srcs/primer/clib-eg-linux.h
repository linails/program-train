/*
 * Progarm Name: clib-eg-linux.h
 * Created Time: 2017-09-24 07:46:34
 * Last modified: 2017-10-22 12:12:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLIB_EG_LINUX_H_
#define _CLIB_EG_LINUX_H_
#ifdef __cplusplus
extern "C" {
#endif

    /* 
     * Note !
     *
     * cLibEgLinux_t 主要是针对 linux c 专有的 C 函数库
     * */

    #include "object-c-macro.h"

    typedef struct cLibEgLinux_ cLibEgLinux_t;
    typedef struct cLibEgLinux_{
    cPublic
        int  (*destructor)(cLibEgLinux_t **pobj);
        int  (*clibegLinux_main)(cLibEgLinux_t *cthis, int argc, char **argv);
    cPrivate
        int  (*test_for_getopt)(cLibEgLinux_t *cthis);
    }cLibEgLinux_t;

    //extern int  cLibEg_linux_constructor_safety(cLibEgLinux_t **pobj);
    extern int  cLibEg_linux_constructor_safety(cLibEgLinux_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_CLIB_EG_LINUX_H_

