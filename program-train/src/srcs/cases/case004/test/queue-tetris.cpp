/*
 * Progarm Name: queue-tetris.cpp
 * Created Time: 2017-02-17 10:25:09
 * Last modified: 2017-02-23 14:25:14
 * @author: minphone.linails linails@foxmail.com 
 */

#include "queue-tetris.hpp"
#include "queue-tetris-def.hpp"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <functional>

using std::cout;
using std::endl;
using std::string;

int queue_tetris_test(void)
{
    int ret = 0;

    {
        cout << "QueueTetris<int> ..." << endl;
        int x;
        QueueTetris<int> qti;

        auto empty_check = [](QueueTetris<int> &qti){
            if(0 == qti.is_empty()){
                cout << "qti is empty !" << endl;
            }else{
                cout << "qti is not empty  - size : " << qti.size() << endl;
            }
        };

        empty_check(qti);

        qti.push(0);
        empty_check(qti);

        if(0 == qti.pop(x)){
            cout << "pop success !" << endl;
            cout << "x = " << x << endl;
            empty_check(qti);
        }else{
            cout << "pop failed !" << endl;
            empty_check(qti);
        }


        qti.push(0);
        qti.push(0);
        qti.push(0);
        qti.push(1);
        qti.push(0);
        qti.push(0);
        empty_check(qti);

        auto pop_expec = [&qti, &empty_check](int expec, int &x){
            if(0 == qti.pop(expec, x)){
                cout << "pop success !" << endl;
                cout << "x = " << x << endl;
                empty_check(qti);
            }else{
                cout << "pop failed !" << endl;
                empty_check(qti);
            }
        };

        pop_expec(1, x);
        pop_expec(2, x);
        pop_expec(0, x);
    }
    cout << "---------------------------" << endl;
    {
        cout << "QueueTetris<string> ..." << endl;
        string x;
        QueueTetris<string> qti;

        auto empty_check = [](QueueTetris<string> &qti){
            if(0 == qti.is_empty()){
                cout << "qti is empty !" << endl;
            }else{
                cout << "qti is not empty  - size : " << qti.size() << endl;
            }
        };

        empty_check(qti);

        qti.push("0");
        empty_check(qti);

        if(0 == qti.pop(x)){
            cout << "pop success !" << endl;
            cout << "x = " << x << endl;
            empty_check(qti);
        }else{
            cout << "pop failed !" << endl;
            empty_check(qti);
        }


        qti.push("0");
        qti.push("0");
        qti.push("0");
        qti.push("1");
        qti.push("0");
        qti.push("0");
        empty_check(qti);

        auto pop_expec = [&qti, &empty_check](string expec, string &x){
            if(0 == qti.pop(expec, x)){
                cout << "pop success !" << endl;
                cout << "x = " << x << endl;
                empty_check(qti);
            }else{
                cout << "pop failed !" << endl;
                empty_check(qti);
            }
        };

        pop_expec("1", x);
        pop_expec("2", x);
        pop_expec("0", x);
    }
    cout << "---------------------------" << endl;
    {
        cout << "QueueTetris<int> ..." << endl;
        int x;
        QueueTetris<int> qti;

        auto empty_check = [](QueueTetris<int> &qti){
            if(0 == qti.is_empty()){
                cout << "qti is empty !" << endl;
            }else{
                cout << "qti is not empty  - size : " << qti.size() << endl;
            }
        };

        auto pop_ = [&qti, &empty_check](int &x, bool flag){
            if(0 == qti.pop(x, flag)){
                cout << "pop success !" << endl;
                cout << "x = " << x << endl;
                empty_check(qti);
            }else{
                cout << "pop failed !" << endl;
                empty_check(qti);
            }
        };

        empty_check(qti);

        qti.push(0);
        empty_check(qti);

        pop_(x, false);
        cout << "--" << endl;
        pop_(x, true);
        cout << "--" << endl;
        pop_(x, false);
        pop_(x, false);
        pop_(x, true);

    }
    cout << "---------------------------" << endl;
    return ret;
}

