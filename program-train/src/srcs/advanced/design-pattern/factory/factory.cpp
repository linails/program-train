/*
 * Progarm Name: factory.cpp
 * Created Time: 2017-11-09 15:10:25
 * Last modified: 2017-11-09 15:38:42
 * @author: minphone.linails linails@foxmail.com 
 */

#include "factory.hpp"
#include <iostream>
#include "factory-product.hpp"

using std::cout;
using std::endl;

Factory::Factory()
{
}

Factory::~Factory()
{
}

ConcreteFactory::ConcreteFactory()
{
    cout << "Fn: ConcreteFactory:" << __func__ << "()" << endl;
}

ConcreteFactory::~ConcreteFactory()
{
}

FactoryProduct *ConcreteFactory::create_product()
{
    FactoryProduct *product = new ConcreteFactoryProduct();
    if(nullptr == product){
        cout << "[Error] new ConcreteFactory() faild !" << endl;
    }

    return product;
}


