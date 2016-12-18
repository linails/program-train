/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2016-12-18 21:52:43
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db_test.hpp"
#include "cases.hpp"
#include "algorithm_main.h"
#include "linux_main.h"
#include <cassert>

using namespace std;

int main(int argc, char **argv)
{
    int ret = 0;

    {
        Primer  primer;

        ret = primer.primer_main(argc, argv);
    }
    {
#if 0
        assert(-1 != ret);
        db_test();
        //ret = linux_main(argc, argv);
#endif
    }
    {
#if 1
        Cases cases;

        assert(-1 != ret);
        ret = cases.cases_main(argc, argv);
#endif
    }
    {
#if 0
        mAlgorithm  malgo;

        assert(-1 != ret);
        ret = malgo.malgo_main(argc, argv);
#endif
    }
    return ret;
}


