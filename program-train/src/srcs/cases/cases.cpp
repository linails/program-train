/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 22:15:06
 * Last modified: 2017-03-31 13:45:44
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"
#include "dic-parser.hpp"
#include "exlibCases.hpp"
#include <cassert>
#include "key-bind-main.hpp"
#include "bit.hpp"
#include "tester-case001.hpp"

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

    /* 
     * exlib-cases
     * */
    {
        #if COMPILE_FLAG_exlibCases
        exlibCases exlibcases;

        ret = exlibcases.exlibcases_main(argc, argv); assert(-1 != ret);
        #endif
    }

    /* 
     * cases 001, 002 ,,,
     * */
    {
        #if COMPILE_FLAG_case001
        /*
         * case001 entry
         * */
        TesterCase001 infinite_loops;

        ret = infinite_loops.main(argc, argv); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case002
        /* 
         * case002
         * */
        DicParser *pdp = new DicParser();
        DicParser::get_instance(pdp);

        if(nullptr != pdp){
            ret = pdp->dicparser_main(argc, argv); assert(-1 != ret);
            delete pdp;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_case003
        /* 
         * case003
         * */
        KeyBind kbind;

        ret = kbind.keybind_main(argc, argv); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case004
        /* 
         * case004
         * */
        Bit bit;

        ret = bit.bit_main(argc, argv); assert(-1 != ret);
        #endif
    }

    return ret;
}

