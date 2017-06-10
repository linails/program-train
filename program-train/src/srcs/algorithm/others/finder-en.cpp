/*
 * Progarm Name: finder-en.cpp
 * Created Time: 2017-06-10 07:15:23
 * Last modified: 2017-06-10 08:35:32
 * @author: minphone.linails linails@foxmail.com 
 */

#include "finder-en.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cassert>
#include <vector>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::vector;
using std::list;

FinderEn::FinderEn()
{
    this->m_seqs.insert(make_pair("2", 1));
    this->m_seqs.insert(make_pair("3", 2));
    this->m_seqs.insert(make_pair("4", 3));
    this->m_seqs.insert(make_pair("5", 4));
    this->m_seqs.insert(make_pair("6", 5));
    this->m_seqs.insert(make_pair("7", 6));
    this->m_seqs.insert(make_pair("8", 7));
    this->m_seqs.insert(make_pair("9", 8));
    this->m_seqs.insert(make_pair("10",9));
    this->m_seqs.insert(make_pair("J", 10));
    this->m_seqs.insert(make_pair("Q", 11));
    this->m_seqs.insert(make_pair("K", 12));
    this->m_seqs.insert(make_pair("A", 13));
}

FinderEn::~FinderEn()
{
}

int  FinderEn::main(int argc, char **argv)
{

    cout << "FinderEn::main ..." << endl;

    int ret = 0;

    while(1){
        sleep(1);

        ret = this->input(); assert(-1 != ret);

        ret = this->fsort(); assert(-1 != ret);

        ret = this->pairs_forword(); assert(-1 != ret);

        ret = this->output(); assert(-1 != ret);
    }

    return ret;
}

int  FinderEn::input(void)
{
    string  istr;

    cin >> istr;

    cout << "istr = " << istr << endl;

    vector<string> units;

    string s;
    for(auto u : istr){

        if(u != ','){
            s += u;
        }else{
            units.push_back(s);
            s.clear();
        }
    }
    units.push_back(s);

    for(auto u: units){
        printf("%d -> %s\n", this->m_seqs[u], u.c_str());
        this->m_result.push(make_pair(this->m_seqs[u], u));
    }

    return 0;
}

int  FinderEn::fsort(void)
{
    /* 
     * ! 用 list 进行 sort 不行
     * */
    vector<pair<int, string> > sort_buf;

    auto greater = [](const pair<int, string> &a, const pair<int, string> &b){
        return a.first < b.first;
    };

    while(false == this->m_result.empty()){
        sort_buf.push_back(this->m_result.top());
        this->m_result.pop();
    }

    std::sort(sort_buf.begin(), sort_buf.end(), greater);

    for(auto &u : sort_buf){
        printf(" * %d -> %s\n", u.first, u.second.c_str());
        this->m_result.push(u);
    }

    return 0;
}

int  FinderEn::pairs_forword(void)
{
    stack<pair<int, string> >   singles;
    stack<pair<int, string> >   pairs;

    while(false == this->m_result.empty()){
        pair<int, string> &u = this->m_result.top();

        if(true == singles.empty()) singles.push(u);
        else{
            if(singles.top().first == u.first){
                pairs.push(singles.top());
                pairs.push(u);
                singles.pop();
            }else{
                singles.push(u);
            }
        }

        this->m_result.pop();
    }

    list<pair<int, string> > result;
    while(false == singles.empty()){
        result.push_back(singles.top());
        singles.pop();
    }
    while(false == pairs.empty()){
        result.push_back(pairs.top());
        pairs.pop();
    }

    for(auto &u : result) this->m_result.push(u);

    return 0;
}

int  FinderEn::output(void)
{
    vector<string> result;

    while(false == this->m_result.empty()){
        pair<int, string> &u = this->m_result.top();

        printf(" - %d -> %s\n", u.first, u.second.c_str());
        result.push_back(u.second);

        this->m_result.pop();
    }

    cout << "Result : ";
    for(auto s : result) cout << s << " ";
    cout << endl;

    return 0;
}

