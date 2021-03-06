/*
 * Progarm Name: seq-list.hpp
 * Created Time: 2016-12-30 12:18:52
 * Last modified: 2017-01-04 17:25:19
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SEQ_LIST_HPP_
#define _SEQ_LIST_HPP_

#include <string>
#include "seq-list-def.hpp"

using std::string;

class SeqBase{
public:
    SeqBase(){};
    virtual ~SeqBase(){};
    virtual int get_name(string &s) = 0;
    //virtual int size(void) = 0;
};

class SeqDrived : public SeqBase{
public:
    SeqDrived(){};
    ~SeqDrived(){};
    virtual int get_name(string &s){s="seq-drived"; return 0;};
};

class tSeqList{
public:
    tSeqList();
    ~tSeqList();
    int  tseqlist_main(int argc, char **argv);
private:
    int  seqlist(void);
    int  seqlist_union(SeqList<int> &la, SeqList<int> &lb);
    int  seqlist_intersection(SeqList<int> &la, SeqList<int> &lb);
    int  singlelist(void);
    int  circlelist(void);
    int  josephus(void);
};

#endif //_SEQ_LIST_HPP_

