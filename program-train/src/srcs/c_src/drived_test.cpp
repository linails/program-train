/*
 * Progarm Name: drived_test.cpp
 * Created Time: 2015-12-05 22:57:31
 * Last modified: 2016-07-28 17:46:35
 */

#include "drived_test.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

ObjBase::ObjBase()
    :var_base(20)
{
    cout << "ObjBase contructor ..." << endl;
}

ObjBase::~ObjBase()
{
    cout << "in base -> " ;
    this->display();
    cout << "ObjBase destructor ..." << endl;
}

void ObjBase::func01(void)
{
    cout << "func01 ..." << endl;
}

void ObjBase::func02(void)
{
    cout << "ObjBase --> func02 ..." << endl;
}

void ObjBase::func03(void)
{
    cout << "ObjBase --> func03 ..." << endl;
}

void ObjBase::display(void)
{
    cout << "ObjBase --> display" << endl;
}

ObjDrived::ObjDrived()
    :flag(21)
{
    cout << "ObjDrived constructor ..." << endl;
}

ObjDrived::~ObjDrived()
{
    cout << "in drived -> " ;
    this->display();
    cout << "ObjDrived destructor ..." << endl;
}

void ObjDrived::func02(void)
{
    cout << "ObjDrived --> func02" << "-flag = " << flag << endl;
}

void ObjDrived::display(void)
{
    cout << "ObjDrived --> var_base : " << this->var_base << endl;
    cout << "ObjDrived --> display" << endl;
}

void display_base(ObjBase &r_base)
{
    r_base.display();
}

void display_drived(ObjDrived &r_drived)
{
    r_drived.display();
}

//---------------------------------------------------------

void drived_test(void)
{
    cout << "drived test ..." << endl;
    ObjBase base;
    ObjDrived drived;
    ObjBase *pbase = 0;
    ObjDrived *pdrived = 0;

    cout << "-----------------" << endl;
    pbase = &base;
    pbase->display();
    pbase->func01();
    pbase->func02();

    pbase = &drived;
    pbase->display();
    pbase->func01();
    pbase->func02(); //非虚函数：执行ObjBase --> func02();决定于pbase定义指针的类型

    cout << "-----------------" << endl;
    pdrived = (ObjDrived *)&base;//这种做法，容易发生访问派生类函数，可实际是个base
    pdrived->display(); //虚函数，执行ObjBase --> display()
    pdrived->func01();
    pdrived->func02(); //非虚函数；执行ObjDrived --> func02();决定于pdrive定义指针的类型
                       //ObjDrived 中的flag为未定义，因为指针所指类型为ObjBase
                       //访问派生类型为非法访问

    pdrived = &drived;
    pdrived->display(); //虚函数，执行ObjBase --> display()
    pdrived->func01();
    pdrived->func02(); //非虚函数；执行ObjDrived --> func02();决定于pdrive定义指针的类型
    cout << "-----------------" << endl;
    display_base(base);
    display_base(drived);
    display_drived((ObjDrived &)base);
    display_drived(drived);
    

    cout << "-----------------" << endl;
    ObjBase *p = new ObjBase;
    delete p;
    p = new ObjDrived;
    delete p;
    cout << "-----------------" << endl;
}

