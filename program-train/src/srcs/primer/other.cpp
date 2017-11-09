/*
 * Progarm Name: other.cpp
 * Created Time: 2016-03-11 15:16:33
 * Last modified: 2017-11-09 14:12:36
 * @author: minphone.linails linails@foxmail.com 
 */

#include "other.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include "class_test.h"
#include <type_traits>
#include <algorithm>
#include <tuple>
#include <functional>
#include <typeinfo>
#include <cassert>

using namespace std;

struct A{
    int i;
    int *p;
};

A a;

typedef vector<unsigned char> UCvec_t;

static void struct_test(void);

class AAA{};
class BBB : AAA{};
class CCC{};

/*other test*/
void other_test(void)
{
    cout <<"-----------------------" << endl;
    {
        cout << "other test \n";

        cout << "sizeof(A) :" << sizeof(A) << endl;
        cout << "sizeof(int):" << sizeof(int) << endl;
        cout << "sizeof(int *) :" << sizeof(int *) << endl;

        int *p = &a.i;
        for(int i=0; i<4; i++){
            printf("p[%d] = %x\n",i,&p[i]);
            p[i] = i;
        }
    }
    cout <<"-----------------------" << endl;
    {
        unsigned int a = 0xfffffff7;
        unsigned char i = (unsigned char)a;
        char *b = (char *)&a;
        
        /*两个b输出都是0xffff fff7，
         * 指针的转换仅仅影响的是指针的寻址*/
        printf("0x%08x, 0x%08x\n",i,*b);
        printf("0x%08x, 0x%08x\n",i,*(char*)b);
        void display(char *ptr);
        display(b);

        char array[5] = {0x01,0x02,0x03,0x04,0x05};
        char *pt = array;
        b = pt;
        printf("0x%08x, 0x%08x\n",i,*b);
    }
    cout <<"-----------------------" << endl;
    {

        float f = 1.0f;
        int *pfi = (int *)&f;
        int &rfi = (int &)f;
        cout << "sizeof (f):" << sizeof(f) << endl;
        cout << "(int)f " << (int)f << endl;
        cout << "&f " << &f << endl;
        cout << "(int&)f "<< (int&)f << endl;
        cout << "rfi " << rfi << endl;
        cout << "*(int *)&f " << *(int *)&f << endl; 
        cout << "*pfi = " << *pfi << endl;

    }
    cout << "----------------------------" << endl;
    {
        typedef unsigned char uint8;

        uint8 a = 0x01;
        uint8 b = 0x02;

        printf("uint8 a = 0x%.2x\n",a);
        printf("uint8 b = 0x%.2x\n",b);

        uint8 *p = &a;
        printf("uint8 *p = 0x%.2x\n",*p);

        uint8 &c = a;
        printf("uint8 c = 0x%.2x\n",c);


        typedef vector<unsigned char> uvec_t;
#if 1
        uvec_t ua;;
        uvec_t &ub = ua;
        ua.push_back(0x01);
        ua.push_back(0x02);
        cout << "ub size : " << ub.size() << endl;

        auto iter = ub.begin();
        printf("ub[0] = 0x%.2x\n",*iter);
        printf("*iter = ub.begin = 0x%.2x\n",*iter);

        const uvec_t &uc = ua;
        cout << "uc size : " << uc.size() << endl;
#endif
    }
    cout << "----------------------------" << endl;
    {
        void func0(const UCvec_t &ua);
        UCvec_t ua;;
        UCvec_t &ub = ua;
        ua.push_back(0x01);
        ua.push_back(0x02);
        func0(ub);
    }
    cout << "----------------------------" << endl;
    {
        struct_test();
    }
    cout << "----------------------------" << endl;
    {
        void auto_decltype_test(void);
        auto_decltype_test();
    }
    cout << "----------------------------" << endl;
    {
        cout << "range-based for" << endl;
        vector<int> arr = {1 , 2 , 3 , 4 , 5};

        for(auto iter = arr.begin();
                 iter!= arr.end(); iter++){
            cout << "*iter = " << *iter << endl;
        }

        /* 基于范围的for循环 
         * n 推导为 arr中元素的类型*/
        {
            /* 这两种是只读方式 */
            for(auto n : arr){
                cout << "n = " << n << endl;
            }
            for(int n : arr){
                cout << "n = " << n << endl;
            }
        }
        cout << endl;
        {
            /* 1.auto &
             * 2.const auto &*/
            for(auto &n : arr) n++;
            for(auto n : arr){
                cout << "n = " << n << endl;
            }
        }
    }
    cout << "----------------------------" << endl;
    {
        map<string,int> mm = {
            {"1", 1},
            {"2", 2},
            {"3", 3},
            {"4", 4},
            {"5", 5},
            {"6", 6},
        };

        for(auto iter = mm.begin(); 
                 iter!= mm.end(); iter++){
            cout << iter->first << " " << iter->second << endl;
        }

        cout << "for range" << endl;
        /* 基于范围的for中的auto推导出的类型不是迭代器，
         * 而是具体的容器元素类型 
         *
         * 冒号后面的表达式只执行一次*/
        for(auto u : mm){
            cout << u.first << " " << u.second << endl;
        }
    }
    cout << "----------------------------" << endl;
    {
        /* 总结：
         * 具体来说，基于范围的 for 循环将以下面的方式查找容器的 begin 和 end 
         * 1.若容器是一个普通 array 对象(eg. int arr[10]), 那么begin是array的
         *   首地址，end为首地址加容器长度
         * 2.若容器是一个类对象，那么range-based for 将试图通过查找类的begin()
         *   和 end()方法来定位 begin / end 迭代器
         * 3.否则，range-based for 将试图使用全局的 begin / end 函数来定位 begin
         *   / end 迭代器
         * 
         * 因此，对于自定义类型来说，分别实现begin() / end() 方法即可*/
        void range_based_for(void);
        range_based_for();
    }
    cout << "----------------------------" << endl;
    {
        void function_bind(void);
        function_bind();
    }
    cout << "----------------------------" << endl;
    {
        void chapter2(void);
        chapter2();
    }
    cout << "----------------------------" << endl;
    {
        cout << "type_traits ..." << endl;

        /* std::is_same<T, U>对两种类型做了是否相同的判断，
         * 类型严格相同才会认为类型一直*/
        cout << "is_same<int, int>::value : " << is_same<int, int>::value << endl;
        cout << "is_same<int, unsigned int>::value : " << is_same<int, unsigned int>::value << endl;
        cout << "is_same<int, signed int>::value : " << is_same<int, signed int>::value << endl;
    }
    cout << "----------------------------" << endl;
    {
        /* is_base_of用来在编译器判断两种是否为继承关系 
         * is_base_of<B, D> 是将第一个模板参数作为基类类型*/
        cout << "is_base_of<AAA, BBB>::value : " << is_base_of<AAA, BBB>::value << endl;
        cout << "is_base_of<BBB, AAA>::value : " << is_base_of<BBB, AAA>::value << endl;
        cout << "is_base_of<CCC, BBB>::value : " << is_base_of<CCC, BBB>::value << endl;
    }
    cout << "----------------------------" << endl;
    {
        void algorithm(void);
        algorithm();
    }
    cout << "----------------------------" << endl;
    {
        unsigned char num = 0x23;
        printf("num = 0x%.2x - %d\n", num, num);

        int num2 = num;
        printf("num2 = 0x%x - %d\n", num2, num2);
    }
    cout << "----------------------------" << endl;
    {
        typedef tuple<int ,string, tuple<string, string> > unit_t;

        unit_t *p = NULL;

        p = new unit_t;

        get<0>(*p) = 10;
        get<1>(*p) = "nice to meet you";
        get<0>(get<2>(*p)) = "one";
        get<1>(get<2>(*p)) = "two";

        delete p;
    }
    cout << "----------------------------" << endl;
    {
        using name = string;
        name n("minphone");
        cout << "name : " << n << endl;
    }
    cout << "----------------------------" << endl;
    {
        unsigned short int a = 3;

        printf("a & 0xffff = %.x\n", a&0xffff);
        printf("0xffff = %d\n", 0xffff);
    }
    cout << "----------------------------" << endl;
    {
        void typeid_test(void);
        typeid_test();
    }
    cout << "----------------------------" << endl;
    {
        void byte_alignment(void);
        byte_alignment();
    }
    cout << "----------------------------" << endl;
    {
        void gcd(void);
        gcd();
    }
    cout << "----------------------------" << endl;
    {
        void cout_tdv_tde(void);
        cout_tdv_tde();
    }
    cout << "----------------------------" << endl;
    {
        OtherTest   ot;
        int ret = ot.main(); assert(-1 != ret);
    }
    cout << "----------------------------" << endl;
}

