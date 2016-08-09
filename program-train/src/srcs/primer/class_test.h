/*
 * Progarm Name: class_test.h
 * Created Time: 2015-11-13 07:51:43
 * Last modified: 2016-08-09 13:27:29
 */

#ifndef _CLASS_TEST_H_
#define _CLASS_TEST_H_

#include <string>

/* 用struct/class定义类，唯一的差别在于默认访问级别的不同 */
class Sales_item {
public:
    /* 
     * 只有当类没有声明任何构造函数时，编译器才会自动地生成默认构造函数
     * */
	Sales_item();
	~Sales_item();

	/* 定义一个新对象时，并用一个同类型的对象对它进行初始化时，将显式使用复制构造函数
	 * 当将该类型的对象传递给函数或从函数返回该类型的对象时，将隐式使用复制构造函数  */
	Sales_item(const Sales_item &r_si);

	/*get units_sold*/
	unsigned get_units_sold(void) const;
#if 0
	/*change units_sold */ //const 成员函数，只能实现用于读取成员数据，不能对成员数据进行修改
	void change_units_sold(unsigned us) const; // fault define
#endif
	/*get isbn,const成员函数的返回引用也必须是const类型的，否则出错*/
	const std::string &get_isbn(void) const;
	/*const对象只能使用const成员，非const对象可以使用任一个成员，但非const版本更匹配*/
	/*display test func*/
	void display(const char *p_str);
	/*display test func*/
	void display(const char *p_str) const;
	/*change val*/
	void change_val(char v) const;
private:
	std::string isbn;
	unsigned units_sold;
	double revenue;


    /* mutable 数据成员，永远不会是const，即使它是const对象的成员 */
	mutable char val;


	/*static成员数据需要在类外部进行定义*/
	static char static_val;
	/*只有const static的成员-only type int，才可以在类中进行初始化*/
	static const char static_val1 = 10;
    static const char version[];
};

/* Note :
 *
 * 1.类可以定义在头文件中，已知值的const对象和inline函数可以定义在头文件中
 * 2.const对象默认定义它的文件的局部变量，所以把它们定义放在头文件中是合法的
 * 3.如果const变量不是用常量表达式初始化，那么它就不应该在头文件中定义
 * 4.常量对象，以及常量对象的引用或指针都只能调用常量成员函数
 *
 * 5.一般来说，最好在类定义开始或者结束前的位置集中声明友元
 * */

class Base{
public:
    Base(void);
    virtual ~Base(void);
    virtual void on(void);
    void off(void);
};

class Derived : public Base {
public:
    Derived();
    virtual ~Derived();
    virtual void on(void);
    void abc(void);
};

/*class test func*/
extern void class_test(void);

class CB;
class CC;

class CA{
public:
    CA();
    ~CA();
    CA(int a);

    typedef union{
        int a;
        struct{
            char b;
            char c;
        };
    }ttu_u;
    ttu_u   ttu;
    void test(void);
    void on(void);
    void off(void);
    void print_fa(void);
    void change_cb(int a);
    void change_cc(CC *pcc, int c);
    static void printa(void);
private:
    friend class CB;
    static int m_a;
    static int m_fb;
};

class CB{
public:
    CB();
    ~CB();
    void func(int fb);

    typedef CA::ttu_u TTU_U;
    void test(void);
    void print_ma(void);
    void print_mc(void);
private:
    //friend class CA;
    friend void CA::change_cb(int a);
    static int m_ba;
    static int m_bc;
};

class CC{
public:
    CC();
    ~CC();
    void change_cc(int a);
    void print_cc(void);
    void do_once(void);
    void func(const int a, const int b) const;
    void func(const int a, int b);
private:
    friend class CA;
    int cc;
};

#endif //_CLASS_TEST_H_

