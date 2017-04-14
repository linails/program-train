/*
 * Progarm Name: user-class.hpp
 * Created Time: 2017-03-31 11:09:33
 * Last modified: 2017-03-31 13:05:09
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _USER_CLASS_HPP_
#define _USER_CLASS_HPP_

#include "event-mecha.hpp"

class UserClass{
public:
    UserClass(){};
    ~UserClass(){};
    int  set(int data){ this->m_data = data; return 0; }
    int  get(void){ return this->m_data; };
private:
    int  m_data = -1;
};

#endif //_USER_CLASS_HPP_