void display(char *ptr)
{
    printf("display addr : 0x%08x\n",*ptr);
}

void func0(const UCvec_t &ua)
{
    printf("func0 -> ua.size = %d\n",(int )ua.size());
    printf("func1 -> ua[0] = 0x%.2x\n",ua[0]);
    auto iter = ua.begin();
    printf("func1 -> *iter = 0x%.2x\n",*iter);
}

void struct_test(void)
{
    cout << "----------------------------" << endl;
    cout << "struct test ...\n";

    #pragma pack(1)
    struct{
        unsigned char a;
        unsigned char b;
        unsigned char c;
        struct{
            unsigned char d;
            unsigned char e[2];
        };
        unsigned char f;
        unsigned char g[2];
        struct{
            unsigned char h;
        };
    }ts;
    #pragma pack()

    cout << "sizeof(ts) : " << sizeof(ts) << endl;

    ts.a = 0x01;
    ts.b = 0x02;
    ts.c = 0x03;
    ts.d = 0x0d;
    ts.e[0] = 0xe1;
    ts.e[1] = 0xe2;
    ts.f = 0x0f;
    ts.g[0] = 0x0a;
    ts.g[1] = 0x1a;
    ts.h = 0xaa;

    cout << "ts : 0x ";
    for(int i=0; i<sizeof(ts); i++){
        printf("%.2x ",(unsigned)((unsigned char*)&ts)[i]);
    }
    cout << endl;
    cout << "----------------------------" << endl;
    {
        //string s("111151111A");
        string s("hello");
        unsigned char buf[64] = {0,};
        cout << "s.length() : " << s.length() << endl;
        memcpy(buf,s.c_str(),s.length());
        printf("buf : %s\n",buf);

        string s1("16:04:19:14:27:01");
        for(int i=0; i<5; i++){
            string::size_type pos = s1.find(':',0+i*3);
            if(pos == string::npos){
                cout << "not find ':' " << endl;
            }else{
                cout << "find - pos : " << pos << endl;
            }
        }

    }
    cout << "----------------------------" << endl;
    {
        string s1("16:04:19:14:27:01");
        int i = 0;
        string::size_type pos = -1;
        do{
            printf("i = %d - num : %c%c\n",i,s1[pos+1],s1[pos+2]);
            pos = s1.find(':',0+i++*3);
            cout << "find - pos : " << pos << endl;
        }while(pos != string::npos);
    }
    {
        string s;
        unsigned char buf[12] = "hello";

        for(int i=0; i<12; i++){
            s += buf[i];
        }

        cout << "s.length() : " << s.length() << endl;
        cout << "s : " << s << endl;
    }
    cout << "----------------------------" << endl;
    {
        typedef union{
            int a;
            struct{
                char b;
                char c;
            };
        }ttu_u;

        ttu_u   ttu;
    }
    cout << "----------------------------" << endl;
    {
#if 0
        /*not init for test*/
        char *p;

        cout << "before core dump" << endl;

        /*这个主要是用来做程序崩溃差错测试
         * eg .
         * 1.dmesg | grep program-train
         *   会显示如下信息：
         *   [982.192117] program-train[3361]:segfault at 7e04a0b58b3 ip 0000465b8c
         *   sp 00007ffd945a2260 error 7 in program-train[400000+7c000]
         *
         * 2.addr2line -e ./program-train 465b8c -f
         *   显示如下信息：
         *   struct_test
         *   /home/minphone/github/program-train/program_train/src/srcs/c_src/other.cpp:250 (discriminator 1)
         *   */
        *p = 10;

        cout << "core dump" << endl;
#endif
    }
    cout << "----------------------------" << endl;
    {
        void test01(void);
        void test02(void);

        void (*test_index[])(void) = {
            test01,
            test02
        };

        test_index[0]();
        test_index[1]();
    }
    cout << "----------------------------" << endl;
    {
        cout << "try catch..." << endl;
        try{
            int a = 10;
            if(a == 10){
                throw a;
            }
        }
        catch(int){
            cout << "catch int..." << endl;
        }
        catch(...){
            cout << "catch something..." << endl;
        }
    }
    cout << "----------------------------" << endl;
    {
        typedef struct{
            int     id;
#if 0
            string  name;
            string  mac;
#else
            char    name;
#endif
        }device_t;

        union devInfo{
            int         scene;
            device_t    dev;
        };

        devInfo dev;
    }
}

