/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-06 22:31:58
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db_test.hpp"
#include "cases_main.h"
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
        db_test();
        ret = linux_main(argc, argv);
    }
    {
        //cases_main();
        //algorithm_main();
    }
    return ret;
}


