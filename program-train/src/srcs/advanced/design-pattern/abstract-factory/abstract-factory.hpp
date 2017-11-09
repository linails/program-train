/*
 * Progarm Name: abstract-factory.hpp
 * Created Time: 2017-11-09 15:57:01
 * Last modified: 2017-11-09 17:04:16
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _ABSTRACT_FACTORY_HPP_
#define _ABSTRACT_FACTORY_HPP_


class AbstractProductA;
class AbstractProductB;

/*
 * AbstractFactory 的关键是将 一组对象 的创建，封装到一个用于创建对象的类中
 *
 * 通过这个 "创建对象的类" 来统一维护创建的对象
 * */

class AbstractFactory{
public:
    virtual ~AbstractFactory() = 0;
    virtual AbstractProductA *create_productA(void) = 0;
    virtual AbstractProductB *create_productB(void) = 0;
protected:
    AbstractFactory();
};

class ConcreteFactoryI : public AbstractFactory{
public:
    ConcreteFactoryI();
    ~ConcreteFactoryI();
    AbstractProductA *create_productA(void);
    AbstractProductB *create_productB(void);
private:
};

class ConcreteFactoryII : public AbstractFactory{
public:
    ConcreteFactoryII();
    ~ConcreteFactoryII();
    AbstractProductA *create_productA(void);
    AbstractProductB *create_productB(void);
private:
};

#endif //_ABSTRACT_FACTORY_HPP_

