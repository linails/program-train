/*
 * Progarm Name: smart_pointer.cpp
 * Created Time: 2016-06-27 13:09:30
 * Last modified: 2016-09-02 09:08:57
 * @author: minphone.linails linails@foxmail.com 
 */

#include "smart_pointer.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <cstdio>

using namespace std;

void smart_pointer(void)
{
    cout << "-----------------------------------------" << endl;
    cout << "smart_pointer" << endl;
    {
        shared_ptr<int> p(new int(1));
        cout << "*p = " << *p << endl;
        shared_ptr<int> p2 = p;
        cout << "*p2 = " << *p2 << endl;
        cout << "p.use_count() : " << p.use_count() << endl;
        cout << "p2.use_count() : " << p2.use_count() << endl;

        shared_ptr<int> ptr;
        ptr.reset(new int(2));
        cout << "*ptr = " << *ptr << endl;
        cout << "ptr.use_count() : " << ptr.use_count() << endl;

        int *ip = ptr.get();
        cout << "*ip = " << *ip << endl;

        int *ip2 = new int(10);
        int *ip3 = new int(20);
        shared_ptr<int> ptr2;
        ptr2.reset(ip2);
        cout << "*ptr2 = " << *ptr2 << endl;
        ptr2.reset(ip3);
        cout << "*ptr2 = " << *ptr2 << endl;
        cout << "ptr2.use_count() : " << ptr2.use_count() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
#if 0
        struct ta{
            int a[1000];
        };
        shared_ptr<ta> ptr;
        for(unsigned int i=0; i<100000; i++){
            ptr.reset(new ta);
        }
        while(1);
#endif
#if 0
        struct ta{
            int a[1024];
        };
        ta *ptr;
        for(unsigned int i=0; i<100000; i++){
            ptr = new ta;
        }
        while(1);
#endif
#if 0
        struct ta{
            int a[1024];
        };
        shared_ptr<ta> ptr;
        ta *pta = NULL;
        for(unsigned int i=0; i<100000; i++){
            pta = new ta;
            ptr.reset(pta);
        }
        while(1);
#endif
    }
    cout << "-----------------------------------------" << endl;
    {
        /* return self this pointer */
        struct A : public enable_shared_from_this<A>
        {
            shared_ptr<A> GetSelf(){
                return shared_from_this();
            }
            int a;
        };

        /* weak_ptr不会增加引用计数 */
        weak_ptr<A> wp;
        {
            shared_ptr<A> sp1(new A);
            sp1->a = 10;
            shared_ptr<A> sp2 = sp1->GetSelf();
            cout << "sp2->a : " << sp2->a << endl;
            cout << "sp1.use_count() : " << sp1.use_count() << endl;
            cout << "sp2.use_count() : " << sp2.use_count() << endl;
            wp = sp1;
        }
        cout << "wp.use_count() : " << wp.use_count() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        struct A;
        struct B;

        struct A{
            shared_ptr<B> bptr;
            ~A()
            {
                cout << "A is deleted !" << endl;
            }
        };

        struct B{
            shared_ptr<A> aptr;
            ~B()
            {
                cout << "B is deleted !" << endl;
            }
        };

        weak_ptr<A> wpa ;
        weak_ptr<B> wpb ;
        {
            shared_ptr<A> ap(new A);
            shared_ptr<B> bp(new B);

            //ap->bptr = bp;
            //bp->aptr = ap;

            wpa = ap;
            wpb = bp;
        }

        cout << "wpa.use_count() : " << wpa.use_count() << endl;
        cout << "wpb.use_count() : " << wpb.use_count() << endl;
        if(wpa.expired()){
            cout << "weak_ptr(ap) is null" << endl;
        }else{
            cout << "weak_ptr(ap) is valid" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 此例子中的做法，会因此循环引用，导致内存释放不掉，引发内存泄漏
         * 解决方法：
         *  1.把其中一个shared_ptr换成weak_ptr
         *  2.weak_ptr不会引起引用计数，因此可以有效解决这类问题*/
        struct A;
        struct B;

        struct A{
            shared_ptr<B> bptr;
            ~A()
            {
                cout << "A is deleted !" << endl;
            }
        };

        struct B{
            shared_ptr<A> aptr;
            ~B()
            {
                cout << "B is deleted !" << endl;
            }
        };

        weak_ptr<A> wpa ;
        weak_ptr<B> wpb ;
        {
            shared_ptr<A> ap(new A);
            shared_ptr<B> bp(new B);

            ap->bptr = bp;
            bp->aptr = ap;

            wpa = ap;
            wpb = bp;
        }
        cout << "wpa.use_count() : " << wpa.use_count() << endl;
        cout << "wpb.use_count() : " << wpb.use_count() << endl;
        cout << "memory is leak" << endl;
        if(wpa.expired()){
            cout << "weak_ptr(ap) is null" << endl;
        }else{
            cout << "weak_ptr(ap) is valid" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        shared_ptr<int> sp(new int(10));
        weak_ptr<int> wp(sp);

        /* 通过expired() 函数来进行判断智能指针是否有效-是否释放 */
        if(wp.expired()){
            cout << "weak_ptr is null" << endl;
        }else{
            cout << "weak_ptr is valid" << endl;

            /* 通过lock() 来获得未释放智能指针 */
            auto spt = wp.lock();
            cout << "*spt = " << *spt << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        struct A:public std::enable_shared_from_this<A>
        {
            shared_ptr<A> getself()
            {
                return shared_from_this();
            }
            ~A()
            {
                cout << "A is deleted !" << endl;
            }
        };

        shared_ptr<A> p;
        {
            shared_ptr<A> spy(new A);
            p = spy->getself();
        }
        weak_ptr<A> wp(p);
        cout << "wp.use_count() : " << wp.use_count() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
#if 0
        struct A
        {
            shared_ptr<A> getself()
            {
                /* 此种做法会导致析构多次，正在做法是使用
                 * shared_from_this() 来返回this指针
                 * 参考上例*/
                return shared_ptr<A>(this);
            }
            ~A()
            {
                cout << "A is deleted !" << endl;
            }
        };

        shared_ptr<A> p;
        {
            shared_ptr<A> spy(new A);
            p = spy->getself();
        }
        weak_ptr<A> wp(p);
        cout << "memory leak" << endl;
        cout << "wp.use_count() : " << wp.use_count() << endl;
#endif
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 总结： 
         * 1.shared_ptr 和 unqi_ptr使用时如何选择：
         *  如果希望只有一个智能指针管理资源或者管理数组，
         *  可以用unqi_ptr;
         *  如果希望多个智能指针管理同一个资源，可以使用
         *  shared_ptr
         * 2.weak_ptr是shared_ptr的助手，只是监视shared_ptr管理
         *  资源是否被释放，本身并不操作或者管理资源。
         *  用于解决shared_ptr循环引用，和返回this指针的问题*/

        void smart_pointer_t1(void);
        smart_pointer_t1();
    }
    cout << "-----------------------------------------" << endl;
    {
    }
}

struct Handler{
    void *(*create)(void);
    void (*release)(void *);
    char *buf;
};

void *Create(void);
void Release(void *p);

static struct Handler for_test = {
    Create,
    Release,
    NULL
};

struct Handler *get_handler(void)
{
    return &for_test;
}

void *Create(void)
{
    for_test.buf = new char[100]();
    cout << "new char[100]() " << endl;
    return for_test.buf;
}

void Release(void *p)
{
    delete[] (char *)p;
    cout << "delete p" << endl;
}

void smart_pointer_t1(void)
{
    {
        void *p = get_handler()->create();

        memcpy(p,"hello world",sizeof("hello world"));

        cout << "p = " << p << endl;
        printf("\"p\" = %s\n",(char *)p);

        get_handler()->release(p);
    }
    cout << "-----------------------------------------" << endl;
    {
        void *p = get_handler()->create();
        shared_ptr<void> sp(p, [](void *p){get_handler()->release(p); cout << "shared_ptr delete !" << endl;});
        cout << "sp.use_count() : " << sp.use_count() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 使用宏定义 shared_ptr 是一种比较好的管理第三方库使用指针的方式 */
        #define GUARD(p) std::shared_ptr<void> p##p(p,[](void *p){get_handler()->release(p);\
                cout << "GUARD(P) delete !" << endl;});

        void *p = get_handler()->create();
        GUARD(p);
    }
}