void test01(void)
{
    cout << "test01 ..." << endl;
}

void test02(void)
{
    cout << "test02 ..." << endl;
}

void do_pcb(void (*pf)(void))
{
    pf();
}

//--------------------------------------------------------------------

void auto_decltype_test(void)
{
    cout << "auto decltype test " << endl;
    {
        auto i = 10;
        cout << "i = " << i << endl;

        auto x = 5;
        auto pi = new auto(1);
        const auto *v = &x, u = 6; /* 常量定义初始化 */

        cout << "x = " << x << endl;
        cout << "*pi = " << *pi << endl;
        cout << "*v = " << *v << endl;
        cout << "u = " << u << endl;

        /* 总结：
         * 使用auto声明的变量，必须马上初始化*/
    }
    cout << "---------------------------" << endl;
    {
        int i = 10;
        decltype(i) y = 12;
        cout << "y = " << y << endl;
    }
}

void range_based_for(void)
{
    cout << "range_based_for" << endl;
    {
        for(int n = 2; n<8; n += 2){ //[2,8)
            cout << " ";
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
    {
    }
}

//--------------------------------------------------------------------

#include <functional>

struct AA{
    int a;
    void m_func(void)
    {
        cout << "m_func !" << endl;
    }
    static void m_func2(void)
    {
        cout << "func : " << __FUNCTION__ << endl;
    }
};

void fr_test01(void)
{
    cout << "func : " << __FUNCTION__ << endl;
}

void call_when_even(int x, const function<void(int)> &f)
{
    /* x % 2 == 0 */
    if(!(x & 1)){
        f(x);
    }
}

void output(int x)
{
    cout << "func : " << __FUNCTION__ ;
    cout << " " << x << " " << endl;
}

void output_add_2(int x)
{
    cout << "func : " << __FUNCTION__ ;
    cout << " " << x+2 << endl;
}

void output_3(int x, int y)
{
    cout << x << " " << y << endl;
}

void function_bind(void)
{
    /* 
     * 函数包装器
     * */
    cout << "function bind " << endl;
    {
        void (AA::* func_ptr)(void) = &AA::m_func;
        int AA::*ptr = &AA::a;

        AA aa;
        (aa.*func_ptr)();
        aa.*ptr = 123;

        cout << "aa.a = " << aa.a << endl;
    }
    cout << "---------------------------" << endl;
    {
        function<void(void)> fr = AA::m_func2;
        fr();

        fr = fr_test01;
        fr();
    }
    cout << "---------------------------" << endl;
    {
        /* placeholders::_1 是一个占位符，代表这个位置将在函数调用时
         * 被传入的第一个参数所替代*/
        auto fr = bind(output, placeholders::_1);
        for(int i=0; i<10; i++){
            call_when_even(i, fr);
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
    {
        auto fr = bind(output_add_2, placeholders::_1);
        for(int i=0; i<10; i++){
            call_when_even(i, fr);
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
    {
        /* std::bind可以直接绑定函数的所有参数，也可以仅绑定部分参数 
         * */
        bind(output_3, 1, 2)(); /*后面直接加括号，表示直接调用*/
        bind(output_3, placeholders::_1, 2)(1);
        bind(output_3, 2, placeholders::_1)(1);
        bind(output_3, 2, placeholders::_2)(1,2);
        bind(output_3, placeholders::_1, placeholders::_2)(3,4);
    }
}

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

struct OA{
    OA()
    {
        cout << "construct : " << ++g_constructCount << endl;
    }
    OA(const OA& a)
    {
        cout << "copy construct : " << ++g_copyConstructCount << endl;
    }
    ~OA()
    {
        cout << "destruct : " << ++g_destructCount << endl;
    }
};

OA GetOA(void)
{
    return OA();
}

class obj{
public :
    obj(){cout << "create obj " << endl; };
    obj(const obj& other) {cout << ">> copy create obj " << endl; };
    ~obj() { cout << "decreate obj " << endl; };
};

vector<obj> foo(void)
{
    vector<obj> c;
    c.push_back(obj());
    cout << "---- exit foo ----" << endl;
    return c;
}


void chapter2(void)
{
    cout << "func : " << __FUNCTION__ << endl;
    cout << "----------------------------" << endl;
    {
        int w1, w2;
        auto && v1 = w1;
    }
    cout << "----------------------------" << endl;
    /* 以下内容都被编译器优化过了，测试不出来效果 
     * 如果需要测试效果，需要直接使用命令编译 eg. g++ -std=c++11 main.c*/
    {
        cout << "get oa ..." << endl;
        OA a ;
        a = GetOA();
    }
    {
        cout << "g_constructCount : " << g_constructCount << endl;
        cout << "g_copyConstructCount : " << g_copyConstructCount << endl;
        cout << "g_destructCount : " << g_destructCount << endl;
    }
    cout << "----------------------------" << endl;
    {
        vector<obj> k;
        k = foo();
    }
}

constexpr int new_sz()
{
    return 43;
}

void afunc(int &a)
{
    cout << "a = " << a << endl;
}

void algorithm(void)
{
    cout << "algorithm ..." << endl;
    {
        vector<int> v = {1, 3, 5, 7, 9};
        auto isEven = [](int i){return i % 2 != 0;};

        bool isallOdd = all_of(v.begin(), v.end(), isEven);

        if(true == isallOdd){
            cout << "all is odd" << endl;
        }

        bool isNoneEven = none_of(v.begin(), v.end(), isEven);
        if(true == isNoneEven)
            cout << "none is even" << endl;
        else
            cout << "none is odd" << endl;
    }
    cout << "----------------------------" << endl;
    {
        constexpr int foo = new_sz();
        cout << "constexpr foo : " << foo << endl;
    }
    cout << "----------------------------" << endl;
    {
        int *p = new(int);

        *p = 10;

        cout << "*p = " << *p << endl;
    }
    cout << "----------------------------" << endl;
    {
        cout << "afunc(&a) ...." << endl;
        int a = 10;
        for(int i=0; i<10; i++)
            afunc(a);
        cout << "a = " << a << endl;
    }
    cout << "----------------------------" << endl;
    {
        char nts1[] = "Test";
        char nts2[] = "Test";

        string str1(nts1);
        string str2(nts2);

        hash<char*> ptr_hash;
        hash<string> str_hash;
        hash<int>   int_hash;

        cout << "hash value of nts1 : " << ptr_hash(nts1) << endl;
        cout << "hash value of nts2 : " << ptr_hash(nts2) << endl;

        cout << "hash value of str1 : " << str_hash(str1) << endl;
        cout << "hash value of str2 : " << str_hash(str2) << endl;
        cout << "hash value of str2 : " << hash<string>()(str2) << endl;

        cout << "hash value of int : " << int_hash(10) << endl;
        cout << "hash value of int : " << hash<int>()(10) << endl;
    }
}

void typeid_test(void)
{
    cout << "typeid(int).name() : "           << typeid(int).name()     << endl;
    cout << "typeid(unsigned).name() : "      << typeid(unsigned).name()<< endl;
    cout << "typeid(long).name() : "          << typeid(long).name()    << endl;
    cout << "typeid(unsigned long).name() : " << typeid(unsigned long).name() << endl;
    cout << "typeid(char).name() : "          << typeid(char).name()    << endl;
    cout << "typeid(unsigned char).name() : " << typeid(unsigned char).name() << endl;
    cout << "typeid(float).name() : "         << typeid(float).name()   << endl;
    cout << "typeid(double).name() : "        << typeid(double).name()  << endl;
    cout << "typeid(string).name() : "        << typeid(string).name()  << endl;
}

void byte_alignment(void)
{
    typedef struct{
        char a;
        char b;
        short int c;
        unsigned char d[0];
    }Msg1_t;

    typedef struct{
        char a;
        char b;
        short int c;
        unsigned char *p;
    }Msg2_t;

    cout << "sizeof(Msg1_t) : " << sizeof(Msg1_t) << endl;
    cout << "sizeof(Msg2_t) : " << sizeof(Msg2_t) << endl;

    char a[0];
    cout << "sizeof(a) : " << sizeof(a) << endl;

    char *p;
    cout << "sizeof(p) : " << sizeof(p) << endl;
}

/* greatest common divisor */
void gcd(void)
{
    int a = 1;
    printf("sizeof(a) : %d\n", sizeof(a));

    auto odd_judge = [](int a){
        /* a & -a : 判断变量a是2的最大公约数 */
        printf("+a = %.8x\n", a);
        printf("-a = %.8x\n", -a);
        printf("a & (-a) : %x(hex) --> %d(10)\n" , a & (-a), a & (-a));
    };

    odd_judge(1);
    odd_judge(2);
    odd_judge(0x8000);
    odd_judge(0x400);
    odd_judge(0x410);
    odd_judge(11);
    odd_judge(101);
    odd_judge(1011);

    printf("-------------\n");

    odd_judge(-1);
    odd_judge(-2);
    odd_judge(0x8000 * -1);
    odd_judge(0x400 * -1);
    odd_judge(0x410 * -1);
    odd_judge(-11);
    odd_judge(-101);
    odd_judge(-1011);
}

//--------------------------------------------------------------------

typedef struct {
    double posx;
    double posy;
    double posz;
    int    nwk;
    int    mac[8];
    int    nodetype;    /* [0:'C', 1:'R', 2:'E'] */
}TestDataVes_t;

typedef struct {
    double sposx;
    double sposy;
    double sposz;
    double eposx;
    double eposy;
    double eposz;
}TestDataEdg_t;

static TestDataVes_t tdv[] = {
    {0, 0, 0,      0x0000, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, 0},
    {0.7, 2.2, 1,  0x0001, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x08}, 1},
    {0, 1.8, 3,    0x0002, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x09}, 1},
    {1.6, 2.3, -1, 0x0003, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0a}, 2},
    {2, 0.8, 3,    0x0004, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0b}, 2},
    {-0.6, -0.6, 2,0x0005, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0c}, 2},
    {-1.3, 0.8, 2, 0x0006, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0d}, 1},
    {-1.5, -1, 0.3,0x0007, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0e}, 2},
    {0.5, -1.5, 2, 0x0008, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0f}, 1},
    {1.7, -0.8, 1, 0x0009, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x10}, 2},
    {1.5, -2.3, 0, 0x000a, {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11}, 2}
};

