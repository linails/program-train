/*
 * Progarm Name: lambda.cpp
 * Created Time: 2016-03-28 20:57:04
 * Last modified: 2016-03-28 21:05:09
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "lambda.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

void lambda_test(void)
{
    vector<int> c {1,2,3,4,5,6,7};
    int x = 5;
    c.erase(remove_if(c.begin(),c.end(),[x](int n){return n < x;}),c.end());

    cout << "c : ";
    for(auto i : c){
        cout << i << ' ';
    }
    cout << endl;

    auto func1 = [](int i){return i + 4;};
    cout << "func 1 : " << func1(6) << endl;

    function<int(int)> func2 = [](int i){return i + 4;};
    cout << "func 2 : " << func2(6) << endl;
}


