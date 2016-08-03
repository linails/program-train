/*
 * Progarm Name: chrono_test.cpp
 * Created Time: 2016-07-30 22:14:29
 * Last modified: 2016-08-02 09:10:12
 */

#include "chrono_test.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void chrono_test(void)
{
    cout << "-----------chrono_test-----------" << endl;

    auto start = chrono::system_clock::now();

    this_thread::sleep_for(chrono::seconds(1));

    auto end = chrono::system_clock::now();

    int elapsed_seconds1 = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    int elapsed_seconds2 = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "elapsed_seconds(milliseconds) : " << elapsed_seconds1 << endl;
    cout << "elapsed_seconds(microseconds) : " << elapsed_seconds2 << endl;
}


