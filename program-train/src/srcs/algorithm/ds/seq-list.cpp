/*
 * Progarm Name: seq-list.cpp
 * Created Time: 2016-08-27 08:43:55
 * Last modified: 2017-01-04 17:25:46
 * @author: minphone.linails linails@foxmail.com 
 */

#include "seq-list.hpp"
#include "seq-list-def.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "single-list-def.hpp"
#include "circle-list-def.hpp"

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

    //ret = this->seqlist(); assert(-1 != ret);

    //ret = this->singlelist(); assert(-1 != ret);

    ret = this->circlelist(); assert(-1 != ret);

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
    cout << "--------------------------------------" << endl;
    {
        SeqList<int> la, lb;

        la.input(10);
        la.input(20);
        la.input(30);
        la.input(40);
        la.output();

        lb.input(11);
        lb.input(21);
        lb.input(31);
        lb.output();

        cout << "seqlist union(la, lb) : " << endl;
        ret = this->seqlist_union(la, lb);
        la.output(); cout << endl;
        

        lb.input(12);
        lb.input(22);
        lb.input(32);
        lb.output();
        cout << "seqlist ntersection(la, lb) : " << endl;
        ret = this->seqlist_intersection(la, lb);
        la.output();
    }

    return ret;
}

int  tSeqList::seqlist_union(SeqList<int> &la, SeqList<int> &lb)
{
    /* 
     *  合并顺序表 la 和 lb, 结果存在与 la 中，重复元素只留一个
     * */

    int ret = 0;

    int remain = la.size() - la.length();

    cout << "remain : " << remain << endl;

    if(remain >= lb.length()){
        int len_b = lb.length();

        for(int i=0; i<len_b; i++){
            int *data = lb.get_data(i);

            if(NULL != data){
                if(-1 == la.search(*data)){
                    la.insert(la.length(), *data);
                }
            }else{
                cout << "lb.get_data error !" << endl;
            }
        }
    }else{
        ret = -1;
        cout << "la have no other space to union lb unit" << endl;
    }

    return ret;
}

int  tSeqList::seqlist_intersection(SeqList<int> &la, SeqList<int> &lb)
{
    /* 
     * 求取顺序表中的 la 和 lb 的共有元素，结果存于 la 中
     * */
    int ret = 0;

    int i = 0;
    int cn = la.length();

    while(i < cn){
        int *data = la.get_data(i);
        if(NULL != data){
            if(-1 == lb.search(*data)){
                int t = 0;
                la.remove(i, t);
                cn--;
            }else{
                i++;
            }
        }
    }

    return ret;
}

int  tSeqList::singlelist(void)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
        cout << " ... singlelist ... " << endl;

        SingleList<int> sl;
        sl.input(1);
        sl.input(2);
        sl.input(3);

        sl.output();
    }
    cout << "--------------------------------------" << endl;
    {
        int a = 10;
        SingleList<int> sl(a);

        sl.input(3);
        sl.input(4);
        sl.input(5);
        sl.input(6);
        sl.input(7);
        sl.output();

        sl.remove(3, a);
        sl.output();

        sl.remove(1, a);
        sl.output();
    }
    cout << "--------------------------------------" << endl;
    {
        SingleList<int> sla;
        SingleList<int> slb;

        for(int i=0; i<10; i++) sla.input(i*1);
        for(int i=0; i<10; i++) slb.input(i*2);

        sla.output();
        slb.output();

        //SingleList<int> slc(sla);

        SingleList<int> slc;
        slc = sla;
        slc.output();

        SingleList<int> sld(slb);
        sld.output();

    }

    return ret;
}

int  tSeqList::circlelist(void)
{
    int ret = 0;

    cout << "--------------------------------------" << endl;
    {
        CircList<int> cl;
    }

    return ret;
}

int  tSeqList::josephus(void)
{
    int ret = 0;

    return ret;
}

