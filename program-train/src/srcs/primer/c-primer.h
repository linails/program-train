/*
 * Progarm Name: c-primer.h
 * Created Time: 2016-12-09 23:19:02
 * Last modified: 2017-10-22 12:02:52
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _C_PRIMER_H_
#define _C_PRIMER_H_
#ifdef __cplusplus
extern "C" {
#endif

    #include "object-c-macro.h"

    typedef struct cPrimer_ cPrimer_t;
    typedef struct cPrimer_{
    cPrivate
        int  (*other_test)(void);
        int  (*process_token)(void);
        int  (*para_uncertainty)(cPrimer_t *cthis);
        int  (*pu_fun)(int n, ...);
        int  (*gnu_c)(void);
        int  (*bit_field)(void);
        int  (*endian_check)(void);
        int  (*clibegLinux)(void);
    cPublic
        int  (*cprimer_main)(cPrimer_t *cthis, int argc, char **argv);
        int  (*destructor)(cPrimer_t **pobj);
    }cPrimer_t;

    extern cPrimer_t *cprimer_constructor(void);

    extern int  cprimer_constructor_safety(cPrimer_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_C_PRIMER_H_

