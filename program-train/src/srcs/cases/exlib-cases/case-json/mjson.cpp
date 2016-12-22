/*
 * Progarm Name: mjson.cpp
 * Created Time: 2016-12-22 09:00:56
 * Last modified: 2016-12-22 09:10:47
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mjson.hpp"
#include <iostream>

using std::cout;
using std::endl;

mJson::mJson()
{
}

mJson::~mJson()
{
}

int  mJson::mjson_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->json_rapidjson();

    ret = this->json_cppjson();

    return ret;
}

int  mJson::json_rapidjson(void)
{
    int ret = 0;

    return ret;
}

int  mJson::json_cppjson(void)
{
    int ret = 0;

    return ret;
}

