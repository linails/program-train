/*
 * Progarm Name: exlibCases.cpp
 * Created Time: 2016-12-21 10:05:59
 * Last modified: 2017-03-31 13:48:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "exlibCases.hpp"
#include <iostream>
#include "mjson.hpp"
#include "case-gtest.hpp"
#include <cassert>
#include "xml-main.hpp"

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
        #if COMPILE_FLAG_exlib_json
        mJson mjson;

        ret = mjson.mjson_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_exlib_gtest
        CaseGtest cg;

        ret = cg.cg_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_exlib_xml
        xmlMain   parser;

        ret = parser.main(argc, argv); assert(-1 != ret);
        #endif
    }

    return ret;
}

