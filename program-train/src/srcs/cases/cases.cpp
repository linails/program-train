/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 22:15:06
 * Last modified: 2017-01-01 18:21:42
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"
#include "dic-parser.hpp"
#include "exlibCases.hpp"
#include <cassert>

using std::cout;
using std::endl;

Cases::Cases()
{
}

Cases::~Cases()
{
}

int Cases::cases_main(int argc, char **argv)
{
    int ret = 0;

    {
        /* case01 entry */
        //test_main();
    }
    {
#if 1
        DicParser dp;

        assert(-1 != ret);
        ret = dp.dicparser_main(argc, argv);
#endif
    }
    {
        exlibCases exlibcases;

        assert(-1 != ret);
        ret = exlibcases.exlibcases_main(argc, argv);
    }

    return ret;
}

