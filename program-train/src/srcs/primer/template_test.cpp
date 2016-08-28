/*
 * Progarm Name: template_test.cpp
 * Created Time: 2016-02-02 16:38:52
 * Last modified: 2016-08-24 11:13:44
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
        cout << "max(13, 11) : " << mmax<int>(13, 10) << endl;
    }
    cout << "---------------------------" << endl;
    {

        #if 0
        template<>
        string const max<const char*>(const char * const &a, const char * const &b);
        #endif

        const char *b = "meet";
        const char *a = "nicex";
        cout << "typeid(a).name() : " << typeid(a).name() << endl;
        cout << "a = 'nice' & b = 'meet' " << endl;
        cout << "max(a,b) : " << mmax(a,b) << endl; /* 如果是相同的4个字节，就可以编译通过 */
        cout << "max<const char *>('meet', 'nicex') : " << mmax<const char *>("meet", "nicex") << endl;

        string sa("nicex");
        string sb("meet");
        cout << "sa = " << sa << endl;
        cout << "sb = " << sb << endl;
        if(sa > sb) cout << "sa > sb" << endl;
        else cout << "sa < sb" << endl;
        cout << "max(sa,sb) : " << mmax(sa, sb) << endl;
    }
}


