/*
 * Progarm Name: design-pattern.cpp
 * Created Time: 2017-02-14 10:04:05
 * Last modified: 2017-11-10 15:09:33
 * @author: minphone.linails linails@foxmail.com 
 */

#include "design-pattern.hpp"
#include <iostream>
#include "factory.hpp"
#include "factory-product.hpp"
#include <cassert>
#include "abstract-factory.hpp"
#include "abstract-product.hpp"
#include "builder-product.hpp"
#include "builder.hpp"
#include "direct.hpp"

using std::cout;
using std::endl;

DesignPattern::DesignPattern()
{
    cout << "------------------------ [START] DesignPattern ------------------------" << endl;
}

DesignPattern::~DesignPattern()
{
    cout << "------------------------ [END] DesignPattern ------------------------" << endl;
}

int  DesignPattern::do_action(void)
{
    int ret = 0;

    cout << "---------------------------------------------------------" << endl;
    {
        ret = this->factory(); assert(-1 != ret);
    }
    cout << "---------------------------------------------------------" << endl;
    {
        ret = this->abstract_factory(); assert(-1 != ret);
    }
    cout << "---------------------------------------------------------" << endl;
    {
        ret = this->builder(); assert(-1 != ret);
    }
    cout << "---------------------------------------------------------" << endl;

    return ret;
}

int  DesignPattern::factory(void)
{
    /*
     * 创建的时候只需要创建具体的 factory 
     *
     * 然后通过这个具体的 factory 来创建具体的 product
     *
     * 主要针对只有 一种 class 的创建
     * */

    Factory *factory = new ConcreteFactory();
    FactoryProduct *product = factory->create_product();

    if(nullptr != factory){ delete factory; }
    if(nullptr != product){ delete product; }

    return 0;
}

int  DesignPattern::abstract_factory(void)
{
    /*
     * 主要针对有 多种 class 的创建
     * */
    auto abs_factory = [](AbstractFactory  *factory){
        AbstractProductA *productA = factory->create_productA();
        AbstractProductB *productB = factory->create_productB();

        if(nullptr != productA){ delete productA; }
        if(nullptr != productB){ delete productB; }
        if(nullptr != factory){ delete factory; }
    };

    cout << "after new ConcreteFactoryI()" << endl;
    abs_factory(new ConcreteFactoryI());
    cout << endl;

    cout << "after new ConcreteFactoryII()" << endl;
    abs_factory(new ConcreteFactoryII());
    cout << endl;

    return 0;
}

int  DesignPattern::builder(void)
{
    Direct *direct = new Direct();

    {
        BuilderProduct *product = nullptr;
        ConcreateBuilderA builder;

        direct->construct(&builder);

        product = builder.get_product();
        product->show();

        if(nullptr != product){ delete product; }
    }
    cout << endl;
    {
        BuilderProduct *product = nullptr;
        ConcreateBuilderB builder;

        direct->construct(&builder);

        product = builder.get_product();
        product->show();

        if(nullptr != product){ delete product; }
    }

    if(nullptr != direct){ delete direct; }

    return 0;
}


