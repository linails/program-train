/*
 * Progarm Name: regex_cpp11.cpp
 * Created Time: 2016-06-16 11:24:06
 * Last modified: 2016-06-16 13:26:57
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "regex_cpp11.h"

/*gcc-5.3*/
/*c++11 regex*/
#include <regex>
#include <iostream>

using namespace std;

regex_cpp11::regex_cpp11()
{
}

regex_cpp11::~regex_cpp11()
{
}

void regex_cpp11::regex_t4(void)
{
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

    regex r(pattern);
    smatch results;

    string test_str("receipt freind theif receive");
    if(regex_search(test_str, results, r)){
        cout << results.str() << endl;
    }
}


//---------------------------------------------------------


