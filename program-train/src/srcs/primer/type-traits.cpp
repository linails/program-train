/*
 * Progarm Name: type-traits.cpp
 * Created Time: 2016-12-16 22:11:53
 * Last modified: 2017-01-05 21:23:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "type-traits.hpp"
#include "type-traits-def.hpp"
#include <iostream>
#include <type_traits>

using std::cout;
using std::endl;

/* 
 * reference <<代码大全>> 计算圈复杂度方法：
 *  1> 从函数第一行开始，一直往下看程序
 *  2> 一旦遇到以下关键字或者同类的词就加 1
 *      if, while, repeat, for, and, or
 *  3> 向 case 语句中的每一种情况加 1
 * */

/* 
 * 1. type_traits 提供了丰富的编译器计算、查询、判断、转换和选择的帮助类
 *
 * 2. type_traits 的类型选择功能，在一定程度上可以消除冗长的 switch-case 或 if-else 的语句，
 *    降低程序的圈复杂度
 *    且 type_traits 的类型判断功能，在编译期就可以检查出是否是正确的类型，以便能编写出更安全的代码
 *
 * 3. 可变参数模板往往需要和 type_traits 结合起来实现更强大的编译期计算功能，也是程序库开发过程中
 *    经常要用到的
 * */

TypeTraits::TypeTraits()
{
}

TypeTraits::~TypeTraits()
{
}

int  TypeTraits::typetraits_main(int argc, char *argv)
{
    int ret = 0;

    return ret;
}

