/*
 * Progarm Name: non-mutating-algo.cpp
 * Created Time: 2016-08-14 10:33:17
 * Last modified: 2017-01-18 22:47:00
 */

#include "non-mutating-algo.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <list>
#include <string>

using namespace std;

void non_mutating_algo(void)
{

    /* 逐元素循环提交处理的     for_each
     * 元素查找的               find     | find_if  | adjacent_find | find_first_of
     * 用于统计元素个数的       count    | count_if 
     * 两序列匹配比较           mismatch | equal 
     * 子序列搜索               search   | search_n | find_end
     * */

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
        cout << " ** find_if struct{} data ** " << endl;
        typedef struct{
            int id;
            string s;
        }Data_t;

        vector<Data_t> v;

        Data_t data[] = {
            {1, "s1"},
            {2, "s2"},
            {3, "s3"},
            {4, "s4"},
            {5, "s5"},
            {6, "s6"},
            {7, "s7"}
        };

        for(size_t i=0; i<sizeof(data)/sizeof(Data_t); i++){
            v.push_back(data[i]);
        }

        cout << "List v :" << endl;
        for(auto &u : v){
            cout << "u : " << u.id << " - " << u.s << endl;
        }
        cout << endl;

        Data_t orig_data = {3, "s3"};

        auto func = [&orig_data](Data_t d){
            if(orig_data.id == d.id){
                return 1; // find it
            }else{
                return 0;
            }
        };

        auto iter = find_if(v.begin(), v.end(), func);

        if(iter == v.end()){
            cout << "find_if nothing !" << endl;
        }else{
            cout << "find : " << iter->id << " - " << iter->s << endl;
        }

    }
    cout << "-----------------------------------------" << endl;
    {
        int index[] = {0, 1, 2, 3, 4, 5, 6, 7};
        vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.push_back(5);
        v.push_back(2);
        v.push_back(7);

        for(auto id : index){
            cout << "id : " << id << endl;

            /* 
             * find_i 定义在内部，对 id 进行引用捕获
             * */
            auto find_i = [&id](int i){
                if(id == i){
                    return 1; // find it
                }else{
                    return 0;
                }
            };

            auto iter = find_if(v.begin(), v.end(), find_i);

            if(iter == v.end()){
                cout << "find nothing !" << endl;
            }else{
                cout << "find : " << *iter << endl;
            }

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
        //find_if

        struct TestData{
            int     a;
            int     b;
            int     c;
            string  d;
            TestData():a(0),b(0),c(0),d("Test"){};
        };
        auto empty = [](TestData &data){
            if(data.d == "Test") return true;
            else return false;
        };

        vector<TestData> vtd;

        TestData td;
        td.a = 0;
        vtd.push_back(td);

        td.d = "1";
        td.a = 1;
        vtd.push_back(td);

        td.d = "2";
        td.a = 2;
        vtd.push_back(td);

        td.d = "3";
        td.a = 3;
        vtd.push_back(td);

        td.d = "Test";
        td.a = 4;
        vtd.push_back(td);

        cout << "vtd : " << endl;
        for(auto &unit : vtd){
            cout << "unit.d : " << unit.d << endl;
        }

        auto iter = find_if(vtd.begin(), vtd.end(), empty);
        if(iter != vtd.end()){
            cout << "Find empty unit" << endl;
            cout << "iter->d : " << iter->d << " - iter->a = " << iter->a << endl;
        }

        iter++;

        iter = find_if(iter, vtd.end(), empty);
        if(iter != vtd.end()){
            cout << "Find empty unit" << endl;
            cout << "iter->d : " << iter->d << " - iter->a = " << iter->a << endl;
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
    cout << "-----------------------------------------" << endl;
    {
        const char *str1 = "abcdef7ghijklnm";
        const char *str2 = "zyx3pr7ys";

        const char *ret  = find_first_of(str1, str1+strlen(str1),
                                   str2, str2+strlen(str2));
        cout << "*ret = " << *ret << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        list<int> l;

        for(int i=0; i<100; i++) l.push_back(i % 20);

        int num = 0;
        int val = 9;

        num = count(l.begin(), l.end(), val);

        cout << "count {val = 9} : " << num << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        string s = "djoianoabbbbabadjijabjoija";

        int num = 0;

        num = count(s.begin(), s.end(), 'a');

        cout << "s : " << s << " - count 'a' : " << num << endl;
    }
    cout << "-----------------------------------------" << endl;
    {
        string str1 = "abcoiuhlngdlk";
        string str2 = "abcoioiujhl";

        auto iter = mismatch(str1.begin(), str1.end(), str2.begin());

        if((iter.first != str1.end()) && (iter.second != str1.end())){
            cout << "*iter.first : " << *iter.first << endl;
            cout << "*iter.second : " << *iter.second << endl;
        }

        if(true == equal(str1.begin(), str1.end(), str2.begin())){
            cout << "equal !" << endl;
        }else{
            cout << "not equal !" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        vector<int> v1;
        v1.push_back(5);
        v1.push_back(6);
        v1.push_back(7);
        v1.push_back(8);
        v1.push_back(9);

        vector<int> v2;
        v2.push_back(7);
        v2.push_back(8);

        /* search 算法函数在一个序列中搜索与另一个序列匹配的子序列 */
        auto iter = search(v1.begin(), v1.end(), v2.begin(), v2.end());

        if(iter != v1.end()){
            cout << "v1 : "; for(auto unit : v1) cout << unit << " "; cout << endl;
            cout << "v2 : "; for(auto unit : v2) cout << unit << " "; cout << endl;
            cout << "v2 started at v1[" << iter - v1.begin() << "]" << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* search_n 算法函数搜索序列中是否有一系列元素值均为某个给定值的子序列 */

        vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(4);
        v.push_back(4);
        v.push_back(4);
        v.push_back(5);

        auto iter = search_n(v.begin(), v.end(), 3, 4);
        if(iter != v.end()){
            cout << "search_n : " << *iter << endl;
        }

        iter = search_n(v.begin(), v.end(), 4, 4);
        if(iter != v.end()){
            cout << "search_n : " << *iter << endl;
        }
    }
    cout << "-----------------------------------------" << endl;
    {
        /* find_end 算法函数在一个序列中搜索出最后一个与另一序列匹配的子序列 
         * 与find_first_of 相对*/
        vector<int> v;
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(6);
        v.push_back(9);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        v.push_back(4);
        v.push_back(6);
        v.push_back(9);

        vector<int> v1;
        v1.push_back(2);
        v1.push_back(3);
        v1.push_back(4);

        auto iter = find_end(v.begin(), v.end(), v1.begin(), v1.end());
        if(iter != v.end()){
            cout << "find_end(v.begin(), v.end(), v1.begin(), v2.end()) : " ;
            for(; iter != v.end(); iter++) cout << *iter << " ";
            cout << endl;
        }
    }
}

