/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-05 09:14:35
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
    {
        Primer  primer;
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


