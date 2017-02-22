/*
 * Progarm Name: bit.cpp
 * Created Time: 2017-02-17 15:25:34
 * Last modified: 2017-02-22 16:23:58
 * @author: minphone.linails linails@foxmail.com 
 */

#include "bit.hpp"
#include <iostream>
#include <cassert>
#include "bt-test.hpp"
#include "queue-tetris.hpp"

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
    return ::queue_tetris_test();
}

int  Bit::tetris_test(void)
{
    return ::tetris_test();
}

int  Bit::bi_tetris_test(void)
{
    return bt_test();
}


