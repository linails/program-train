/*
 * Progarm Name: factory-product.cpp
 * Created Time: 2017-11-09 15:18:03
 * Last modified: 2017-11-09 15:38:31
 * @author: minphone.linails linails@foxmail.com 
 */

#include "factory-product.hpp"
#include <iostream>

using std::cout;
using std::endl;

FactoryProduct::FactoryProduct()
{
}

FactoryProduct::~FactoryProduct()
{
}

ConcreteFactoryProduct::ConcreteFactoryProduct()
{
    cout << "Fn : ConcreteFactoryProduct::" << __func__ << "()" << endl;
}

ConcreteFactoryProduct::~ConcreteFactoryProduct()
{
}

