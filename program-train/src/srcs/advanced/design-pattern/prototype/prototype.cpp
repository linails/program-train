/*
 * Progarm Name: prototype.cpp
 * Created Time: 2017-11-14 22:55:00
 * Last modified: 2017-11-14 23:08:58
 * @author: minphone.linails linails@foxmail.com 
 */

#include "prototype.hpp"
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

ProtoType::ProtoType()
{
}

ProtoType::~ProtoType()
{
}

ConcreteProtoType::ConcreteProtoType()
{
    printf("Fn: %s | constructor\n", __func__);
}

ConcreteProtoType::~ConcreteProtoType()
{
}

ConcreteProtoType::ConcreteProtoType(const ConcreteProtoType &cpt)
{
    printf("Fn: %s | copy constructor\n", __func__);
}

ProtoType *ConcreteProtoType::Clone(void) const
{
    printf("Fn: %s \n", __func__);
    return new ConcreteProtoType(*this);
}

