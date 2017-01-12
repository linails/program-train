/*
 * Progarm Name: mqueue.cpp
 * Created Time: 2017-01-03 15:01:53
 * Last modified: 2017-01-12 13:27:55
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

    CircQueue<int> iq(10);

    iq.output();

    return 0;
}


