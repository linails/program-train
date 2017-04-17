/*
 * Progarm Name: class-enhenced.hpp
 * Created Time: 2017-01-05 09:00:11
 * Last modified: 2017-02-16 10:09:03
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CLASS_ENHENCED_HPP_
#define _CLASS_ENHENCED_HPP_

#include <string>
#include <vector>

using std::string;
using std::vector;

class ClassEnhenced{
public:
    ClassEnhenced();
    ~ClassEnhenced();
    int  class_enhenced_main(int argc, char **argv);
private:
    int  copy_ctrl(void);
    int  private_mem_use(void);
    int  pure_VirtualBase(void);
};

/* 
 * 这个类和 class-def.hpp 中的 OnlyHpp 进行对比，如果在头文件中有其他类定义在 .cpp 中，
 * 则如下这个类的实现要么定义在类内部，要么就定义在 .cpp 文件中
 *
 * OnlyHpp类中的实现都定义在头文件中，则可以把定义放到类外面进行实现
 * */
class PrivateMemUse{
public:
    PrivateMemUse(int data = 0):m_data(data){}
    PrivateMemUse(const PrivateMemUse &pmu){ 
        /* !!! */
        this->m_data = pmu.m_data; 
    }
    ~PrivateMemUse(){}
    int get_data(void) const{ return this->m_data; }
private:
    int m_data;
};

class pureVirtualBase{
public:
    pureVirtualBase();
    virtual ~pureVirtualBase();
    virtual void func01(void) = 0;
    virtual void func02(void);
private:
};

class VirtualDrived : public pureVirtualBase{
public:
    VirtualDrived();
    virtual ~VirtualDrived();
    virtual void func01(void);
    virtual void func02(void);
private:
};

#endif //_CLASS_ENHENCED_HPP_

