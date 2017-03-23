/*
 * Progarm Name: tester-case001.hpp
 * Created Time: 2017-03-23 17:10:49
 * Last modified: 2017-03-23 17:22:06
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TESTER_CASE001_HPP_
#define _TESTER_CASE001_HPP_

#include <vector>
#include <string>

using std::vector;
using std::string;

class TesterCase001{
public:
    TesterCase001();
    ~TesterCase001();
    int  main(int argc, char **argv);
private:
    int  infinite_loops(void);
    int  child_sibling(void);
private:
    int             m_argc;
    vector<string>  m_argvs;
};

#endif //_TESTER_CASE001_HPP_

