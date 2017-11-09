/*
 * Progarm Name: abstract-product.hpp
 * Created Time: 2017-11-09 16:22:56
 * Last modified: 2017-11-09 16:28:25
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _ABSTRACT_PRODUCT_HPP_
#define _ABSTRACT_PRODUCT_HPP_

class AbstractProductA{
public:
    virtual ~AbstractProductA() = 0;
protected:
    AbstractProductA();
};

class AbstractProductB{
public:
    virtual ~AbstractProductB() = 0;
protected:
    AbstractProductB();
};

class ConcreteAbstractProductA1 : public AbstractProductA{
public:
    ConcreteAbstractProductA1();
    ~ConcreteAbstractProductA1();
private:
}; 

class ConcreteAbstractProductA2 : public AbstractProductA{
public:
    ConcreteAbstractProductA2();
    ~ConcreteAbstractProductA2();
private:
};

class ConcreteAbstractProductB1 : public AbstractProductB{
public:
    ConcreteAbstractProductB1();
    ~ConcreteAbstractProductB1();
private:
};

class ConcreteAbstractProductB2 : public AbstractProductB{
public:
    ConcreteAbstractProductB2();
    ~ConcreteAbstractProductB2();
private:
};

#endif //_ABSTRACT_PRODUCT_HPP_

