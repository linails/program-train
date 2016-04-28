/*
 * Progarm Name: other.cpp
 * Created Time: 2016-03-11 15:16:33
 * Last modified: 2016-04-19 16:36:05
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "other.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <string>
#include "class_test.h"

using namespace std;

struct A{
    int i;
    int *p;
};

A a;

typedef vector<unsigned char> UCvec_t;

static void struct_test(void);

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
    struct_test();
}

void display(char *ptr)
{
    printf("display addr : 0x%08x\n",*ptr);
}

void func0(const UCvec_t &ua)
{
    printf("func0 -> ua.size = %d\n",ua.size());
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
        printf("%.2x ",((unsigned char*)&ts)[i]);
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
}


