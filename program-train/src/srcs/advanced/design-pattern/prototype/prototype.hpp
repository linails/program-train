/*
 * Progarm Name: prototype.hpp
 * Created Time: 2017-11-14 22:54:56
 * Last modified: 2017-11-14 23:10:23
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _PROTOTYPE_HPP_
#define _PROTOTYPE_HPP_

/* 
 * ProtoType 模式用来复制原型的方式来获得创建对象的功能
 * */

class ProtoType{
public:
    virtual ~ProtoType();
    virtual ProtoType *Clone() const = 0;
protected:
    ProtoType();
};

class ConcreteProtoType : public ProtoType{
public:
    ConcreteProtoType();
    ~ConcreteProtoType();
    ConcreteProtoType(const ConcreteProtoType &cpt);
    ProtoType *Clone(void) const;
private:
};

#endif //_PROTOTYPE_HPP_