/* 此种定义在 C 中非法 */
static TestDataEdg_t tde[] = {
#if 1
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[1].posx, tdv[1].posy, tdv[1].posz},
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[2].posx, tdv[2].posy, tdv[2].posz},
    {tdv[0].posx, tdv[0].posy, tdv[0].posz, tdv[3].posx, tdv[3].posy, tdv[3].posz},
    {tdv[1].posx, tdv[1].posy, tdv[1].posz, tdv[4].posx, tdv[4].posy, tdv[4].posz},
    {tdv[1].posx, tdv[1].posy, tdv[1].posz, tdv[5].posx, tdv[5].posy, tdv[5].posz},
    {tdv[2].posx, tdv[2].posy, tdv[2].posz, tdv[6].posx, tdv[6].posy, tdv[6].posz},
    {tdv[2].posx, tdv[2].posy, tdv[2].posz, tdv[7].posx, tdv[7].posy, tdv[7].posz},
    {tdv[6].posx, tdv[6].posy, tdv[6].posz, tdv[8].posx, tdv[8].posy, tdv[8].posz},
    {tdv[8].posx, tdv[8].posy, tdv[8].posz, tdv[9].posx, tdv[9].posy, tdv[9].posz},
    {tdv[8].posx, tdv[8].posy, tdv[8].posz, tdv[10].posx, tdv[10].posy, tdv[10].posz}
