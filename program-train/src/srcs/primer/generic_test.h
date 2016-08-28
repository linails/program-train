/*
 * Progarm Name: generic_test.h
 * Created Time: 2016-07-11 11:36:07
 * Last modified: 2016-08-24 09:49:56
 */

#ifndef _GENERIC_TEST_H_
#define _GENERIC_TEST_H_

#include <iostream>
#include <cstdlib>

/* 
 * 函数模板可以用与非模板函数一样的方式声明为 inline
 * 放在模板形参表之后，返回值类型之前，不能放在关键字 template 之前
 * */

/* function template 
 * template 后接模板形参表 */
template <typename T>
int compare(const T &v1, const T &v2)
{
    if(v1 < v2) return -1;
    if(v2 < v1) return  1;
    return 0;
}

template <typename Type> class Queue;

template <typename Type>
class QueueItem{
    friend class Queue<Type>;
    QueueItem(const Type &t):item(t), next(0){}
    Type       item;
    QueueItem *next;
};

/* 
 * 1.同一个模板的声明和定义中，模板形参的名字可以不同
 *
 * 2.与调用函数模板形成对比，使用类模板时，必须为模板形参显示指定实参:
 *   Queue<in> qi;
 *   Queue<string> qs;
 *   Queue<vector<double> > qc;
 * */
template <typename Type> 
class Queue{
public:
    Queue(): head(0), tail(0) { }
    Queue(const Queue &Q): head(0), tail(0) { copy_elems(Q); }
    Queue& operator=(const Queue&);
    ~Queue() { destroy(); }
    Type &front(void) { return head->item; }
    void push(const Type &);
    void pop(void);
    bool empty(void) const { return head == 0; }
private:
    void destroy(void);
    void copy_elems(const Queue&);
private:
    QueueItem<Type> *head;
    QueueItem<Type> *tail;
};

template <typename Type>
void Queue<Type>::destroy(void)
{
    while( !empty() ) pop();
}

template <typename Type>
void Queue<Type>::pop(void)
{
    QueueItem<Type> *p = head;
    head = head->next;
    delete p;
}

/* 
 * int x[42];
 *
 * double y[10];
 *
 * array_init(x); // instantiates array_init(int(&)[42]);
 * array_init(y); // instantiates array_init(double(&)[10]);
 *
 * 对模板的非类型形参而言，求值结果相同的表达式将认为是等价的
 * */
template <typename T, size_t N>
void array_init(T (&parm)[N])
{
    for(size_t i = 0; i < N; ++i){
        parm[i] = 0;
    }
}

template <typename T>
struct TestClass{
    TestClass(){};
    virtual void dotest01(T const &d){};
    virtual ~TestClass(){};
#if 0
    /* error : templates may not be 'virtual' 
     * member function templates can't be virtual */
    template<typename T1>
    virtual void dotest02(T1 const &d){};
#endif
};


/* 
 * 总结：
 * 
 * 1. 编写模板代码时，对实参类型的要求尽可能少是很有益的
 *    两个重要原则
 *    1)模板的形参是 const 引用
 *    2)函数体中的测试只用 < 比较
 * 2. 一般而言，不会转换实参以匹配已有的实例化，相反，会产生新的实例
 * 3. 编译器只会执行两种转换：
 *    1)const 转换：接受 const 引用或 const 指针的函数可以分别用非 const 对象的引用或指针来调用，无需产生新的实例化
 *    2)数组或函数到指针的转换：如果模板形参不是引用类型，则对数组或函数类型的实参应用常规指针转换
 *
 * 4. 在类模板中可以出现三种友元声明，每一种都声明了与一个或多个实体的友元关系
 *    1)普通非模板类或函数的友元声明，将友元关系授予明确指定的类或函数
 *    2)类模板或函数模板的友元声明，授予对友元所有实例的访问权
 *    3)只授予对类模板或函数模板的特定实例的访问权的友元声明
 * 
 * 5. 任意类（模板或非模板）可以拥有本身为类模板或函数模板的成员，这种成员称为成员模板，
 *    成员模板不能为虚
 * 6. 当成员模板是类模板的成员时，它的定义必须包含类模板形参以及自己的模板形参
 * 7. 部分特化的模板形参表只列出未知模板实参的那些形参
 * */

#include "generic_test.cpp"

#endif //_GENERIC_TEST_H_

