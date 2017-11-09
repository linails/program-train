/*
 * Progarm Name: abstract-product.cpp
 * Created Time: 2017-11-09 16:23:02
 * Last modified: 2017-11-09 16:38:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "abstract-product.hpp"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

AbstractProductA::AbstractProductA()
{
}

AbstractProductA::~AbstractProductA()
{
}

AbstractProductB::AbstractProductB()
{
}

AbstractProductB::~AbstractProductB()
{
}

ConcreteAbstractProductA1::ConcreteAbstractProductA1()
{
    printf("Fn: %s:%s()\n", __func__, __func__);
}

ConcreteAbstractProductA1::~ConcreteAbstractProductA1()
{
}

ConcreteAbstractProductA2::ConcreteAbstractProductA2()
{
    printf("Fn: %s:%s()\n", __func__, __func__);
}

ConcreteAbstractProductA2::~ConcreteAbstractProductA2()
{
}

ConcreteAbstractProductB1::ConcreteAbstractProductB1()
{
    printf("Fn: %s:%s()\n", __func__, __func__);
}

ConcreteAbstractProductB1::~ConcreteAbstractProductB1()
{
}

ConcreteAbstractProductB2::ConcreteAbstractProductB2()
{
    printf("Fn: %s:%s()\n", __func__, __func__);
}

ConcreteAbstractProductB2::~ConcreteAbstractProductB2()
{
}


