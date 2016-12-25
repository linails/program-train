/*
 * Progarm Name: exlibCases.cpp
 * Created Time: 2016-12-21 10:05:59
 * Last modified: 2016-12-24 19:45:18
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exlibCases.hpp"
#include <iostream>
#include "mjson.hpp"

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

        ret = mjson.mjson_main(argc, argv);
#endif
    }

    return ret;
}

