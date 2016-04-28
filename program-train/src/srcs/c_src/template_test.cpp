/*
 * Progarm Name: template_test.cpp
 * Created Time: 2016-02-02 16:38:52
 * Last modified: 2016-04-04 16:23:19
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "template_test.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void template_test(void)
{
    cout << "--------- template_test ----------" << endl;
    {
        int a = 10,b = 12;
        cout << "a=10;b=12; max(a,b):" << ::max(a,b) << endl;
    }
}