#endif
};

void cout_tdv_tde(void)
{
    cout << "tdv" << endl;
    cout << "tde" << endl;

    cout << "tdv List :" << endl;
    for(int i=0; i<(int)(sizeof(tdv)/sizeof(TestDataVes_t)); i++){
        printf("(%.2f, %.2f, %.2f) - 0x%.4x - ", tdv[i].posx, tdv[i].posy, tdv[i].posz, tdv[i].nwk);
        printf("0x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x - ", 
                tdv[i].mac[0], 
                tdv[i].mac[1], 
                tdv[i].mac[2], 
                tdv[i].mac[3], 
                tdv[i].mac[4], 
                tdv[i].mac[5], 
                tdv[i].mac[6], 
                tdv[i].mac[7]
                );
        if(tdv[i].nodetype == 0) printf("'C'\n");
        else if(tdv[i].nodetype == 1) printf("'R'\n");
        else printf("'E'\n");
    }

    cout << endl;

    cout << "tde List :" << endl;
    for(int i=0; i<(int)(sizeof(tde)/sizeof(TestDataEdg_t)); i++){
        printf("((%.2f, %.2f, %.2f) -> (%.2f, %.2f, %.2f))\n", 
                tde[i].sposx,
                tde[i].sposy,
                tde[i].sposz,
                tde[i].eposx,
                tde[i].eposy,
                tde[i].eposz
                );
    }
    cout << "----------------------------" << endl;
    {
        cout << "汉字打印" << endl;

        string s = "汉字";
        char *chars = "汉字";
        char arrays[] = "汉字";

        cout << "s = " << s << endl;
        cout << "chars = " << chars << endl;
        cout << "arrays = " << arrays << endl;
    }
}

