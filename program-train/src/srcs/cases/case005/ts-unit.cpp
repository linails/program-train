/*
 * Progarm Name: ts-unit.cpp
 * Created Time: 2017-06-26 10:29:32
 * Last modified: 2017-06-26 17:04:43
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-unit.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

using std::cout;
using std::endl;

TsUnit::TsUnit(const char *unit)
{
    memcpy(this->m_buf, unit, 188);

    assert(0x47 == this->m_buf[0]);
    if(0x47 != this->m_buf[0]){
        cout << "[Error] TsUnit false!" << endl;
    }
}

TsUnit::~TsUnit()
{
}

