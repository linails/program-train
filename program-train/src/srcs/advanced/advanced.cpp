/*
 * Progarm Name: advanced.cpp
 * Created Time: 2017-01-09 17:40:22
 * Last modified: 2017-11-09 16:18:07
 * @author: minphone.linails linails@foxmail.com 
 */

#include "advanced.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include "design-pattern.hpp"

using std::cout;
using std::endl;
using std::string;

Advanced::Advanced()
{
}

Advanced::~Advanced()
{
}

int  Advanced::advanced_main(int argc, char **argv)
{
    cout << "---------------------------------------------------------" << endl;
    cout << "Advanced::advanced_main() ..." << endl;

    int ret = 0;
    {
        DesignPattern design_pattern;

        ret = design_pattern.do_action(); assert(-1 != ret);
    }
    cout << "---------------------------------------------------------" << endl;
    return ret;
}

