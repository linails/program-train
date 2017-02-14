/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2017-02-14 09:42:54
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include "primer.hpp"
#include "db-caller.hpp"
#include "cases.hpp"
#include "malgorithm.hpp"
#include <cassert>
#include "container.hpp"
#include "mlinux.hpp"
#include "advanced.hpp"

using namespace std;

int main(int argc, char **argv)
{
    int ret = 0;

    {
        Primer  primer;

        ret = primer.primer_main(argc, argv); assert(-1 != ret);
    }
    {
#if 0
        Advanced advanced;

        ret = advanced.advanced_main(argc, argv); assert(-1 != ret);
#endif
    }
    {
#if 0
        Container container;

        assert(-1 != ret);
        ret = container.container_main(argc, argv);
#endif
    }
    {
#if 1
        dbCaller dbcaller;

        assert(-1 != ret);
        ret = dbcaller.dbcaller_main(argc, argv);
#endif
    }
    {
#if 1
        mLinux mlinux;

        assert(-1 != ret);
        ret = mlinux.mlinux_main(argc, argv);
#endif
    }
    {
#if 0
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