OtherTest::OtherTest()
{
    cout << "----------- OtherTest Class ----------------" << endl;
}

OtherTest::~OtherTest()
{
    cout << "----------- End OtherTest Class ------------" << endl;
}

int  OtherTest::main(void)
{
    int ret = 0;

    ret = this->macro_test(); assert(-1 != ret);

    ret = this->cout_test(); assert(-1 != ret);

    ret = this->bits_test(); assert(-1 != ret);

    return 0;
}

int  OtherTest::macro_test(void)
{
    cout << "Function: OtherTest::macro_test()" << endl;
    {
        typedef struct{
            int a;
            char b;
            double c;
            int d;
            float e;
        }Data_t;

        cout << "sizeof(Data_t) : " << sizeof(Data_t) << endl;

        #define DATA_T_SIZE ((sizeof(Data_t)+8-1)/8*8)

        cout << "sizeof(Data_t *) : " << sizeof(Data_t *) << endl;
        cout << "DATA_T_SIZE : " << DATA_T_SIZE << endl;

        /*
         * Note !
         *
         * 运行结果值：DATA_T_SIZE = sizeof(Data_t) 即两个相等
         * */

        /* 
         * 取消宏
         * */
        #ifdef DATA_T_SIZE
        #undef DATA_T_SIZE
        #endif
    }
    cout << "----------------------------" << endl;
    {
        #define DMA_DELAY_THRESHOLD_SET(dma_ctrl) ((dma_ctrl) | (0x3 << 2))
        #define DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl) ((dma_ctrl) & ~(0x3 << 2))

        unsigned dma_ctrl = 0x1230;
        printf("dma_ctrl = 0x%x \n", dma_ctrl);
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_SET(dma_ctrl));
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl)); cout << endl;

        dma_ctrl = 0x1230;
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_SET(dma_ctrl = 0));
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl = 0)); cout << endl;

        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_SET(dma_ctrl = (0x880) | 0x1));
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl = (0x880) | 0x1)); cout << endl;

        dma_ctrl = 0;
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_SET(dma_ctrl += 0x20));
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl += 0x20)); cout << endl;

        dma_ctrl = 0;
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_SET(dma_ctrl |= 0x20));
        printf("dma_ctrl = 0x%x \n", DMA_DELAY_THRESHOLD_CLEAR(dma_ctrl |= 0x20)); cout << endl;

        #ifdef DMA_DELAY_THRESHOLD_SET
        #undef DMA_DELAY_THRESHOLD_SET
        #endif
        #ifdef DMA_DELAY_THRESHOLD_CLEAR
        #undef DMA_DELAY_THRESHOLD_CLEAR
        #endif
    }
    cout << "----------------------------" << endl;
    {
        typedef struct {
            char a;
            char b;
            int  c;
        }Data_t;

        Data_t data;

        MACRO_SET_A(10);

        printf("data.a = %d \n", data.a);
    }
    cout << "----------------------------" << endl;
    {
        unsigned DMA_CTRL = 0;
        unsigned HW_DEMOD_DMA_CTRL = 0;
        /*
         * 这里 delay 设置成 6 bit
         * */
        #define DMA_DELAY_THRESHOLD(delay)                      \
        do{                                                     \
            DMA_CTRL &= ~(0x3 << 2);                            \
            HW_DEMOD_DMA_CTRL &= ~(0xf << 4);                   \
                                                                \
            DMA_CTRL |= (((delay) & 0x3F) & 0x30) >> 2;         \
            HW_DEMOD_DMA_CTRL |= (((delay) & 0x3F) & 0x0F) << 4;\
        }while(0)

        DMA_DELAY_THRESHOLD(0x30);

        printf("DMA_CTRL = 0x%x\n", DMA_CTRL);
        printf("HW_DEMOD_DMA_CTRL = 0x%x\n", HW_DEMOD_DMA_CTRL); cout << endl;

        
        DMA_CTRL = 0;
        HW_DEMOD_DMA_CTRL = 0;
        DMA_DELAY_THRESHOLD(0x33);
        printf("DMA_CTRL = 0x%x\n", DMA_CTRL);
        printf("HW_DEMOD_DMA_CTRL = 0x%x\n", HW_DEMOD_DMA_CTRL); cout << endl;

        #ifdef DMA_DELAY_THRESHOLD
        #undef DMA_DELAY_THRESHOLD
        #endif
    }
    cout << "----------------------------" << endl;
    {
        #define DMA_DELAY_THRESHOLD 0x33

        unsigned DMA_CTRL = 0;
        unsigned HW_DEMOD_DMA_CTRL = 0;

        printf("DMA_CTRL = 0x%x\n", DMA_CTRL | ((((DMA_DELAY_THRESHOLD) & 0x3F) & 0x30) >> 2));
        printf("HW_DEMOD_DMA_CTRL = 0x%x\n", HW_DEMOD_DMA_CTRL | ((((DMA_DELAY_THRESHOLD) & 0x3F) & 0x0F) << 4)); cout << endl;


        #ifdef DMA_DELAY_THRESHOLD
        #undef DMA_DELAY_THRESHOLD
        #endif
    }
    cout << "----------------------------" << endl;

    return 0;
}

