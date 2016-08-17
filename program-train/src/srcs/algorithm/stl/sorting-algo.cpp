/*
 * Progarm Name: sorting-algo.cpp
 * Created Time: 2016-08-16 22:16:56
 * Last modified: 2016-08-17 14:53:29
 * @author: minphone.linails linails@foxmail.com 
 */

#include "sorting-algo.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

void sorting_algo(void)
{
    /* 排序算法一般要求容器提供随机访问迭代器，一般适用于序列容器，
     * 如vector, list, string 但不适用于内部数据结构较为复杂的关联容器，
     * 如set, map, hash_set, hash_map 等*/
    cout << "----------- sorting_algo -----------" << endl;
    {
        vector<int> v;
        v.push_back(38);
        v.push_back(26);
        v.push_back(15);
        v.push_back(17);
        v.push_back(29);
        v.push_back(11);
        v.push_back(32);
        v.push_back(9);
        v.push_back(10);
        v.push_back(60);

        auto f = [](vector<int> &v){
            cout << "v : " ;
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        /* push_heap 算法是将一个元素置入已构成堆的迭代器区间中 */
        f(v);
        push_heap(v.begin(), v.end());
        f(v);
    }
    cout << "-----------------------------------------" << endl;
    {
        /* make_heap 算法重新排列元素顺序，使它们逻辑上构成一个堆 
         *
         * 堆的 push & pop 操作，都是把元素置到容器的最后一个 ,
         * 然后再进行堆操作*/

        vector<int> v;
        v.push_back(5);
        v.push_back(6);
        v.push_back(4);
        v.push_back(8);
        v.push_back(2);
        v.push_back(3);
        v.push_back(7);
        v.push_back(1);
        v.push_back(9);

        auto f = [](vector<int> &v, const char *str){
            cout << str << " : ";
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        f(v, "v");
        make_heap(v.begin(), v.end());
        f(v, "v");

        vector<int> v1;
        for(int i=0; i<9; i++) v1.push_back(i + 1);
        f(v1, "v1");
        make_heap(v1.begin(), v1.end());
        f(v1, "v1");
        pop_heap(v1.begin(), v1.end());
        f(v1, "v1");

        v1.erase(--v1.end());
        f(v1, "v1");
        make_heap(v1.begin(), v1.end());
        f(v1, "v1");

    }
    cout << "-----------------------------------------" << endl;
    {
        /* sort_heap 是一种利用堆进行排序的算法，时间复杂度为 O() */
        auto f = [](vector<int> &v, const char *str){
            cout << str << " : ";
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        auto check = [](vector<int> &v){
            /* is_heap 算法并不是C++标准库算法函数，而是SGI C++ STL 的一个扩展算法
             * 用于判断迭代器区间 [first, last) 元素是否构成一个默认的大根堆 */

            if(true == is_heap(v.begin(), v.end())) {
                cout << "  : v is a heap !" << endl;
            }else{
                cout << "  : v is not a heap !" << endl;
            }
        };

        vector<int> v;
        v.push_back(3);
        v.push_back(9);
        v.push_back(6);
        v.push_back(3);
        v.push_back(12);
        v.push_back(17);
        v.push_back(20);

        f(v, "v"); check(v);
        make_heap(v.begin(), v.end());
        f(v, "v"); check(v);
        sort_heap(v.begin(), v.end());
        f(v, "v"); check(v);

    }
    cout << "-----------------------------------------" << endl;
    {
        /* partial_sort 算法仅对部分元素进行排序，通常用来挑选最小(或最大)的若干元素 
         * 其内部使用堆排序来实现 */
        vector<int> v;
        v.push_back(1);
        v.push_back(4);
        v.push_back(6);
        v.push_back(2);
        v.push_back(3);
        v.push_back(5);
        v.push_back(7);

        auto f = [](vector<int> &v, const char *str){
            cout << str << " : ";
            for(auto unit : v) cout << unit << " ";
            cout << endl;
        };

        f(v, "v");
        partial_sort(v.begin(), v.begin() + 4, v.end());
        f(v, "v");

        /* sort 默认从小到大排序，也可以使用自定义谓词判断函数 */
        sort(v.begin(), v.end());
        f(v, "v");

        sort(v.begin(), v.end(), greater<int>());
        f(v, "v");
    }
    cout << "-----------------------------------------" << endl;
    {
        /* merge 算法将两个具有相同升序方向的有序序列，合并成一个有序序列 */
        int arr1[] = {12, 23, 33};
        int arr2[] = {2, 4, 5, 3, 0, 9, 7, 1};
        int arr3[11] = {0,};

        auto f = [](int *arr, int size, const char *str){
            cout << str << " : ";
            for(int i=0; i<size; i++) cout << arr[i] << " ";
            cout << endl;
        };

        f(arr1, 3, "arr1");
        f(arr2, 8, "arr2");
        f(arr3,11, "arr3");

        sort(arr1, arr1+3);
        sort(arr2, arr2+8);
        merge(arr1, arr1+3, arr2, arr2+8, arr3);

        f(arr1, 3, "arr1");
        f(arr2, 8, "arr2");
        f(arr3,11, "arr3");
    }
    cout << "-----------------------------------------" << endl;
    {
        /* lower_bound 算法用于在有序的区间中查找首个不小于某个值的元素（大于等于某值） */
        int arr[] = {3, 5, 6, 7, 13, 19, 23, 37};
        int len = sizeof(arr)/sizeof(int);

        int *ret = lower_bound(arr, arr+len, 16);
        cout << "lower_bound : " << *ret << endl;
    }
}



