/*
 * Progarm Name: builder-product.cpp
 * Created Time: 2017-11-09 17:27:21
 * Last modified: 2017-11-10 14:53:51
 * @author: minphone.linails linails@foxmail.com 
 */

#include "builder-product.hpp"
#include "builder.hpp"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

BuilderProduct::BuilderProduct()
{
    printf("Fn: %s:%s()\n", __func__, __func__);
}

BuilderProduct::~BuilderProduct()
{
}

//
//BuilderProduct *BuilderProduct::create_product(Builder *builder)
//{
//    builder->build_product();
//    builder->build_part_I(10);
//    builder->build_part_II(20);
//    return builder->get_product();
//}

void BuilderProduct::part_I(int I)
{
    this->m_I = I;
}

void BuilderProduct::part_II(int II)
{
    this->m_II = II;
}

void BuilderProduct::show(void)
{
    printf("Fn: %s:%s()\n", __func__, __func__);
    printf("this->m_I = %d | this->m_II = %d \n", this->m_I, this->m_II);
}


