/*
 * Progarm Name: data-structure.cpp
 * Created Time: 2016-12-30 09:12:14
 * Last modified: 2017-01-07 17:54:15
 * @author: minphone.linails linails@foxmail.com 
 */

#include "data-structure.hpp"
#include <iostream>
#include <cassert>

#include "linear-list.hpp"
#include "mstack.hpp"
#include "mqueue.hpp"
#include "mstring.hpp"

using std::cout;
using std::endl;

DataStructure::DataStructure()
{
}

DataStructure::~DataStructure()
{
}

int  DataStructure::datastruct_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->linearlist(argc, argv); assert(-1 != ret);

    ret = this->stack(); assert(-1 != ret);

    ret = this->queue(argc, argv); assert(-1 != ret);

    ret = this->mstring(argc, argv); assert(-1 != ret);

    return ret;
}

int  DataStructure::linearlist(int argc, char **argv)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
#if 1
        assert(-1 != ret);
        tLinearList tll;
        ret = tll.linearlist_main(argc, argv);
#endif
    }

    return ret;
}

int  DataStructure::stack(void)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
        mStack ms;
        ret = ms.stack_main(0, NULL); assert(-1 != ret);
    }

    return ret;
}

int  DataStructure::queue(int argc, char **argv)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
        mQueue mq;
        ret = mq.mqueue_main(argc, argv); assert(-1 != ret);
    }

    return ret;
}

int  DataStructure::mstring(int argc, char **argv)
{
    int ret = 0 ;

    cout << "--------------------------------------" << endl;
    {
        cout << "mstring()" << endl;
        mString s("hello world!");

        cout << "s.length() : " << s.length() << endl;

        mString s1(s(3, 5));
        cout << "s1.length() : " << s1.length() << endl;
        cout << "s1.c_str() : " << s1.c_str() << endl;

        cout << "s.length() : " << s.length() << endl;

        mString s2;

        s1 = s;
        cout << "s1.length() : " << s1.length() << endl;
        cout << "s1.c_str() : " << s1.c_str() << endl;

        s1 += "nice";
        cout << "s1.length() : " << s1.length() << endl;
        cout << "s1.c_str() : " << s1.c_str() << endl;

        s1 += s;
        cout << "s1.length() : " << s1.length() << endl;
        cout << "s1.c_str() : " << s1.c_str() << endl;

        if(s1 == s){
            cout << "s1 == s : YES !" << endl;
        }else{
            cout << "s1 == s : NO !" << endl;
        }

        int index = s1.find("wold", 0);
        cout << "index : " << index << endl;

        s1.find("abaabcac");
    }
    cout << "--------------------------------------" << endl;
    {
        /*
         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
         *
         * print sizeof(type) : x64 - byte
         *  
         *  size_t    : 8
         *  short     : 2
         *  int       : 4
         *  long      : 8
         *  lont long : 8
         * */
        cout << "sizeof(size_t) : " << sizeof(size_t) << endl;
        cout << "sizeof(short)  : " << sizeof(short) << endl;
        cout << "sizeof(int)    : " << sizeof(int) << endl;
        cout << "sizeof(long)   : " << sizeof(long) << endl;
        cout << "sizeof(long long) : " << sizeof(long long) << endl;
   }

    return ret;
}


