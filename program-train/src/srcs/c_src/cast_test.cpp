/*
 * Progarm Name: cast_test.cpp
 * Created Time: 2015-11-22 20:16:36
 * Last modified: 2016-01-03 22:02:34
 * @author: minphone.linails linails@foxmail.com 
 * @version 1.0
 */

#include "cast_test.h"
#include <iostream>
#include <cstdio>

using namespace std;

/*const_cast_test*/
static void const_cast_test(void);

/*static cast test func*/
static void static_cast_test(void);

/*reinterpret_cast_test func*/
static void reinterpret_cast_test(void);

/*cast test function*/
void cast_test(void)
{
	cout<<"cast test function"<<endl;
	const_cast_test();
	static_cast_test();
	reinterpret_cast_test();
	cout<<"---------------------------"<<endl;
}

/*const_cast_test*/
void const_cast_test(void)
{
	//const_cast 是用来进行实现转换表达式的const性质
	//添加或者删除const性质
	/*使用const_cast也总是预示着设计缺陷
	 * 设计合理的系统应不需要使用强制转换抛弃const特性*/
	const char *p = "const char pointer";
	char *pc = const_cast<char*>(p);
	cout<<"p :"<<p<<endl;
	cout<<"pc :"<<pc<<endl;
	cout<<"---------------------------"<<endl;
}

/*static cast test func*/
void static_cast_test(void)
{
	/*编译器隐式执行的任何类型转换，都可以由static_cast显示完成*/
	int a = 10;
	cout<<"a = "<<a<<endl;
	char b = a;
	printf("b = %d\n",b);
	char c = static_cast<char>(a);
	printf("c = %d\n",c);
	double d = 97.3;
	cout<<"d = "<<d<<endl;
	c = d; //隐式进行了转换
	printf("c = %d\n",c);
	c = static_cast<char>(d);
	printf("c = %d\n",c);
	void *p = &d;
	double *dp = static_cast<double*>(p); //这个时候就需要显示地进行转换
	cout<<"*dp = "<<*dp<<endl;
	double *dp1 = (double *)p;
	cout<<"*dp1 = "<<*dp1<<endl;
	cout<<"---------------------------"<<endl;
}

/*reinterpret_cast_test func*/
void reinterpret_cast_test(void)
{
	//reinterpret_cast通常为操作数的位模式提供较低层次的重新解释
	cout<<"---------------------------"<<endl;
}

