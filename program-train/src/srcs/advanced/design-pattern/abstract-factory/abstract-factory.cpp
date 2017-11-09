/*
 * Progarm Name: abstract-factory.cpp
 * Created Time: 2017-11-09 15:57:05
 * Last modified: 2017-11-09 17:14:00
 * @author: minphone.linails linails@foxmail.com 
 */

#include "abstract-factory.hpp"
#include <iostream>
#include "abstract-product.hpp"

using std::cout;
using std::endl;

AbstractFactory::AbstractFactory()
{
}

AbstractFactory::~AbstractFactory()
{
}

ConcreteFactoryI::ConcreteFactoryI()
{
}

ConcreteFactoryI::~ConcreteFactoryI()
{
}

AbstractProductA *ConcreteFactoryI::create_productA(void)
{
    AbstractProductA *productA = new ConcreteAbstractProductA1();
    if(nullptr == productA){
        cout << "[Error] new ConcreteAbstractProductA1() faild !" << endl;
    }

    return productA;
}

AbstractProductB *ConcreteFactoryI::create_productB(void)
{
    AbstractProductB *productB = new ConcreteAbstractProductB1();
    if(nullptr == productB){
        cout << "[Error] new ConcreteAbstractProductB1() faild !" << endl;
    }

    return productB;
}

ConcreteFactoryII::ConcreteFactoryII()
{
}

ConcreteFactoryII::~ConcreteFactoryII()
{
}

AbstractProductA *ConcreteFactoryII::create_productA(void)
{
    AbstractProductA *productA = new ConcreteAbstractProductA2();
    if(nullptr == productA){
        cout << "[Error] new ConcreteAbstractProductA1() faild !" << endl;
    }

    return productA;
}

AbstractProductB *ConcreteFactoryII::create_productB(void)
{
    AbstractProductB *productB = new ConcreteAbstractProductB2();
    if(nullptr == productB){
        cout << "[Error] new ConcreteAbstractProductB1() faild !" << endl;
    }

    return productB;
}


