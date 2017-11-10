/*
 * Progarm Name: builder-product.hpp
 * Created Time: 2017-11-09 17:27:16
 * Last modified: 2017-11-10 14:52:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _BUILDER_PRODUCT_HPP_
#define _BUILDER_PRODUCT_HPP_


/* 
 * builder 模式是将一个复杂对象的构建与它的表示进行分离
 *
 * 使得同样的构建过程，在传入参数时可以创建不同的表示
 * */

class Builder;

class BuilderProduct{
public:
    BuilderProduct();
    ~BuilderProduct();
    void part_I(int);
    void part_II(int);
    void show(void);
    //BuilderProduct *create_product(Builder *builder);
private:
    int     m_I  = -1;
    int     m_II = -1;
};

#endif //_BUILDER_PRODUCT_HPP_