int  OtherTest::cout_test(void)
{
    auto func = [](int &i){
        i = 10;
        return i;
    };

    int x = 0;

    /* 
     * cout 语句是 "从右往左" 执行 | 符合 栈 的执行模型
     * */
    cout << "x = " << func(x) << " | x = " << x << endl;

    /*
     * 执行结果： 11 | 10
     * */
    cout << "x = " << x++ << " | " << x++ << endl;

    return 0;
}

int  OtherTest::bits_test(void)
{
    cout << "----------------------------" << endl;
    cout << "OtherTest::bits_test() ..." << endl;
    {
        /* 
         * 如果是清除 某几位，正确写法：
         *
         *  -> bit_origine^(bit_origine & 0xab) | 0xab 表示具体值
         * */

        unsigned bit_origine = 0x12f4;
        printf("bit_origine = 0x%x\n", bit_origine);

        printf("bit_origine^0x%x = 0x%x\n", 0x10, bit_origine^0x10);
        printf("bit_origine^0x%x = 0x%x\n", 0x20, bit_origine^0x20);
        printf("bit_origine^0x%x = 0x%x\n", 0x40, bit_origine^0x40);
        printf("bit_origine^0x%x = 0x%x\n", 0x80, bit_origine^0x80);

        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x10, bit_origine^(bit_origine & 0x10));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x20, bit_origine^(bit_origine & 0x20));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x40, bit_origine^(bit_origine & 0x40));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x80, bit_origine^(bit_origine & 0x80));

        printf("bit_origine^0x%x = 0x%x\n", 0x11, bit_origine^0x11);
        printf("bit_origine^0x%x = 0x%x\n", 0x22, bit_origine^0x22);
        printf("bit_origine^0x%x = 0x%x\n", 0x44, bit_origine^0x44);
        printf("bit_origine^0x%x = 0x%x\n", 0x88, bit_origine^0x88);

        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x11, bit_origine^(bit_origine & 0x11));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x22, bit_origine^(bit_origine & 0x22));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x44, bit_origine^(bit_origine & 0x44));
        printf("bit_origine^(bit_origine & 0x%x) = 0x%x\n", 0x88, bit_origine^(bit_origine & 0x88));
    }
    cout << "----------------------------" << endl;
    return 0;
}

