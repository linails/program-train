/*
 * Progarm Name: c-primer.h
 * Created Time: 2016-12-09 23:19:02
 * Last modified: 2016-12-12 20:44:54
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _C_PRIMER_H_
#define _C_PRIMER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "object-c-macro.h"

    typedef struct cPrimer_{
    cPrivate
        void (*other_test)(void);
        int  (*process_token)(void);
        int  (*para_uncertainty)(void *cthis);
        int  (*pu_fun)(int n, ...);
    cPublic
        int  (*cprimer_main)(void *cthis, int argc, char **argv);
        int  (*destructor)(struct cPrimer_ **pobj);
    }cPrimer_t;

    extern cPrimer_t *cprimer_constructor(void);

    extern int  cprimer_constructor_safety(cPrimer_t **pobj);

#ifdef __cplusplus
}
#endif
#endif //_C_PRIMER_H_

