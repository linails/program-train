/*
 * Progarm Name: class_test.cpp
 * Created Time: 2015-11-13 07:51:55
 * Last modified: 2017-09-21 17:06:38
 */

#include "class_test.h"
#include <iostream>
#include <string>
#include <cstdio>
#include "other.h"
#include <cstdlib>
#include <cstring>

using namespace std;

/*class test func*/
void class_test(void)
{
    cout << "class test start ..." << endl;
    {
        Sales_item si;
        cout << "units_sold = " << si.get_units_sold() << endl;
        cout << "sales_item 's = " << si.get_isbn() << endl;

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

        od.abc();
        ((Derived *)ptr)->abc();

    }
    cout << "---------------------------" << endl;
    {

        cout << "size of Base :" << sizeof(Base) << endl;

        //void *p = ((Base *)0)->on;
        //void *p = csi.display;
        printf("addr Base::on : 0x%x\n",&Base::on);
        printf("addr Base::off : 0x%x\n",&Base::off);

    }
    #if 0
    cout << "---------------------------" << endl;
    {
        /* 
         * 这种做法是错误的：
         *  定义基类，然后强转为 Derived 类型，进行赋值 Derived 成员，是错误的，因为就没有 Derived 空间使用
         * */
        Base baseArray[10];

        Derived *p = (Derived *)&baseArray[0];
        p->show();

        p->m_derived_b = 33;
        p->show();
    }
    #endif
    cout << "---------------------------" << endl;
    {
        CA  ca,ca1;
        ca.test();
        ca1.test();

        CB  cb;
        cb.test();
        cb.func(12);

        ca.print_fa();
        ca.change_cb(123);

        cb.print_ma();

        CC cc;
        cc.change_cc(222);

        cb.print_mc();

        ca.change_cc(&cc, 12);
        cc.print_cc();

        cc.do_once();
    }
    cout << "---------------------------" << endl;
    {
        void (* pf)(void);

        CA  ca(11);
        pf = &ca.printa;

        do_pcb(pf);
    }
    cout << "---------------------------" << endl;
    {
        void (* pf)(void);

        CA  ca(11);
        pf = CA::printa;

        do_pcb(pf);
    }
    cout << "---------------------------" << endl;
    {
        CC cc;

        const int a = 10;
        const int b = 12;
        int c = 13;

        cc.func(a, b);
        cc.func(a, c);

        const CC cc2;

        const int a2 = 22;
        const int b2 = 33;
        int c2 = 44;
        cc2.func(a2, b2);
        cc2.func(a2, c2);
    }
    cout << "---------------------------" << endl;
    {
        void copy_control(void);
        copy_control();
    }
    cout << "---------------------------" << endl;
    {

        void library_test(void);
        library_test();
    }
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
	cout << p_str << endl;
    printf("static val:%d\n",static_val);
    printf("static val1:%d\n",static_val1);
    cout << "const version" << endl;
}

/*display test func*/
void Sales_item::display(const char *p_str)
{
    cout << p_str << endl;
    printf("static val:%d\n",static_val);
    printf("static val1:%d\n",static_val1);
    cout << "non const version" << endl;
}

/*change val*/
void Sales_item::change_val(char v) const
{
    /*const函数是可以修改mutable类型的数据成员*/
    val = v;
}

Base::Base(void)
{
    this->m_base_a = 11;
    cout << "base ..." << endl;
}

Base::~Base(void)
{
    cout << "~base ..." << endl;
}

void Base::on(void)
{
    cout << "base on ..." << endl;
    printf("base::on this addr : 0x%x\n",this);
}

void Base::off(void)
{
    cout << "base off ..." << endl;
}

void Base::show(void)
{
    cout << "this->m_base_a : " << this->m_base_a << endl;
}

Derived::Derived()
{
    this->m_derived_a = 22;
    cout << "derived ..." << endl;
}

Derived::~Derived()
{
    cout << "~derived ..." << endl;
}

void Derived::on()
{
    cout << "derived on ..." << endl;
    printf("derived::on this addr : 0x%x\n",this);
}

