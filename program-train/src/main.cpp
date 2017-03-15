/*
 * Progarm Name: rebuild main.cpp
 * Created Time: 2016-04-28 17:23:45
 * Last modified: 2017-03-15 15:23:53
 * @author: minphone.linails linails@foxmail.com 
 */

#include <iostream>
#include <cassert>
#include "manager.hpp"

int main(int argc, char **argv)
{
    int ret = 0;

    Manager manager;

    ret = manager.main(argc, argv); assert(-1 != ret);

    return ret;
}


