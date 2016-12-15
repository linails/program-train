/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-15 13:41:15
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db_test.hpp"
#include "cases.hpp"
#include "mlinux.hpp"
#include "m-algorithm.hpp"


using namespace std;

int main(int argc, char **argv)
{
    int ret = 0;

    {
        Primer  primer;
    }
    {
        db_test();
    }
    {
        mLinux mlinux;

        ret = mlinux.mlinux_main(argc, argv);
    }
    {
#if 0
        Cases cases;

        ret = cases.cases_main();
#endif
    }
    {
#if 0
        mAlgorithm malgorithm;

        ret = malgorithm.algorithm_main(argc, argv);
#endif
    }
    return ret;
}