void Derived::abc(void)
{
    cout << "abc ..." << endl;
}

void Derived::show(void)
{
    cout << "this->m_derived_a : " << this->m_derived_a << endl;
    cout << "this->m_derived_b : " << this->m_derived_b << endl;
}

int CA::m_a;
int CA::m_fb;

CA::CA()
{
}

CA::~CA()
{
}

CA::CA(int a)
{
    m_a = a;
}

void CA::test(void)
{
    cout << "..............CA::TEST .............." << endl;
    this->ttu.a = 10;
    printf("this->ttu.a = %d\n",this->ttu.a);
    printf("addr this : 0x%x\n",this);

    this->ttu.b = 10;
    this->ttu.c = 10;

    printf("this->ttu.a = %.4x\n",this->ttu.a);
    printf("this->ttu.b = %d\n",this->ttu.b);
    printf("this->ttu.b = %.2x\n",this->ttu.b);
    printf("this->ttu.c = %d\n",this->ttu.c);
    printf("this->ttu.c = %.2x\n",this->ttu.c);


    void (CA::* pf[])(void) ={
         &CA::on,
         &CA::off
    };
    (this->*pf[0])();
    (this->*pf[1])();


    cout << "..............CA::TEST END..........." << endl;
}

void CA::on(void)
{
    cout << "........CA::on........" << endl;
}

void CA::off(void)
{
    cout << "........CA::off........" << endl;
}

void CA::change_cc(CC *pcc, int c)
{
    pcc->cc = c;
}

void CA::printa(void)
{
    cout << "........CA::printa........" << endl;

    cout << "static m_a : " << m_a << endl;

    cout << ".........................." << endl;
}

void CA::print_fa(void)
{
    cout << "func : " << __FUNCTION__ << endl;
    cout << "m_fb = " << m_fb << endl;
}

int CB::m_ba = 0;
int CB::m_bc = 0;

