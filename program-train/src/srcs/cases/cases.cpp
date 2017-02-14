/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 22:15:06
 * Last modified: 2017-01-20 22:42:03
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"
#include "dic-parser.hpp"
#include "exlibCases.hpp"
#include <cassert>
#include "key-bind-main.hpp"

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

        ret = dp.dicparser_main(argc, argv); assert(-1 != ret);
#endif
    }
    {
#if 0
        exlibCases exlibcases;

        ret = exlibcases.exlibcases_main(argc, argv); assert(-1 != ret);
#endif
    }
    {
#if 0
        KeyBind kbind;

        ret = kbind.keybind_main(argc, argv); assert(-1 != ret);
#endif
    }

    return ret;
}