int tetris_test(void)
{
    int ret = 0;

    {
        /*
         * init ...
         * */
        int dev     = 0;
        int left    = 0;
        int right   = 0;

        Tetris<int> *ti = nullptr;
        cout << "Tetris<int> *ti" << endl;

        vector<int> devs;
        map<int, vector<int> > data;

        for(int i=0; i<10; i++){
            devs.clear();   for(int j=0 + 10*i ; j<10 + 10*i; j++) devs.push_back(j+1);
            data.insert(make_pair(i+1, devs));
        }

        for(auto &u : data){
            printf("tid = %.2d - ", u.first);
            for(auto i : u.second) printf(" %3.d", i);
            cout << endl;
        }

        auto trigger = [](int tid, int right) -> int{
            printf("[trigger] ... : tid = %d - right = %d\n", tid, right);
            return 0;
        };

#if 0
        ti = new Tetris<int>(data);
#else
        ti = new Tetris<int>();
        for(auto &u : data){
            pair<int, vector<int> > pair_d = u;
            ti->add_tid(pair_d);
        }
#endif

        ti->register_trigger_cb(trigger);


        /*
         * Testing ...
         * */
        cout << "---------Testing 01--------" << endl;
        {
            #if 0
            left = 1;
            ti->push_left(10, left); ti->print_info(1);
            left = 0;
            ti->push_left(10, left); ti->print_info(1);
            {
                left = 0;
                for(int i=0; i<10; i++) ti->push_left(i+1, left); ti->print_info(1);
                left = 1;
                for(int i=0; i<9; i++) ti->push_left(i+1, left); ti->print_info(1);
            }
            cout << "Line : " << __LINE__ << " File : " << __FILE__<< endl;
            left = 0;
            ti->push_left(10, left); ti->print_info(1);
            #endif
        }
        cout << "---------Testing 02--------" << endl;
        {
            #if 0
            right = 1;
            ti->push_right(1, right); ti->print_info(1);
            ti->push_right(1, right); ti->print_info(1);

            right = 0;
            ti->push_right(1, right); ti->print_info(1);
            ti->push_right(1, right); ti->print_info(1);

            right = 1;
            ti->push_right(1, right); ti->print_info(1);
            ti->push_right(1, right); ti->print_info(1);
            ti->push_right(1, right); ti->print_info(1);
            #endif
        }
        cout << "---------Testing 03--------" << endl;
        {
            /*
             * 这个测试假设 dev = 1 故障，无法 report
             * */
            #if 0
            right = 1;  ti->push_right(1, right); ti->print_info(1);

            left = 1;   ti->push_left(10, left); ti->print_info(1);
            for(int i=1; i<9; i++) ti->push_left(i+1, left); ti->print_info(1);

            right = 0;  ti->push_right(1, right); ti->print_info(1);
            right = 1;  ti->push_right(1, right); ti->print_info(1);

            {
                left = 0;   ti->push_left(2, left); ti->print_info(1);
                left = 1;   ti->push_left(2, left); ti->print_info(1);
                left = 1;   ti->push_left(2, left); ti->print_info(1);
                left = 1;   ti->push_left(2, left); ti->print_info(1);
                left = 1;   ti->push_left(2, left); ti->print_info(1);

                //left = 1;   ti->push_left(2, left); ti->print_info(1);
                left = 1;   for(int i=2; i<9; i++) ti->push_left(i+1, left); ti->print_info(1);
                left = 1;   ti->push_left(10, left); ti->print_info(1);
                cout << "Line : " << __LINE__ << endl;
                left = 0;   for(int i=2; i<9; i++) ti->push_left(i+1, left); ti->print_info(1);
                left = 0;   ti->push_left(10, left); ti->print_info(1);

                /* recover dev = 1 */
                left = 0;   ti->push_left(1, left); ti->print_info(1);
            }
            #endif
        }


        if(nullptr != ti){
            delete ti;
            ti = nullptr;
        }
    }
    cout << "---------------------------" << endl;
    return ret;
}

