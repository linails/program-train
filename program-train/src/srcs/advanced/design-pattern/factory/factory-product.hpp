/*
 * Progarm Name: factory-product.hpp
 * Created Time: 2017-11-09 15:18:08
 * Last modified: 2017-11-09 15:37:59
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FACTORY_PRODUCT_HPP_
#define _FACTORY_PRODUCT_HPP_

class FactoryProduct{
public:
    virtual ~FactoryProduct() = 0;
protected:
    FactoryProduct();
};

class ConcreteFactoryProduct: public FactoryProduct {
public:
    ConcreteFactoryProduct();
    ~ConcreteFactoryProduct();
private:
};

#endif //_FACTORY_PRODUCT_HPP_

