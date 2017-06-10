/*
 * Progarm Name: finder.hpp
 * Created Time: 2017-06-05 14:24:14
 * Last modified: 2017-06-05 15:11:15
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _FINDER_HPP_
#define _FINDER_HPP_

#include <vector>
#include <list>

using std::vector;
using std::list;

class Finder{
public:
    Finder();
    ~Finder();
    int  main(int argc, char **argv);
private:
    int  input(void);
    int  fsort(void);
    int  pairs_forword(void);
    int  output(void);
private:
    vector<char> m_data;
    list<char>   m_data_list;
};

#endif //_FINDER_HPP_

