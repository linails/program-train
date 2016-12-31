/*
 * Progarm Name: seq-list.cpp
 * Created Time: 2016-08-27 08:43:55
 * Last modified: 2016-12-30 22:01:24
 * @author: minphone.linails linails@foxmail.com 
 */

#include "seq-list.hpp"
#include "seq-list-def.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using std::cout;
using std::endl;
using std::string;
using std::vector;

tSeqList::tSeqList()
{
}

tSeqList::~tSeqList()
{
}

int  tSeqList::tseqlist_main(int argc, char **argv)
{
    int ret = 0;

    cout << "tseqlist_main ..." << endl;

    assert(-1 != ret);
    ret = this->seqlist();

    return ret;
}

int  tSeqList::seqlist(void)
{
    int ret = 0;

    {
        SeqList<int> sl;
        int a = 10;

        cout << "sl.size() : " << sl.size() << endl;
        cout << "sl.length() : " << sl.length() << endl;

        sl.insert(0, a); sl.output();

        sl.input(20);
        sl.input(30);
        sl.input(40);
        sl.output();

        sl.remove(0, a); sl.output();
        sl.remove(0, a); sl.output();
        sl.remove(0, a); sl.output();
        sl.remove(0, a); sl.output();
    }
    cout << "--------------------------------------" << endl;
    {
        SeqDrived sd;

        string name;
        sd.get_name(name);
        cout << "sd.get_name() : " << name << endl;
    }

    return ret;
}

