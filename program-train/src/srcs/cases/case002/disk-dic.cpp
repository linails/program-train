/*
 * Progarm Name: disk-dic.cpp
 * Created Time: 2017-02-27 15:35:36
 * Last modified: 2017-02-27 15:39:20
 * @author: minphone.linails linails@foxmail.com 
 */

#include "disk-dic.hpp"
#include <iostream>
#include "sqlite3.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

DiskDic::DiskDic(string path)
    :m_path(path)
{
}

DiskDic::~DiskDic()
{
}


