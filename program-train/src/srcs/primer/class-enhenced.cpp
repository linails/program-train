/*
 * Progarm Name: class-enhenced.cpp
 * Created Time: 2017-01-05 09:00:05
 * Last modified: 2017-02-16 10:11:45
 * @author: minphone.linails linails@foxmail.com 
 */

#include "class-enhenced.hpp"
#include <iostream>
#include <cassert>
#include "class-def.hpp"

using std::cout;
using std::endl;

ClassEnhenced::ClassEnhenced()
{
}

ClassEnhenced::~ClassEnhenced()
{
}

int  ClassEnhenced::class_enhenced_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->copy_ctrl(); assert(-1 != ret);

    ret = this->private_mem_use(); assert(-1 != ret);

    ret = this->pure_VirtualBase(); assert(-1 != ret);

    return ret;
}

int  ClassEnhenced::copy_ctrl(void)
{
    /*
     * Note : 
     *
     * 只包含类类型或内置类型数据成员、不含指针的类一般可以使用合成操作，复制、赋值或
     * 撤销这样的成员不需要特殊控制
     *
     * !!! 具有指针成员的类一般需要定义自己的复制控制来进行管理这些成员
     *
     *
     * 如果派生类定义了自己的复制构造函数，该复制构造函数一般应显式使用积累复制构造函数初始化对象的基类部分
     * -> class_test.cpp : 651  |  LibraryDrived(const LibraryDrived &ld)
     *    如果没有显式调用，则基类是直接使用默认构造函数初始化，这个时候就没有实现 对ld 中基类的复制
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * 赋值操作符通常与复制构造函数类似，如果派生类定义了自己的赋值操作符，则该操作符必须对基类部分显式赋值
     * -> class_test.cpp : 659  |  LibraryDrived &operator=(const LibraryDrived &rld)
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * 析构函数的工作与 "复制构造函数/赋值操作符" 不同，派生类析构函数不负责撤销基类对象的成员
     *
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * !!! [虚函数必须在基类和派生类中具有同样的形参]
     *
     * !!! 在复制控制成员中，只有析构函数应定义为虚函数，构造函数不能定义为虚函数，构造函数是在对象
     *     完全构造之前运行的，在构造函数运行的时候，对象的动态类型还不完整
     *  1> 析构函数可以定义为虚函数
     *  2> operator= 虽然也可以定义为虚函数，不过不影响派生类中的使用，每个类有自己的赋值操作符，
     *     不定义为虚函数最好 , 赋值操作符有一个与类本身类型相同的形参，这不符合虚函数定义
     *  3> 复制构造函数不可以定义为虚函数
     *
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * {
     *  A> 构造派生类对象时，首先运行基类构造函数初始化对象的基类部分
     *  B> 撤销派生类对象时，首先撤销它的派生类部分，然后再撤销基类
     * }
     *
     * 如果在构造函数或析构函数中调用虚函数，则运行的是为构造函数或析构函数自身类型定义的版本
     *  1> 在派生类的构造函数中运行的虚函数，则是派生类自身定义的虚函数 !!!
     *  2> 在基类的构造函数中运行的虚函数，则是基类自身定义的虚函数     !!!
     * */
    int ret = 0;

    return ret;
}

int  ClassEnhenced::private_mem_use(void)
{
    cout << "---------------------------------------------------------" << endl;
    int ret = 0;

    cout << "private_mem_use ..." << endl;

    PrivateMemUse pmu(100);
    cout << "pmu.get_data() : " << pmu.get_data() << endl;

    OnlyHpp oh(200);
    cout << "oh.get_data() : " << oh.get_data() << endl;

    return ret;
}

int  ClassEnhenced::pure_VirtualBase(void)
{
    int ret = 0;

    pureVirtualBase *pvb;

    VirtualDrived vd;

    pvb = &vd;

    cout << "pvb->func01() : "; pvb->func01();
    cout << "pvb->func02() : "; pvb->func02();
    cout << "pvb->pureVirtualBase::func02() : "; pvb->pureVirtualBase::func02();

    return ret;
}

pureVirtualBase::pureVirtualBase()
{
}

pureVirtualBase::~pureVirtualBase()
{
}

void pureVirtualBase::func02(void)
{
    cout << "func02 (pureVirtualBase) ..." << endl;
}

VirtualDrived::VirtualDrived()
{
}

VirtualDrived::~VirtualDrived()
{
}

void VirtualDrived::func01(void)
{
    cout << "func01 (VirtualDrived) ..." << endl;
}

void VirtualDrived::func02(void)
{
    cout << "func02 (VirtualDrived) ..." << endl;
}

