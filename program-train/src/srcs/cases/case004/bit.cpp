/*
 * Progarm Name: bit.cpp
 * Created Time: 2017-02-17 15:25:34
 * Last modified: 2017-02-17 17:20:42
 * @author: minphone.linails linails@foxmail.com 
 */

#include "bit.hpp"
#include <iostream>
#include "binditem-tetris.hpp"
#include <cassert>

using std::cout;
using std::endl;

Bit::Bit()
{
}

Bit::~Bit()
{
}

int  Bit::bit_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->queue_tetris_test(); assert(-1 != ret);

    ret = this->tetris_test(); assert(-1 != ret);

    ret = this->bi_tetris_test(); assert(-1 != ret);

    return ret;
}

int  Bit::queue_tetris_test(void)
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
    return ret;
}

int  Bit::tetris_test(void)
{
    int ret = 0;

    Tetris<int> *ti = nullptr;

    cout << "---------------------------" << endl;
    return ret;
}

int  Bit::bi_tetris_test(void)
{
    int ret = 0;

    BindItemTetris binditem_tetris;

    cout << "---------------------------" << endl;
    return ret;
}


