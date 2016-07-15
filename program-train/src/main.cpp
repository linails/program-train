/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-07-14 19:22:08
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "object_c.h"
#include "sqlite3.h"

#include "refrence_test.h"
#include "container_test.h"
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
#include "generic_test.h"
#include "thread_test.h"

#include "insertion_sort.h"

using namespace std;

int main(void)
{
    {
#if 0
        refrence_test();
        class_test();
        cast_test();
        find_char2("hello",'e');
        const_test();
        drived_test();
        overload_test();
        boost_test();
        template_test();
        ctest();
#endif
        //regex_test();
        //smart_pointer();
        //other_test();
        generic_test();
        thread_test();
        //container_test();
        //lambda_test();
    }
    {
#if 0
        insertion_sort_test();
#endif
    }

    {
#if 0
    sqlite3 *db = NULL;
    sqlite3_open("first.db",&db);
    sqlite3_close(db);
#endif
    }
    return 0;
}


