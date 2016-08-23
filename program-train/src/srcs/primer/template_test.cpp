/*
 * Progarm Name: template_test.cpp
 * Created Time: 2016-02-02 16:38:52
 * Last modified: 2016-08-23 13:58:29
 * @author: minphone.linails linails@foxmail.com 
 */

#include "template_test.h"
#include <iostream>
#include <vector>
#include <string>
#include "generic_test.h"

using namespace std;

void template_test(void)
{
    cout << "--------- template_test ----------" << endl;
    {
        int a = 10,b = 12;
        cout << "a=10;b=12; max(a,b):" << mmax(a,b) << endl;
        cout << "max(12, 10) : " << mmax(12, 10) << endl;
    }
    cout << "---------------------------" << endl;
    {

        #if 0
        template<>
        string const max<const char*>(const char * const &a, const char * const &b);
        #endif

        const char *a = "nice";
        const char *b = "meet";
        cout << "a = 'nice' & b = 'meet' " << endl;
        cout << "max(a,b):" << mmax(a,b) << endl;
        cout << "max('nice', 'meet') : " << mmax("meet", "nice") << endl;
    }
}


