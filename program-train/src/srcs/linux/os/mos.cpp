/*
 * Progarm Name: mos.cpp
 * Created Time: 2016-11-25 09:24:26
 * Last modified: 2016-11-25 09:32:14
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mos.hpp"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

Mos::Mos()
{
}

Mos::~Mos()
{
}

string Mos::pwd(void)
{
    char buf[128] = {0, };

    getcwd(buf, sizeof(buf));

    return string(buf);
}

int Mos::pwd(string &cpath)
{
    char buf[128] = {0, };

    getcwd(buf, sizeof(buf));
    cpath = string(buf);

    if(cpath.length() > 0)
        return 0;
    else
        return -1;
}



