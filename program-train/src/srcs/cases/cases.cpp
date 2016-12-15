/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 13:32:22
 * Last modified: 2016-12-15 13:34:02
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"

using std::cout;
using std::endl;

Cases::Cases()
{
}

Cases::~Cases()
{
}

int  Cases::cases_main(int argc, char **argv)
{
    int ret = 0;

    /* case01 entry */
    test_main();

    return ret;
}

