/*
 * Progarm Name: mos.hpp
 * Created Time: 2016-11-25 09:24:31
 * Last modified: 2016-11-27 10:54:46
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MOS_HPP_
#define _MOS_HPP_

#include <string>

using std::string;

class Mos{
public:
    Mos();
    ~Mos();
    string pwd(void);
    int pwd(string &cpath);
private:
};

#endif //_MOS_HPP_

