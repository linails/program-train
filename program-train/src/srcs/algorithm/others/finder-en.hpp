/*
 * Progarm Name: finder-en.hpp
 * Created Time: 2017-06-10 07:15:20
 * Last modified: 2017-06-10 08:33:57
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FINDER_EN_HPP_
#define _FINDER_EN_HPP_

#include <map>
#include <string>
#include <stack>

using std::map;
using std::string;
using std::stack;
using std::pair;

class FinderEn{
public:
    FinderEn();
    ~FinderEn();
    int  main(int argc, char **argv);
private:
    int  input(void);
    int  fsort(void);
    int  pairs_forword(void);
    int  output(void);
private:
    map<string, int>            m_seqs;
    stack<pair<int, string> >   m_result;
};

#endif //_FINDER_EN_HPP_

