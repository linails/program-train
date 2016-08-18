/*
 * Progarm Name: refrence_test.cpp
 * Created Time: 2015-11-13 07:53:20
 * Last modified: 2016-08-18 18:06:07
 */

#include "refrence_test.h"
#include <iostream>

using namespace std;

/*refrence test func*/
void refrence_test(void)
{
    double dval = 3.14;
    const int &r1 = dval;
    const int &r2 = r1;

    cout << "dval = " << dval << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "---------------------------" << endl;
    dval = 4.23;
    cout << "dval = " << dval << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "---------------------------" << endl;

    int val = 12;
    int &r3 = val;
    int &r4 = r3;

    cout << "val = " << val << endl;
    cout << "r3 = " << r3 << endl;
    cout << "r4 = " << r4 << endl;
    cout << "---------------------------" << endl;
    cout << "val change" << endl;
    val = 15;
    cout << "val = " << val << endl;
    cout << "r3 = " << r3 << endl;
    cout << "r4 = " << r4 << endl;
    cout << "---------------------------" << endl;
    cout << "r4 change" << endl;
    r4 =18;
    cout << "val = " << val << endl;
    cout << "r3 = " << r3 << endl;
    cout << "r4 = " << r4 << endl;
    cout << "---------------------------" << endl;
}

