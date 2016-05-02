/*
 * Progarm Name: class_test.cpp
 * Created Time: 2015-11-13 07:51:55
 * Last modified: 2016-05-02 13:58:56
 * @author: minphone.linails linails@foxmail.com 
 * @version 1.0
 */

#include "class_test.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

/*class test func*/
void class_test(void)
{
	cout<<"class test start ..."<<endl;
	Sales_item si;
	cout<<"units_sold = "<<si.get_units_sold()<<endl;
	cout<<"sales_item 's = "<<si.get_isbn()<<endl;

	/*此为基于const的重载*/
	/*const对象只能使用const成员，非const对象可以使用任一个成员，但非const版本更匹配*/
	si.display("010203");
	const Sales_item csi;
	csi.display("040506");

	si.change_val(10);

    Base *ptr = 0;
    Derived od;
    ptr = &od;
    ptr->on();
	cout<<"---------------------------"<<endl;

    cout << "size of Base :" << sizeof(Base) << endl;

    //void *p = ((Base *)0)->on;
    //void *p = csi.display;
    printf("addr Base::on : 0x%x\n",&Base::on);
    printf("addr Base::off : 0x%x\n",&Base::off);

	cout<<"---------------------------"<<endl;
    CA  ca;
    ca.test();

    CB  cb;
    cb.test();
	cout<<"---------------------------"<<endl;
}

//-----------------------------------------------------------------------------

/*static数据成员必须在类定义体的外部定义，不像普通数据成员，static成员
 * 不是通过类构造函数进行初始化，而是应该在定义时进行初始化
 * **static 符号，不能在定义处出现*/
char Sales_item::static_val;
const char Sales_item::static_val1;
/*staitc 符号在这里不出现*/
const char Sales_item::version[] = "v.0.0.1";

/*default constructor,并使用默认初始化列表
 * 构造函数和析构函数，不建议使用inline*/
//inline Sales_item::Sales_item(void)
Sales_item::Sales_item(void)
    : units_sold(10)
    , isbn("hello isbn")
    ,revenue(0.0)
{
}

/*default destructor*/
//inline Sales_item::~Sales_item(void)
Sales_item::~Sales_item(void)
{
}

/*get units_sold*/
unsigned Sales_item::get_units_sold(void) const
{
	return units_sold;
}

#if 0
/*change units_sold*/
void Sales_item::change_units_sold(unsigned us) const
{
    /*const 成员函数不能修改成员数据*/
	units_sold = us;
}
#endif

/*get isbn*/
const std::string &Sales_item::get_isbn(void) const
{
	return isbn;
}

/*display test func*/
void Sales_item::display(const char *p_str) const
{
	cout<<p_str<<endl;
	printf("static val:%d\n",static_val);
	printf("static val1:%d\n",static_val1);
	cout<<"const version"<<endl;
}

/*display test func*/
void Sales_item::display(const char *p_str)
{
	cout<<p_str<<endl;
	printf("static val:%d\n",static_val);
	printf("static val1:%d\n",static_val1);
	cout<<"non const version"<<endl;
}

/*change val*/
void Sales_item::change_val(char v) const
{
	/*const函数是可以修改mutable类型的数据成员*/
	val = v;
}

Base::Base(void)
{
    cout << "base ..." << endl;
}

Base::~Base(void)
{
    cout << "~base ..." << endl;
}

void Base::on(void)
{
    cout << "base on ..." << endl;
}

void Base::off(void)
{
    cout << "base off ..." << endl;
}

Derived::Derived()
{
    cout << "derived ..." << endl;
}

Derived::~Derived()
{
    cout << "~derived ..." << endl;
}

void Derived::on()
{
    cout << "derived on ..." << endl;
}


CA::CA()
{
}

CA::~CA()
{
}

void CA::test(void)
{
    cout << "..............CA::TEST .............." << endl;
    this->ttu.a = 10;
    printf("this->ttu.a = %d\n",this->ttu.a);

    this->ttu.b = 10;
    this->ttu.c = 10;

    printf("this->ttu.a = %.4x\n",this->ttu.a);
    printf("this->ttu.b = %d\n",this->ttu.b);
    printf("this->ttu.b = %.2x\n",this->ttu.b);
    printf("this->ttu.c = %d\n",this->ttu.c);
    printf("this->ttu.c = %.2x\n",this->ttu.c);
    cout << "..............CA::TEST END..........." << endl;
}

CB::CB()
{
}

CB::~CB()
{
}

void CB::test(void)
{
    cout << "..............CB::TEST .............." << endl;
    TTU_U   ttu;
    ttu.b = 10;
    ttu.c = 10;
    printf("ttu.b = %d\n",ttu.b);
    printf("ttu.c = %d\n",ttu.c);
    cout << "..............CB::TEST END..........." << endl;
}


