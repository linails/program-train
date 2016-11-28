/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-11-27 18:48:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "sqlite3.h"

#include "refrence_test.h"
#include "container_test.hpp"
#include "class_test.h"
#include "container_test.h"
#include "cast_test.h"
#include "function_test.h"
#include "drived_test.h"
#include "other.h"
#include "overload.h"
#include "boost_test.h"
#include "lambda.h"
#include "template_test.h"
#include "ctest.h"
#include "regex_test.h"
#include "smart_pointer.h"
#include "thread_test.h"
#include "chrono_test.h"
#include "db_test.hpp"
#include "exception_test.h"
#include "cases_main.h"
#include "algorithm_main.h"
#include "linux_main.h"


using namespace std;

int main(int argc, char **argv)
{
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
    {
        db_test();
        //linux_main(argc, argv);
    }
    {
        //cases_main();
        //algorithm_main();
    }
    return 0;
}