void CA::change_cb(int a)
{
    CB::m_ba = a;
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

void CB::func(int fb)
{
    cout << "..............friend func .............." << endl;
    CA::m_fb = fb;
    cout << "CA::m_fb = " << CA::m_fb << endl;
}

void CB::print_ma(void)
{
    cout << "CB::m_ba = " << m_ba << endl;
}

void CB::print_mc(void)
{
    cout << "CB::m_bc = " << m_bc << endl;
}

CC::CC()
{
}

CC::~CC()
{
}

void CC::change_cc(int a)
{
}

void CC::print_cc(void)
{
    cout << "CC:cc = " << this->cc << endl;
}

void CC::do_once(void)
{
    CA ca;

    ca.change_cc(this, 8888);

    this->print_cc();
}

void CC::func(const int a, const int b) const
{
    cout << "called func(const int, const int)" << endl;
    cout << "a = " << a << " b = " << b << endl;
}

void CC::func(const int a, int b)
{
    cout << "called func(const int, int)" << endl;
    cout << "a = " << a << " b = " << b << endl;
}

//-----------------------------------------------------------------------------

class CopyCtrl01{
public:
    CopyCtrl01():b(20){}
    ~CopyCtrl01(){}
private:
    static const int a;
    const int b;
};

const int CopyCtrl01::a = 10;

class CopyCtrl02{
public:
    CopyCtrl02(char *buf)
    {   
        p = new char[strlen(buf)+1];
        memcpy(p, buf, strlen(buf)+1);
    }
    CopyCtrl02(const CopyCtrl02 &);
    CopyCtrl02 &operator=(const CopyCtrl02 &);
    ~CopyCtrl02(){ delete [] p; cout << "delete ..." << endl;};
    int  write(char data, int index);
    int  read(char &data, int index);
    void print(void);
private:
    char *p;
};

CopyCtrl02::CopyCtrl02(const CopyCtrl02 &cc)
{
    this->p = new char [strlen(cc.p)+1];
    memcpy(this->p, cc.p, strlen(cc.p)+1);
    cout << "copy done !" << endl;
}

CopyCtrl02 &CopyCtrl02::operator=(const CopyCtrl02 &cc)
{
    cout << "operator = done !" << endl;
    /* 
     *  1. 检查自赋值
     *  2. 释放原有的内存资源
     *  3. 分配新的内存资源，并复制内容
     *  4. 返回本对象的引用
     * */
    if(this == &cc) return *this;

    delete [] p;
    this->p = new char[strlen(cc.p)+1];
    memcpy(this->p, cc.p, strlen(cc.p)+1);

    return *this;
}

int  CopyCtrl02::write(char data, int index)
{
    this->p[index] = data;
    return 0;
}

int  CopyCtrl02::read(char &data, int index)
{
    data = this->p[index];
    return 0;
}

void CopyCtrl02::print(void)
{
    cout << "content : " << this->p << endl;
}

void copy_control(void)
{
    /* 
     * 如果不主动编写拷贝构造函数和赋值函数，
     * 编译器将以"位拷贝"的方式自动生成缺省的函数
     * 如果类中含有指针变量，则就隐含了错误
     * */
    cout << "----------- copy control -----------" << endl;
    {
        CopyCtrl01  cc1;

        CopyCtrl01  cc2;

        /* 1.如果类的某个成员的拷贝赋值运算符是删除的或不可访问的，
         * 2.或是类有一个const的或引用成员
         *
         * => 则类的 {合成拷贝赋值运算符} 被定义为删除的 */
        //cc2 = cc1;
        
        /* 
         * 1.拷贝构造函数是在对象被创建时调用
         * 2.赋值函数只能被已经存在了的对象调用
         * eg. 
         *   A a = aa; 拷贝构造函数
         *   A b ;
         *   b = a;  赋值函数
         * */
    }
    cout << "---------------------------" << endl;
    {
        /* 赋值操作运算符函数的定义分4步：
         *  1. 检查自赋值
         *  2. 释放原有的内存资源
         *  3. 分配新的内存资源，并复制内容
         *  4. 返回本对象的引用
         * */
        #if 0
        String & String::operator=(const String &other)
        {
            /* 1. 检查自赋值 */
            if(this == &other) return *this;

            /* 2. 释放原有的内存资源 */
            delete [] m_data;

            /* 3. 分配新的内存资源，并复制内容 */
            int length = strlen(other.m_data);
            m_data = new char[length+1];
            strcpy(m_data, other.m_data);

            /* 4. 返回本对象的引用 */
            return *this;
        }
        #endif

        char data[] = "nice to";
        cout << "data[] : " << data << endl;

        char buf[] = "hello world";
        cout << "buf[] : " << buf << endl;

        CopyCtrl02  cc1(buf);
        CopyCtrl02  cc2 = cc1;

        CopyCtrl02  cc3(data);

        cc3.print();
        cc3 = cc1;
        cc3.print();
    }
    cout << "---------------------------" << endl;
}

//-----------------------------------------------------------------------------

void library_test(void)
{
    cout << "LibraryBase ..." << endl;

    /* 只有通过引用或指针进行函数调用，才可以使用动态绑定 */
    LibraryBase *pl;

    LibraryBase lb("11111");
    LibraryDrived ld("22222");

    pl = &lb;
    double net_price = pl->net_price(10); cout << "net_price = " << net_price << endl;
    print_total(lb, "lb", 10);
    print_total(*pl, "*pl", 10);

    pl = &ld;
    net_price = pl->net_price(10); cout << "net_price = " << net_price << endl;
    double ori_price = ((LibraryDrived*)pl)->ori_price(); cout << "ori_price = " << ori_price << endl;
    pl->salebook();
    print_total(ld, "ld", 10);
    print_total(*pl, "*pl", 10);
    cout << endl;

    /* 派生类虚函数调用基类版本时，必须显式使用作用域操作符 
     *
     * 即 “覆盖虚函数机制” :
     *  在某些情况下，希望覆盖虚函数机制并强制函数调用使用虚函数的特定版本，
     *  这个时候可以使用作用域操作符
     * */
    net_price = pl->LibraryBase::net_price(10); cout << "net_price : " << net_price << endl;


    /* 每个派生类对象包含一个基类部分，这意味着可以像使用基类对象一样在派生类对象上执行操作
     *
     * 因为每个派生类对象也是基类对象，所以存在从派生类型引用到基类类型引用的自动转换
     *
     * 一般可以使用派生类型对象对基类对象进行赋值或初始化
     * */

    /* 对基类对象进行初始化或赋值，实际上是在调用函数：初始化时调用构造函数，赋值时调用赋值操作符 */
}

#if 1
void callback(void *fn)
{
    typedef int (*PFN)(void);
    cout << "callback : " << ((PFN)fn)() << endl;
}
#endif

LibraryBase::LibraryBase(std::string risbn)
    :isbn(risbn)
    ,price(10)
{
    printf("addr : get_price : 0x%x\n", &LibraryBase::get_price);
#if 0
    callback((void *)&LibraryBase::get_price);
    cout << " wrong !!!" << endl;
#endif
}

std::string LibraryBase::book() const
{
    return this->isbn;
}

int LibraryBase::get_price(void)
{
    return this->price;
}

void LibraryBase::salebook(void) const
{
    cout << "LibraryBase::salebook ..." << endl;
}

double LibraryBase::net_price(int n, const char *s) const
{
    cout << "s = " << s << endl;
    return n * this->price;
}

void LibraryBase::library(void)
{
    cout << "static library ... " << endl;
}

LibraryBase::~LibraryBase()
{
    cout << "~LibraryBase : " << this->isbn << endl;
}

/* 
 * 派生类一般会重定义所继承的虚函数，
 * 如果派生类没有重定义某个虚函数，则使用基类中定义的版本
 * */
LibraryDrived::LibraryDrived(std::string risbn)
    :LibraryBase(risbn)
    ,disbn(risbn)
    ,price(20)
{
    /* 派生类的构造函数受继承关系的影响，每个派生类构造函数除了初始化自己的
     * 数据成员之外，还要初始化基类 */
}

LibraryDrived::LibraryDrived(const LibraryDrived &ld)
    :LibraryBase(ld)  /* 转换为对基类部分的引用，并调用基类复制构造函数 */
{
    cout << "LibraryDrived::LibraryDrived(const LibraryDrived &ld) !" << endl;
}

LibraryDrived &LibraryDrived::operator=(const LibraryDrived &rld)
{
    if(this != &rld){
        LibraryBase::operator=(rld);
        cout << "LibraryDrived::operator= !" << endl;
        //...
    }
    return *this;
}

/* virtual 的目的是启动动态绑定 ，virtual保留字只能出现在类内 
 *
 * 虚函数 与 默认实参：虚函数是动态绑定，而默认实参是静态绑定，
 *  也就是指针是哪种类型，就调用该类型对应的类中的默认实参，
 *  因此 LibraryBase *pl; 中 pl 是基类，因此虚函数的默认实参均是基类中的实参，与实际指针指向是否是派生类无关*/
double LibraryDrived::net_price(int n, const char *s) const 
{
    cout << "s = " << s << endl;
    return n * this->price;
}

/* 类可以访问其基类的 public 和 protected 成员，就好像那些成员是派生类自己的成员一样 */
double LibraryDrived::ori_price(void) const
{
    //return this->price;
    //return LibraryBase::price;
    return this->LibraryBase::price;
}

LibraryDrived::~LibraryDrived()
{
    /* 派生类析构函数不负责撤销基类对象的成员 
     *
     * 每个析构函数只负责清除自己的成员
     *
     * 如果析构函数是虚函数，那么通过指针调用时，运行哪个析构函数将因指针所指对象类型的不同而不同
     * */
}

void print_total(const LibraryBase &lb, const char *str,  int n)
{
    cout << "...para : " << str << endl;
    cout << "...lb.price : " << lb.price << endl;
    cout << "...print_total : " << lb.price * n << endl;
    cout << "...net_price : " << lb.net_price(n) << endl;
    cout << endl;
}




