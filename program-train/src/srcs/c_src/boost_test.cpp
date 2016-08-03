/*
 * Progarm Name: boost_test.cpp
 * Created Time: 2016-03-25 16:52:20
 * Last modified: 2016-08-03 13:37:56
 * @author: minphone.linails linails@foxmail.com 
 */

#include "boost_test.h"
#include <iostream>
#include <cstdio>
#include <tuple>
#include <bitset>
#include <vector>

using namespace std;
//using namespace boost;

static void tuple_test(void);

/*boost test*/
void boost_test(void)
{
    cout << "boost test ....." << endl;
    tuple_test();
}

tuple<int,string> tg(1,"hello");

void tuple_test(void)
{
    get<1>(tg) = "nice to you";
    cout << "get<1>(tg) : " << get<1>(tg) << endl;
    cout << "--------------------------------" << endl;
    {
    tuple<int,string> t1(1,"hello");
    tuple<int,string> t2;
    t2 = t1;

    cout << "get<0>(t2) : " << get<0>(t2) << endl;
    cout << "get<1>(t2) : " << get<1>(t2) << endl;
    tuple<int,string> t3(3,"nice");
    t2 = t3;
    cout << "get<0>(t2) : " << get<0>(t2) << endl;
    cout << "get<1>(t2) : " << get<1>(t2) << endl;
    get<1>(t2) = "nice to you";
    cout << "get<1>(t2) : " << get<1>(t2) << endl;
    }
    cout << "--------------------------------" << endl;
    {
        vector<tuple<bitset<10>,bitset<10>,float> > v1;

        v1.push_back(make_tuple(0x01,0x02,0.0001));
        v1.push_back(make_tuple(0x01,0x02,0.0001));
        v1.push_back(make_tuple(0x01,0x03,0.0001));

        for(auto iter = v1.begin();
                 iter!= v1.end(); iter++){
            cout << "v1 : " << get<0>(*iter).to_string() << " "
                 << get<1>(*iter).to_string() << " "
                 << get<2>(*iter) << endl;
        }
    }
    cout << "--------------------------------" << endl;
    {
        vector<tuple<vector<float>,vector<float>,float> > v1;

        tuple<vector<float>,vector<float>,float> t1;
        get<0>(t1).push_back(0.0001);
        get<0>(t1).push_back(0.0002);
        get<0>(t1).push_back(0.0003);
        get<0>(t1).push_back(0.0004);
        get<1>(t1).push_back(0.0011);
        get<1>(t1).push_back(0.0012);
        get<1>(t1).push_back(0.0013);
        get<1>(t1).push_back(0.0014);
        get<2>(t1) = 0.0201;

        v1.push_back(t1);

        for(auto iter = v1.begin();
                 iter!= v1.end(); iter++){
            cout << "ant : " << endl;
            for(auto iter1 = get<0>(*iter).begin();
                     iter1!= get<0>(*iter).end(); iter1++){
                printf(" - %.6f" ,*iter1);
            }
            cout << endl;
            cout << "sec : " << endl;
            for(auto iter1 = get<1>(*iter).begin();
                     iter1!= get<1>(*iter).end(); iter1++){
                printf(" - %.6f" ,*iter1);
            }
            cout << " cfd : " << get<2>(*iter) << endl;
        }

        //t1.clear();
    }
}



