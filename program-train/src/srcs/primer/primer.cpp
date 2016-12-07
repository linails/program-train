/*
 * Progarm Name: primer.cpp
 * Created Time: 2016-10-28 16:16:59
 * Last modified: 2016-12-05 21:49:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include "primer.hpp"
#include <iostream>

#include "refrence_test.h"
#include "container_test.hpp"
#include "class_test.h"
#include "container_test.h"
#include "cast_test.h"
#include "function_test.h"
#include "drived_test.h"
#include "other.h"
#include "overload.h"
#include "lambda.h"
#include "template_test.h"
#include "ctest.h"
#include "regex_test.h"
#include "smart_pointer.h"
#include "thread_test.h"
#include "chrono_test.h"
#include "exception_test.h"

using std::cout;
using std::endl;

Primer::Primer()
{
    cout << endl;
    cout << "Beginning primer ..." << endl;
    cout << endl;
    {
#if 0
        refrence_test();
        cast_test();
        find_char2("hello",'e');
        const_test();
        drived_test();
        boost_test();
#endif
        //ctest();
        //regex_test();
        //smart_pointer();
        //other_test();
        //class_test();
        //chrono_test();
        //thread_test();
        //container_test();
        //exception_test();
        //lambda_test();
        //template_test();
        //overload_test();
    }
}

Primer::~Primer()
{
    cout << endl;
    cout << "Ending primer ..." << endl;
    cout << endl;
}




