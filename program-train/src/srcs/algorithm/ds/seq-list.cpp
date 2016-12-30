/*
 * Progarm Name: seq-list.cpp
 * Created Time: 2016-08-27 08:43:55
 * Last modified: 2016-12-30 17:59:34
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

    //SeqList<int> sl;

    //cout << "sl.size() : " << sl.size() << endl;

    return ret;
}

