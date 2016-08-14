/*
 * Progarm Name: non-mutating-algo.cpp
 * Created Time: 2016-08-14 10:33:17
 * Last modified: 2016-08-14 23:02:42
 */

#include "non-mutating-algo.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void non_mutating_algo(void)
{
    cout << "----------- non_mutating_algo -----------" << endl;
    {
        vector<int> v;

        auto print = [](int x){
            cout << x/2 << " "; 
        };

        for(int i=0; i<10; i++) v.push_back(i * 2);

        cout << "for_each(v.begin(), v.end(), print) : " << endl;
        cout << "v[i] : ";

        for_each(v.begin(), v.end(), print);
        
        cout << endl;

        cout << "find(v.begin(), v.end(), 6) : " << endl;
        auto iter = find(v.begin(), v.end(), 6);
        if(iter == v.end()){
            cout << "find nothing !" << endl;
        }else{
            cout << "*iter : " << *iter << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> v;
        for(int i=0; i<10; i++) v.push_back(i);

        auto func = [](int x){return x%3 ? 0 : 1;};

        /* 查找第一个能被3整除的元素 
         * find first*/
        auto iter = find_if(v.begin(), v.end(), func);

        if(iter == v.end()){
            cout << "find_if nothing !" << endl;
        }else{
            cout << "find : " << *iter << endl;
        }

        /* find second */
        iter = find_if(++iter, v.end(), func);
        if(iter == v.end()){
            cout << "find_if nothing !" << endl;
        }else{
            cout << "find : " << *iter << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* adjacent_find 函数 
         * 该函数用于查找相等或满足条件的邻近元素对，有两种用法
         * 1.一个是用于查找相等的连续元素
         * 2.一个是使用二元谓词判断，查找满足条件的邻近元素对
         * */
        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(3);
        v.push_back(8);
        v.push_back(9);
        v.push_back(0);

        auto func = [](vector<int> v){
            cout << "v[i] : ";
            auto funcs = [](int x){cout << x << " ";};
            for_each(v.begin(), v.end(), funcs); cout << endl;
        };

        func(v);

        auto iter = adjacent_find(v.begin(), v.end());
        if(iter == v.end()){
            cout << "have no equal elements" << endl;
        }else{
            cout << "two equal elements : " << *iter << " " << *++iter << endl;
        }

        auto func1 = [](int x, int y)-> bool {
            cout << "x = " << x << " ; y = " << y << endl;
            if(y == x) return true;
            else return false;
        };

        iter = adjacent_find(v.begin(), v.end(), func1);
        if(iter != v.end()){
            cout << "*iter : " << *iter << " - ";
            cout << "*++iter : " << *++iter << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* 查询操作是应用最为广泛的操作，STL主要提供以下查询函数
         * 1.find() : 在单迭代器序列中找出某个值第一次出现的位置
         * 2.find_if() : 在单迭代器序列中找出符合某谓词的第一个元素
         * 3.find_first_of() : 在双迭代器序列中找出一个子序列中某元素第一次出现的位置
         * 4.adjacent_find() : 在单迭代器序列中找出第一次相邻值相等的位置
         * 5.find_end() : 在双迭代器序列中找出一个子序列最后一次出现的位置
         * 6.search() : 在双迭代器序列中找出一个子序列第一次出现的位置
         * 7.search_n() : 在单迭代器序列中找出一个值连续n次出现的位置
         * */

        /*
         * 1.find() : 查询迭代器间对应的元素值，是否有等于val的，若有则返回其迭代器指针；
         *   若无则返回xxx.end()
         *   模板T对应的类必须重载运算符 "operator=="
         * */

        vector<int> v;

        auto init = [](vector<int> &v){ for(int i=0; i<10; i++) v.push_back(i); };

        init(v);

        auto iter = find(v.begin(), v.end(), 4);
        if(iter != v.end()){
            cout << "find *iter = 4 : " << *iter << endl;
        }

        auto greater = [](int x){ return x > 3;};

        iter = find_if(v.begin(), v.end(), greater);
        if(iter != v.end()){
            cout << "find greater(): *iter > 3 : " << *iter << endl;
        }

        vector<int> v1;
        v1.push_back(4);
        v1.push_back(5);
        v1.push_back(7);

        iter = find_first_of(v.begin(), v.end(), v1.begin(), v1.end());
        if(iter != v.end()){
            cout << "find_first_of : " << *iter << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> v1, v2;
        v1.push_back(3);
        v1.push_back(6);
        v1.push_back(9);
        v1.push_back(0);
        v2.push_back(13);
        v2.push_back(19);
        v2.push_back(17);
        v2.push_back(12);
        v2.push_back(10);

        auto print = [](vector<int> &v){
            cout << "v : " ;
            auto f = [](int x){cout << x << " ";};
            for_each(v.begin(), v.end(), f);
            cout << endl;
        };

        print(v1);
        print(v2);

        sort(v1.begin(), v1.end());
        print(v1);
        sort(v2.begin(), v2.end());
        print(v2);

#if 0
        /* fault */
        vector<int> v3;
        merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
        print(v3);
#endif
    }
    cout << "-----------------------------------------" << endl;
    {
        int a1[3] = {20, 23, 39};
        int a2[6] = {2, 9, 13, 18, 26, 30};
        int a3[9];

        auto print = [](int *p, int len){
            cout << "array : ";
            for(int i=0; i<len; i++) cout << p[i] << " ";
            cout << endl;
        };

        print(a1, 3);
        print(a2, 6);
        merge(a1, a1+3, a2, a2+6, a3);
        print(a3, 9);
    }
}

