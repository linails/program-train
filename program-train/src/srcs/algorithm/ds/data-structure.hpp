/*
 * Progarm Name: data-structure.hpp
 * Created Time: 2016-12-30 09:11:35
 * Last modified: 2017-01-09 14:40:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DATA_STRUCTURE_HPP_
#define _DATA_STRUCTURE_HPP_

class DataStructure{
public:
    DataStructure();
    ~DataStructure();
    int  datastruct_main(int argc, char **argv);
private:
    int  linearlist(int argc, char **argv);
    int  stack(void);
    int  queue(int argc, char **argv);
    int  mstring(int argc, char **argv);
    int  tree(int argc, char **argv);
private:
};

/* 
 *  时间复杂度度量
 *  算法的运行时间涉及到加、减、乘、除、转移、存、取等基本运算
 *
 *  [各种语句给出的程序步数]
 *      1> "注释"     : 程序步数为 0 ，因为是非执行语句
 *
 *      2> "声明语句" : 同上
 *
 *      3> "表达式"   : 如果表达式中不包含函数调用，则程序步数为 1，
 *                      如果包含函数调用，总的程序步数要包括分配给函数调用的程序步数
 *
 *      4> "赋值语句" : <val>=<exp> 的程序步数与 "表达式" 的程序步数相同
 *                      如果语句中的变量是 数组/字符串，则程序步数 = 变量的体积 + 表达式程序步数
 *
 *      5> "循环语句" : 若仅考虑循环控制部分，则有3种形式
 *                      a) while<exp> do ...
 *                      b) do ... while<exp>
 *                      c) for(<ini>; <exp1>; <exp2>) ...
 *                      while和do语句，控制部分一次执行的步数 = <exp> 的程序步数
 *                      for 语句：I> 第一次执行的步数 = <ini> + <exp1>
 *                                II>第二次执行的步数 = <exp1> + <exp2>
 *
 *      6> "switch语句"  :
 *              switch(<exp1>){
 *                  case condition: <exp2>
 *                  ...
 *                  default : <exp>
 *              }
 *              switch(<exp1>) 的程序步数 = <exp1>
 *              执行一个条件的程序步数 = <exp2> + 前面所有条件计算的程序步数
 *
 *      7> "if-then语句" :
 *              if(<exp>) <exp1>;
 *              else <exp2>;
 *
 *      8> "函数执行语句/函数调用语句" :
 *              函数调用语句的步数为 0,其时间开销计入函数执行语句
 *              函数执行语句的程序步数一般为 1
 *              I> 当函数执行语句中包含有传值参数且传值参数的体积与实例特征有关时，
 *                 执行函数调用的程序步数 = 这些值参的体积之和
 *              II>如果函数的递归调用，那么还需要考虑在函数中的局部变量
 *                 如果局部变量的体积依赖于实例特性，需要把这个体积加到程序步数中
 *
 *      9> "动态存储管理语句" :
 *              new object;
 *              delete object;
 *              sizeof(object)
 *              每一个语句的程序步数都是 1, new和delete还分别隐式地调用了对象的构造函数和析构函数，
 *              这时可以用类似于分析函数调用语句的方式来计算其程序步数
 *
 *      A> "转移语句" :
 *              continue, break, goto, return 和 return<exp>
 *              它们的程序步数一般为1，return<exp>需要计算 exp
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *  算法的渐进分析(asymptotic algorithm analysis)简称算法分析
 *      算法分析直接与它所求解的问题的规模 n 有关，因此通常将问题规模作为分析的参数，
 *      求算法的时间和空间开销与问题规模 n 的关系
 *
 *      c < ln(n)/ln(2) < n < nln(n)/ln(2) < n^2 < n^3 < 2^n < 3^n < n!
 *
 *      这里 ln(n)/ln(2) = log2N
 *
 *      如果一个算法的时间复杂度取到 c, ln(n)/ln(2), n, nln(n)/ln(2) 那么它的时间效率是比较高的
 *
 *      如果存在多层的嵌套循环，关键操作在最内层循环中
 *
 *  [最好、最坏、平均情况]
 *      大O表示法描述的是算法的上限
 *      Ω表示法是描述算法的最小时间代价
 * */

#endif //_DATA_STRUCTURE_HPP_

