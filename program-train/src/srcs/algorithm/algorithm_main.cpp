/*
 * Progarm Name: algorithm_main.cpp
 * Created Time: 2016-08-14 10:35:26
 * Last modified: 2016-12-12 20:53:56
 */

#include "algorithm_main.h"
#include <iostream>
#include "non-mutating-algo.h"
#include "mutating-algo.h"
#include "sorting-algo.h"

using namespace std;

void algorithm_main(void)
{
    cout << "----------- algorithm_main -----------" << endl;
    {
        non_mutating_algo();

        //mutating_algo();

        //sorting_algo();
    }
    cout << "-----------------------------------------" << endl;
    {
        //data_structure_test();
    }
}


