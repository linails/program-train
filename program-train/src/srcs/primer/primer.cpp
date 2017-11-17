/*
 * Progarm Name: primer.cpp
 * Created Time: 2016-10-28 16:16:59
 * Last modified: 2017-11-17 10:24:50
 * @author: minphone.linails linails@foxmail.com 
 */

#include "primer.hpp"
#include <iostream>

#include "refrence_test.h"
#include "class_test.h"
#include "cast_test.h"
#include "function_test.h"
#include "drived_test.h"
#include "other.h"
#include "overload.h"
#include "lambda.h"
#include "template.hpp"
#include "regex_test.h"
#include "smart_pointer.h"
#include "thread_test.h"
#include "chrono_test.h"
#include "exception_test.h"
#include "c-primer.h"
#include "regex_cpp11.h"
#include <cassert>
#include "class-enhenced.hpp"
#include "jump.hpp"
#include "exception-ex.hpp"

using std::cout;
using std::endl;

Primer::Primer()
{
    cout << endl;
    cout << "Beginning primer ..." << endl;
    cout << endl;
}

int  Primer::primer_main(int argc, char **argv)
{
    int ret = 0;
    {
        #if COMPILE_FLAG_exception
        cout << "---------------------------------------------------------" << endl;
        exception_test();
        #endif
        #if COMPILE_FLAG_exception_ex
        cout << "---------------------------------------------------------" << endl;
        ExceptionEx ee; ret = ee.main(); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_regex
        cout << "---------------------------------------------------------" << endl;
        regex_test();
        #endif
    }
    {
        #if COMPILE_FLAG_smartpointer
        cout << "---------------------------------------------------------" << endl;
        smart_pointer();
        #endif
    }
    {
        #if COMPILE_FLAG_other
        cout << "---------------------------------------------------------" << endl;
        other_test();
        #endif
    }
    {
        #if COMPILE_FLAG_class
        cout << "---------------------------------------------------------" << endl;
        class_test();
        #endif
    }
    {
        #if COMPILE_FLAG_chrono
        cout << "---------------------------------------------------------" << endl;
        chrono_test();
        #endif
    }
    {
        #if COMPILE_FLAG_thread_cpp11
        cout << "---------------------------------------------------------" << endl;
        thread_test();
        #endif
    }
    {
        #if COMPILE_FLAG_overload
        cout << "---------------------------------------------------------" << endl;
        overload_test();
        #endif
    }

    #if COMPILE_FLAG_cprimer
    #if 0
    {
        cout << "---------------------------------------------------------" << endl;

        cPrimer_t *cprimer = cprimer_constructor();
        if(NULL != cprimer){
            cout << "cprimer constructor successed !" << endl;

            /* cPrimer main */
            cprimer->cprimer_main((void *)cprimer, 0, NULL);

            if(0 == cprimer->destructor(&cprimer)){
                cout << "cprimer destructor successed !" << endl;
            }
        }
    }
    #else
    {
        cout << "---------------------------------------------------------" << endl;

        cPrimer_t *cprimer = NULL;

        if(0 == cprimer_constructor_safety(&cprimer)){

            if(NULL != cprimer){
                cout << "cprimer constructor successed !" << endl;

                /* cPrimer main */
                cprimer->cprimer_main(cprimer, 0, NULL);

                if(0 == cprimer->destructor(&cprimer)){
                    cout << "cprimer destructor successed !" << endl;
                }
            }
        }
    }
    #endif
    #endif
    {
    #if COMPILE_FLAG_regex_cpp11
        cout << "---------------------------------------------------------" << endl;

        regex_cpp11 re;

        if(0 == (ret = re.regex_base())){
            cout << "cpp 11 regex successed !" << endl;
        }else{
            cout << "cpp 11 regex failed !" << endl;
        }
        assert(-1 != ret);

    #endif
    }
    {
    #if COMPILE_FLAG_lambda
        cout << "---------------------------------------------------------" << endl;
        mLambda mlambda;
        ret = mlambda.mlambda_main(argc, argv); assert(-1 != ret);
    #endif
    }
    {
    #if COMPILE_FLAG_class_enhenced
        cout << "---------------------------------------------------------" << endl;
        ClassEnhenced ce;
        ret = ce.class_enhenced_main(argc, argv); assert(-1 != ret);
    #endif
    }
    {
    #if COMPILE_FLAG_jumper 
        Jumper jumper;
        ret = jumper.main(argc, argv); assert(-1 != ret);
    #endif
    }

    cout << "---------------------------------------------------------" << endl;

    return ret;
}

Primer::~Primer()
{
    cout << endl;
    cout << "Ending primer ..." << endl;
    cout << endl;
}




