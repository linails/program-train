/*
 * Progarm Name: algorithm_main.cpp
 * Created Time: 2016-08-14 10:35:26
 * Last modified: 2016-12-18 21:47:42
 */

#include "algorithm_main.h"
#include <iostream>
#include "non-mutating-algo.h"
#include "mutating-algo.h"
#include "sorting-algo.h"

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
        non_mutating_algo();

        //mutating_algo();

        //sorting_algo();
    }
    cout << "-----------------------------------------" << endl;
    {
        //data_structure_test();
    }

    return ret;
}

