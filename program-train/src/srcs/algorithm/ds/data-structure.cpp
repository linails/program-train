/*
 * Progarm Name: data-structure.cpp
 * Created Time: 2016-12-30 09:12:14
 * Last modified: 2017-01-06 11:10:39
 * @author: minphone.linails linails@foxmail.com 
 */

#include "data-structure.hpp"
#include <iostream>
#include <cassert>

#include "linear-list.hpp"
#include "mstack.hpp"

using std::cout;
using std::endl;

DataStructure::DataStructure()
{
}

DataStructure::~DataStructure()
{
}

int  DataStructure::datastruct_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->linearlist(argc, argv); assert(-1 != ret);

    ret = this->stack(); assert(-1 != ret);

    return ret;
}

int  DataStructure::linearlist(int argc, char **argv)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
#if 1
        assert(-1 != ret);
        tLinearList tll;
        ret = tll.linearlist_main(argc, argv);
#endif
    }

    return ret;
}

int  DataStructure::stack(void)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
        mStack ms;
        ret = ms.stack_main(0, NULL); assert(-1 != ret);
    }

    return ret;
}

