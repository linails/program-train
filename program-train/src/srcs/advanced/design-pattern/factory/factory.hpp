/*
 * Progarm Name: factory.hpp
 * Created Time: 2017-11-09 15:10:21
 * Last modified: 2017-11-09 15:49:36
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

class FactoryProduct;


/*
 * Factory 模式不仅仅是提供了创建对象的接口，其最重要的是延迟了子类的实例化
 *
 * 但是 Factory 仅仅限制于同一个 基类 的对象，如果基类对象不同，则不能使用，需要使用 abstract factory
 * */

class Factory{
public:
    virtual ~Factory() = 0;
    virtual FactoryProduct *create_product() = 0;
protected:
    Factory();
};

class ConcreteFactory : public Factory{
public:
    ConcreteFactory();
    ~ConcreteFactory();
    FactoryProduct *create_product();
private:
};

#endif //_FACTORY_HPP_

