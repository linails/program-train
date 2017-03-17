/*
 * Progarm Name: mos.cpp
 * Created Time: 2016-11-25 09:24:26
 * Last modified: 2017-03-15 18:59:59
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

string Mos::home(void)
{
    return getenv("HOME");
}

int  Mos::pwd(string &cpath)
{
    char buf[128] = {0, };

    getcwd(buf, sizeof(buf));
    cpath = string(buf);

    if(cpath.length() > 0)
        return 0;
    else
        return -1;
}

int  Mos::home(string &home)
{
    home = getenv("HOME"); return 0;
}


