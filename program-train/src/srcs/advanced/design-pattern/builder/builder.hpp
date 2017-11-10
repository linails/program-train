/*
 * Progarm Name: builder.hpp
 * Created Time: 2017-11-09 17:25:19
 * Last modified: 2017-11-10 15:06:24
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _BUILDER_HPP_
#define _BUILDER_HPP_

class BuilderProduct;

class Builder{
public:
    virtual ~Builder();
    virtual void build_product(void);
    virtual void build_part_I(int) = 0;
    virtual void build_part_II(int) = 0;
    virtual BuilderProduct *get_product(void);
protected:
    Builder();
    BuilderProduct  *m_product = nullptr;
};

class ConcreateBuilderA : public Builder{
public:
    ConcreateBuilderA();
    ~ConcreateBuilderA();
    void build_part_I(int);
    void build_part_II(int);
};

class ConcreateBuilderB : public Builder{
public:
    ConcreateBuilderB();
    ~ConcreateBuilderB();
    void build_part_I(int);
    void build_part_II(int);
};


#endif //_BUILDER_HPP_

