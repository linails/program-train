/*
 * Progarm Name: mos.hpp
 * Created Time: 2016-11-25 09:24:31
 * Last modified: 2017-03-15 18:59:06
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
    string home(void);
    int  pwd(string &cpath);
    int  home(string &home);
private:
};

#endif //_MOS_HPP_

