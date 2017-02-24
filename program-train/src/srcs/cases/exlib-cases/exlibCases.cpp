/*
 * Progarm Name: exlibCases.cpp
 * Created Time: 2016-12-21 10:05:59
 * Last modified: 2017-02-24 14:30:33
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exlibCases.hpp"
#include <iostream>
#include "mjson.hpp"
#include "case-gtest.hpp"
#include <cassert>

using std::cout;
using std::endl;

exlibCases::exlibCases()
{
}

exlibCases::~exlibCases()
{
}

int  exlibCases::exlibcases_main(int argc, char **argv)
{
    int ret = 0;

    {
        #if 0
        mJson mjson;

        ret = mjson.mjson_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if 1
        CaseGtest cg;

        ret = cg.cg_main(argc, argv); assert(-1 != ret);
        #endif
    }

    return ret;
}

