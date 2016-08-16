/*
 * Progarm Name: mutating-algo.cpp
 * Created Time: 2016-08-16 15:52:36
 * Last modified: 2016-08-16 22:16:06
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mutating-algo.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

void mutating_algo(void)
{
    cout << "----------- mutating_algo -----------" << endl;
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(5);
        v.push_back(3);
        v.push_back(6);
        v.push_back(4);
        v.push_back(2);
        v.push_back(7);

        cout << "v : " ;
        for(auto unit : v) cout << unit << " "; cout << endl;

        list<int> l;
        l.push_back(2);
        l.push_back(2);
        l.push_back(2);
        l.push_back(2);
        l.push_back(2);

        if(l.size() >= v.size()){
            cout << "copy : l->v" << endl;
            /* 从 v 中复制到 l，不过前提条件是 l 有足够的容量存储 v 
             * 复制的时候，l 不会自动扩大容量 */
            copy(v.begin(), v.end(), l.begin());
        }else{
            cout << "l.size() < v.size()" << endl;
        }

        cout << "l : " ;
        for(auto unit : l) cout << unit << " "; cout << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> v;
        for(int i=0; i<10; i++) v.push_back(i+1);

        /* 将前面三个元素拷贝到最后 */
        copy_backward(v.begin(), v.begin()+3, v.end());

        cout << "v : ";
        for(auto unit : v) cout << unit << " "; cout << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        int a = 10;
        int b = 20;

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        swap(a, b);
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        int a = 10;
        int b = 20;

        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        iter_swap(&a, &b);
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        vector<int> v1;

        v1.push_back(10);
        v1.push_back(11);
        v1.push_back(12);

        cout << "v1 : " << v1[0] << " " << v1[1] << endl;

        auto iter = v1.begin();
        cout << "*iter = " << *iter << endl;
        cout << "*++iter = " << *++iter << endl;

        iter = v1.begin();
        cout << "*iter = " << *iter << endl;
        cout << "*iter++ = " << *iter++ << endl;

        iter = v1.begin();
        /* iter_swap : 注意编译器查找参数的方向 */
        iter_swap(iter, iter+1);
        //iter_swap(iter, iter++);

        cout << "after iter_swap" << endl;
        cout << "v1 : " << v1[0] << " " << v1[1] << endl;

        int c = 1;
        cout << "c = " << c << endl;
        cout << "c++ = " << c++ << endl;
        cout << "c = " << c << endl;
        cout << "++c = " << ++c << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 函数读取参数方向：从右向左 */
        auto func = [](int *a, int *b)
        {
            cout << "*a = " << *a << endl;
            cout << "*b = " << *b << endl;
        };

        int a[2] = {10, 20};

        cout << "a : " << a[0] << " " << a[1] << endl;

        int *p = a;
        func(p, ++p);

        p = a;
        func(p, p++);
    }
    cout << "-----------------------------------------" << endl;
    {
        auto f = [](vector<int> &v, const char *str){
            cout << str << " : " ;
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        vector<int> v1;
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);


        vector<int> v2;
        for(int i=0; i<10; i++) v2.push_back(i);

        f(v1, "v1"); f(v2, "v2");
        /* swap_ranges算法用于进行两个迭代器区间元素的交换：
         * [first1, last1)迭代器区间的元素，与
         * [first2, first2 + (last1 - first1)]迭代器区间元素交换*/
        swap_ranges(v1.begin(), v1.end(), v2.begin());
        cout << "after swap_ranges" << endl;
        f(v1, "v1"); f(v2, "v2");
    }
    cout << "-----------------------------------------" << endl;
    {
        auto f = [](vector<int> &v, const char *str){
            cout << str << " : " ;
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        vector<int> v1;
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(2);


        vector<int> v2;
        for(int i=0; i<10; i++) v2.push_back(i);

        f(v1, "v1"); f(v2, "v2");

        auto square = [](int x){ return x * x; };

        /* transform算法用于实行容器元素的变化操作：
         * 将迭代器[first, last)中元素，执行一元函数对象op操作，
         * 变换后的结果放在[result, result+(last-first))区间中*/
        transform(v1.begin(), v1.end(), v2.begin(), square);
        f(v1, "v1"); f(v2, "v2");
    }
    cout << "-----------------------------------------" << endl;
    {
        auto f = [](vector<int> &v, const char *str){
            cout << str << " : " ;
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        vector<int> v1;
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(4);
        v1.push_back(2);
        v1.push_back(2);
        v1.push_back(4);

        f(v1, "v1");
        /* replace 算法将指定元素值替换为新值
         * 将迭代器区间[first, last)中值为 old_value 的元素全部替换为 new_value 值*/
        replace(v1.begin(), v1.end(), 2, 10);
        f(v1, "v1");

        vector<tuple<int, string> > v2;
        v2.push_back(make_tuple(1, "nice"));
        v2.push_back(make_tuple(1, "nice"));
        v2.push_back(make_tuple(2, "hello"));
        v2.push_back(make_tuple(1, "nice"));
        v2.push_back(make_tuple(2, "hello"));
        v2.push_back(make_tuple(1, "nice"));
        v2.push_back(make_tuple(1, "nice"));
        v2.push_back(make_tuple(2, "hello"));
        v2.push_back(make_tuple(2, "hello"));
        v2.push_back(make_tuple(1, "nice"));

        auto f2 = [](vector<tuple<int, string> > &v, const char *str){
            cout << str << " : " << endl;
            for(auto &unit : v){
                cout << get<0>(unit) << " - " << get<1>(unit) << endl;
            }
        };

        f2(v2, "v2");
        replace(v2.begin(), v2.end(), make_tuple(1, "nice"), make_tuple(5, "world"));
        f2(v2, "v2");

        auto f3 = [](tuple<int, string> &unit){
            if(get<1>(unit) == "world") return true; 
        };

        replace_if(v2.begin(), v2.end(), f3, make_tuple(8, "go"));
        f2(v2, "v2");
    }
}


