/*
 * Progarm Name: other.cpp
 * Created Time: 2016-03-11 15:16:33
 * Last modified: 2016-07-23 13:46:00
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
    cout << "other test \n";

    cout << "sizeof(A) :" << sizeof(A) << endl;
    cout << "sizeof(int):" << sizeof(int) << endl;
    cout << "sizeof(int *) :" << sizeof(int *) << endl;

    int *p = &a.i;
    for(int i=0; i<4; i++){
        printf("p[%d] = %x\n",i,&p[i]);
        p[i] = i;
    }

    cout <<"-----------------------" << endl;
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

    cout <<"-----------------------" << endl;

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
         * 具体来说，基于范围的 for 循环将以厦门的方式查找容器的 begin 和 end 
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
}

