/*
 * Progarm Name: direct.cpp
 * Created Time: 2017-11-10 14:42:57
 * Last modified: 2017-11-10 14:54:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "direct.hpp"
#include <iostream>
#include "builder.hpp"

using std::cout;
using std::endl;

void Direct::construct(Builder *builder)
{
    builder->build_product();
    builder->build_part_I(10);
    builder->build_part_II(20);
}

