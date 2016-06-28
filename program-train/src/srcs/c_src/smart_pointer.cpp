/*
 * Progarm Name: smart_pointer.cpp
 * Created Time: 2016-06-27 13:09:30
 * Last modified: 2016-06-28 23:43:58
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "smart_pointer.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unistd.h>

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

        shared_ptr<A> sp1(new A);
        sp1->a = 10;
        shared_ptr<A> sp2 = sp1->GetSelf();
        cout << "sp2->a : " << sp2->a << endl;
        cout << "sp1.use_count() : " << sp1.use_count() << endl;
        cout << "sp2.use_count() : " << sp2.use_count() << endl;
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

            ap->bptr = bp;
            bp->aptr = ap;

            wpa = ap;
            wpb = bp;
        }
        cout << "wpa.use_count() : " << wpa.use_count() << endl;
        cout << "wpb.use_count() : " << wpb.use_count() << endl;
        cout << "memory is leak" << endl;
    }
}

