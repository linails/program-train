/*
 * Progarm Name: linear-list.cpp
 * Created Time: 2016-12-30 10:59:03
 * Last modified: 2017-01-03 14:50:44
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linear-list.hpp"
#include "linear-list-def.hpp"
#include "seq-list.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cout;
using std::endl;
using std::vector;
using std::string;

tLinearList::tLinearList()
{
}

tLinearList::~tLinearList()
{
}

int  tLinearList::linearlist_main(int argc, char **argv)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
#if 1
        assert(-1 != ret);
        tSeqList tsl;
        ret = tsl.tseqlist_main(argc, argv);
#endif
    }

    return ret;
}

