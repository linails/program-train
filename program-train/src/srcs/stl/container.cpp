/*
 * Progarm Name: container.cpp
 * Created Time: 2016-12-20 17:17:15
 * Last modified: 2017-11-10 16:46:45
 * @author: minphone.linails linails@foxmail.com 
 */

#include "container.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <map>
#include <typeinfo>
#include <bitset>
#include <list>
#include <queue>
#include <deque>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <stack>
#include <cstring>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::list;
using std::tuple;
using std::make_pair;
using std::make_tuple;
using std::stack;
using std::queue;
using std::allocator;

Container::Container()
{
}

Container::~Container()
{
}

int  Container::container_main(int argc, char **argv)
{
    int ret = 0;

    //ret = this->container_test(); assert(-1 == ret);
    
    ret = this->vector_t(); assert(-1 != ret);
    
    ret = this->list_t(); assert(-1 != ret);

    ret = this->map_t(); assert(-1 != ret); 

    ret = this->stack_t(); assert(-1 != ret); 

    ret = this->queue_t(); assert(-1 != ret); 

    ret = this->unordered_map_t(); assert(-1 != ret); 

    ret = this->allocator_t(); assert(-1 != ret); 

    return ret;
}

int  Container::vector_t(void)
{
    int ret = 0;

    {
        auto fp = [](vector<int> iv){
            cout << "iv : ";
            for(auto id : iv) {
                cout << id << " ";
            }
            cout << endl;
        };

        vector<int> iv;

        iv.push_back(1);
        iv.push_back(2);
        iv.push_back(3);
        iv.push_back(4);
        iv.push_back(5);

        fp(iv);

        auto iter = find(iv.begin(), iv.end(), 3);
        if(iter != iv.end()){
            cout << "find it and delete it" << endl;

            /* 
             * iterator erase(iterator it)  : 删除向量中某一个元素
             * iterator erase(iterator first, iterator last)  : 删除向量[first, last)
             * */
            iv.erase(iter);
            fp(iv);
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> gids;
        gids.push_back(0);
        gids.push_back(0);
        gids.push_back(2);
        gids.push_back(4);
        gids.push_back(3);
        gids.push_back(5);
        gids.push_back(4);
        gids.push_back(1);
        gids.push_back(1);
        gids.push_back(5);
        gids.push_back(1);
        gids.push_back(2);
        gids.push_back(0);
        gids.push_back(3);
        gids.push_back(2);
        gids.push_back(5);
        gids.push_back(4);
        gids.push_back(1);
        gids.push_back(3);
        gids.push_back(5);

        auto print_gids = [](vector<int> &gids){
            cout << "gids :";
            for(auto i : gids) cout << " " << i;
            cout << endl;
        };

        print_gids(gids);

        sort(gids.begin(), gids.end()); print_gids(gids);

        auto iter = unique(gids.begin(), gids.end()); print_gids(gids);

        gids.resize(std::distance(gids.begin(), iter)); print_gids(gids);
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> iv;
        
        iv.push_back(0);
        iv.push_back(2);
        iv.push_back(4);

        cout << "iv.size() : " << iv.size() << endl;

        iv.pop_back();
        cout << "iv.size() : " << iv.size() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        #if 1
        struct Data{
            Data(){}
            int a;
            char b;
            char *c;
            int  *d = nullptr;
            struct Data *next = nullptr;
            vector<char *> cv;
        };

        vector<Data *> dv;
        for(int i=0; i<10; i++){
            Data *pd = new Data();
            pd->cv.push_back(new char[10]());

            dv.push_back(pd);
        }

        vector<Data *> dv0;

        dv0 = dv;

        for(auto &u : dv){
            for(auto &c : u->cv) delete[] c;
            delete u;
        }

        vector<Data *> dv1 = dv;
        //dv1[0]->a = 10;

        cout << "dv.size() : " << dv.size() << endl;
        cout << "dv1.size() : " << dv1.size() << endl;
        #endif
    }
    cout << "-----------------------------------------" << endl;
    {
        struct Data{
            Data(){}
            ~Data(){
                cout << "icv.size() : " << cv.size() << endl;
            }
            int a;
            char b;
            char *c;
            int  *d = nullptr;
            struct Data *next = nullptr;
            vector<char *> cv;
        };

        Data *d = new Data();

        vector<char *> ocv;
        ocv.push_back(new char[10]());
        ocv.push_back(new char[10]());

        cout << "ocv.size() : " << ocv.size() << endl;
        d->cv = ocv;
        cout << "d->cv.size() : " << d->cv.size() << endl;

        for(auto ptr : d->cv) if(nullptr != ptr) delete ptr;
        delete d;
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::list_t(void)
{
    int ret = 0;

    {
        auto fp = [](list<int> &li){
            cout << "li : ";
            for(auto id : li) {
                cout << id << " ";
            }
            cout << endl;
        };

        list<int> li;
        li.push_back(1);
        li.push_back(2);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(3);
        li.push_back(4);
        li.push_back(5);

        fp(li);

        /* 
         *  <<STL源码剖析>>
         *  iterator list<>::erase(iterator position){
         *      ...
         *      return iterator(next_node);
         *  }
         * */
        #if 1
        for(auto iter = li.begin();
                 iter!= li.end();){
            if(*iter == 3) {
                iter = li.erase(iter);
            }else{
                iter++;
            }
        }
        #else
        auto iter = li.begin();

        while(iter != li.end()){
            if(*iter == 3){
                iter = li.erase(iter);
            }else{
                iter++;
            }
        }
        #endif

        fp(li);
    }
    cout << "-----------------------------------------" << endl;
    {
        list<char>  data_list;
        data_list.push_back('1');
        data_list.push_back('2');
        data_list.push_back('3');
        data_list.push_back('.');
        data_list.push_back('5');
        data_list.push_back('6');
        data_list.push_back('7');

        char forword = '.';

        /* 
         * 反向遍历的时候，不可以调用 erase 方法，因为这个时候的 iter 的类型和正向遍历的类型不一样
         * */
        //for(auto iter = data_list.rbegin(); iter!= data_list.rend();)
        for(auto iter = data_list.begin(); iter!= data_list.end();){

            if(*iter == forword){
                data_list.push_front(forword);

                iter = data_list.erase(iter);
                continue;
            }

            iter++;
        }

        cout << "data_list : ";
        for(auto iter = data_list.begin(); 
                 iter!= data_list.end(); iter++){
            cout << *iter << " ";
        }
        cout << endl;

    }
    cout << "-----------------------------------------" << endl;
    {
        typedef struct{
            int buf[10];
        }ArrayData_t;

        list<ArrayData_t> arrlist;

        ArrayData_t a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        ArrayData_t b = {10, 20, 30, 40, 50, 60, 70, 80, 90, 10};

        arrlist.push_back(a);
        arrlist.push_back(b);

        cout << "arrlist.size() : " << arrlist.size() << endl;

        for(auto &u : arrlist){
            cout << "u : ";
            for(int i=0; i<10; i++){
                cout << u.buf[i] << " ";
            }
            cout << endl;
        }
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::map_t(void)
{
    int ret = 0;

    {
        typedef map<string, list<tuple<int, string> > > BindDeviceSet_t;

        list<tuple<int, string> > li;
        BindDeviceSet_t binddev_set;

        li.push_back(make_tuple(1, "01"));
        li.push_back(make_tuple(2, "02"));
        li.push_back(make_tuple(3, "03"));

        binddev_set.insert(make_pair("g1", li));

        cout << "binddev_set.size() : " << binddev_set.size() << endl;

        auto iter = binddev_set.begin();

        for(auto &dev : iter->second){
            cout << "std::get<0>(dev) : " << std::get<0>(dev) << endl;
            cout << "std::get<1>(dev) : " << std::get<1>(dev) << endl;
        }
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::stack_t(void)
{
    int ret = 0;

    {
        auto stack_info = [](stack<int> &is){
            vector<int> copy;
            cout << "stack<int> : ";
            while(false == is.empty()){
                cout << is.top() << " ";
                copy.push_back(is.top());
                is.pop();
            }
            cout << endl;

            for(auto iter = copy.rbegin(); iter != copy.rend(); iter++) is.push(*iter);
        };

        stack<int> is;

        is.push(1);
        is.push(3);

        stack_info(is);
        stack_info(is);
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::queue_t(void)
{
    int ret = 0;

    {
        cout << "queue_t() .. " << endl;

        queue<int> qi;

        for(int i=0; i<10; i++){
            qi.push(i);
        }

        while(false == qi.empty()){
            int a = qi.front();
            qi.pop();
            cout << "a = " << a << endl;
        }
        cout << "qi.size() : " << qi.size() << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        typedef struct{
            int     flag; 
            char    buf[128];
            vector<int> vi;
        }Data_t;

        queue<Data_t> dq;

        for(int i=0; i<50; i++){
            Data_t data;
            data.flag = i;
            data.vi.push_back(i);

            dq.push(data);
        }

        cout << "dq.size() : " << dq.size() << endl;

        while(false == dq.empty()){
            Data_t data = dq.front();
            dq.pop();
        }

        cout << "dq.size() : " << dq.size() << endl;
    }
    cout << "-----------------------------------------" << endl;

    return ret;
}

int  Container::unordered_map_t(void)
{
    {
        unordered_map<int , char*> icmap;

        icmap.insert(make_pair(1, new char[10]));

        cout << "icmap.size() : " << icmap.size() << endl;

        for(auto &u : icmap){
            if(nullptr != u.second){
                delete[] u.second;
            }
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 
         * 针对复杂数据的使用
         * */
        struct Data{
            Data(){}
            int a;
            char b;
            char *c;
            int  *d = nullptr;
            struct Data *next = nullptr;
            vector<char *> cv;
        };

        unordered_map<int, Data *> idmap;

        Data *pd = new Data();
        idmap.insert(make_pair(1, pd));

        cout << "idmap.size() : " << idmap.size() << endl;
        delete pd;
    }
    cout << "-----------------------------------------" << endl;
    {
        class PesPacket;
        class DescriptorBase;
        struct TsES{
            TsES(){}
            TsES(const TsES &es){
                this->pes_packet = es.pes_packet;
            }
            ~TsES(){}
            unsigned short           pid        = 0;
            unsigned char            stream_id  = 0;
            unsigned char            stream_type= 0;
            unsigned short           program_number = 0;
            vector<DescriptorBase *> descriptors;
            PesPacket               *pes_packet = nullptr;
        };

        unordered_map<int, TsES *> itmap;

        TsES *es = new TsES();

        auto add_es = [&itmap](TsES *es){
            auto iter = itmap.find(es->pid);
            if(iter == itmap.end()){
                itmap.insert(make_pair(1, es));
            }
        };
        
        add_es(es);

        cout << "itmap.size() : " << itmap.size() << endl;
        delete es;

    }
    cout << "-----------------------------------------" << endl;
    return 0;
}

/* 
 * allocator 的引入是 C++ 内存管理的一个突破，因为 STL 所有组件的内存均从 allocator 分配
 * */
int  Container::allocator_t(void)
{
    cout << "---[Start] Container::allocator_t() ------" << endl;
    {
        allocator<char> alloc;

        char *ptr = alloc.allocate(40);

        memcpy(ptr, "0123456789012345678\0", 20);

        cout << "ptr = " << ptr << endl;
        alloc.deallocate(ptr, 40);
    }
    cout << "-----------------------------------------" << endl;
    {
        allocator<char> alloc;

        char *ptr = alloc.allocate(40);
        char *ptrn = new char[40];

        string s("0123456789012345678\0");
        std::uninitialized_copy(s.begin(), s.end(), ptr);
        cout << "ptr = " << ptr << endl;

        /* 
         * Note !
         *  
         *  这里实验一个 将 buffer 都填充满 40 字节，没有字符串结束标志 '\0'
         *
         *  实验显示 ：uninitialized_fill() 更安全
         *
         *  memset() 操作的内存就存在读的时候越界访问了
         * */

        // [Test NO. 1]
        std::uninitialized_fill(ptr, &ptr[39], '1');
        cout << "ptr = " << ptr << endl;

        // [Test NO. 2]
        memset(ptrn, '2', 40);
        cout << "ptrn = " << ptrn << endl;

        alloc.deallocate(ptr, 40);
        delete [] ptrn;
    }
    cout << "---[End] Container::allocator_t() --------" << endl;
    return 0;
}


