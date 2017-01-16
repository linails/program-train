/*
 * Progarm Name: malgorithm.cpp
 * Created Time: 2016-08-14 10:35:26
 * Last modified: 2017-01-16 11:12:27
 */

#include "malgorithm.hpp"
#include <iostream>
#include "non-mutating-algo.h"
#include "mutating-algo.h"
#include "sorting-algo.h"
#include "data-structure.h"
#include "data-structure.hpp"
#include <cassert>

using namespace std;

mAlgorithm::mAlgorithm()
{
}

mAlgorithm::~mAlgorithm()
{
}

int  mAlgorithm::malgo_main(int argc, char **argv)
{
    int ret = 0;

    cout << "----------- algorithm_main -----------" << endl;
    {
        //non_mutating_algo();

        //mutating_algo();

        //sorting_algo();
    }
    cout << "----------- data structure --------------" << endl;
    {
#if 0
        /* 
         * version C
         * */
        cDataStruct_t *cds = NULL;

        if(0 == (ret = cds_constructor_safety(&cds))){
            if(NULL != cds){
                cout << "cDataStruct_t construct successed !" << endl;

                ret = cds->cdatastruct_main((void *)cds, argc, argv);

                if(0 == cds->destructor(&cds)){
                    cout << "cDataStruct_t destruct successed !" << endl;
                }
            }
        }
#endif
    }
    cout << "----------- data structure --------------" << endl;
    {
#if 0
        /* 
         * version C++
         * */
        DataStructure ds;

        ret = ds.datastruct_main(argc, argv); assert(-1 != ret);
#endif
    }

    return ret;
}

