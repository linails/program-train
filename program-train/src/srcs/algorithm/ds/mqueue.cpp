/*
 * Progarm Name: mqueue.cpp
 * Created Time: 2017-01-03 15:01:53
 * Last modified: 2017-01-13 17:59:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mqueue.hpp"
#include "mqueue-def.hpp"
#include "circle-queue-def.hpp"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

mQueue::mQueue()
{
}

mQueue::~mQueue()
{
}

int  mQueue::mqueue_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->circ_queue(); assert(-1 != ret);

    return ret;
}

int  mQueue::circ_queue(void)
{
    cout << "--------------------------------------" << endl;

    CircQueue<int> iq(5);
    int a = 0;

    iq.en_queue(1);
    iq.en_queue(2);
    iq.en_queue(3);

    iq.output();

    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();

    iq.en_queue(5);
    iq.output();
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();

    iq.en_queue(1);
    iq.output();
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();

    iq.en_queue(10);
    iq.en_queue(11);
    iq.en_queue(12);
    iq.en_queue(13);
    iq.en_queue(14);
    iq.output();

    iq.en_queue(15);
    iq.output();

    cout << "--------------------------------------" << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();

    iq.de_queue(a); cout << "a = " << a << endl;

    cout << "--------------------------------------" << endl;
    iq.en_queue(20);
    iq.en_queue(21);
    iq.en_queue(22);
    iq.en_queue(23);
    iq.en_queue(24);
    iq.output();

    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();
    iq.en_queue(30);
    iq.output();

    iq.en_queue(40);
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();

    iq.de_queue(a); cout << "a = " << a << endl;
    iq.output();
    return 0;
}


