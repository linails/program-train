/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-17 20:12:00
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db_test.hpp"
#include "cases.hpp"
#include "algorithm_main.h"
#include "linux_main.h"


using namespace std;

int main(int argc, char **argv)
{
    int ret = 0;

    {
        Primer  primer;
    }
    {
#if 0
        db_test();
        //ret = linux_main(argc, argv);
#endif
    }
    {
#if 0
        Cases cases;

        ret = cases.cases_main(argc, argv);
#endif
    }
    {
        //algorithm_main();
    }
    return ret;
}


