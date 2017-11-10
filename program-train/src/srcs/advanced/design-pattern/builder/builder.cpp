/*
 * Progarm Name: builder.cpp
 * Created Time: 2017-11-09 17:25:23
 * Last modified: 2017-11-10 15:08:38
 * @author: minphone.linails linails@foxmail.com 
 */

#include "builder.hpp"
#include <iostream>
#include "builder-product.hpp"
#include <cassert>

using std::cout;
using std::endl;

Builder::Builder()
{
}

Builder::~Builder()
{
}

void Builder::build_product(void)
{
    this->m_product = new BuilderProduct();
    if(nullptr == this->m_product){
        cout << "[Error] new BuilderProduct() failed !" << endl;
    }

    assert(nullptr != this->m_product);
}

BuilderProduct *Builder::get_product(void)
{
    return this->m_product;
}

ConcreateBuilderA::ConcreateBuilderA()
{
}

ConcreateBuilderA::~ConcreateBuilderA()
{
}

void ConcreateBuilderA::build_part_I(int part_I)
{
    printf("Fn: %s:%s()\n", __func__, __func__);
    this->m_product->part_I(part_I);
}

void ConcreateBuilderA::build_part_II(int part_II)
{
    printf("Fn: %s:%s()\n", __func__, __func__);
    this->m_product->part_II(part_II);
}

ConcreateBuilderB::ConcreateBuilderB()
{
}

ConcreateBuilderB::~ConcreateBuilderB()
{
}

void ConcreateBuilderB::build_part_I(int part_I)
{
    printf("Fn: %s:%s()\n", __func__, __func__);
    this->m_product->part_I(part_I * 10);
}

void ConcreateBuilderB::build_part_II(int part_II)
{
    printf("Fn: %s:%s()\n", __func__, __func__);
    this->m_product->part_II(part_II * 10);
}

