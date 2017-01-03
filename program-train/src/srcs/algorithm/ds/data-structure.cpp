/*
 * Progarm Name: data-structure.cpp
 * Created Time: 2016-12-30 09:12:14
 * Last modified: 2017-01-03 14:47:57
 * @author: minphone.linails linails@foxmail.com 
 */

#include "data-structure.hpp"
#include <iostream>
#include <cassert>

#include "linear-list.hpp"

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

    {
        assert(-1 != ret);
        ret = this->linearlist(argc, argv);
    }

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

