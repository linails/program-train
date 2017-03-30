/*
 * Progarm Name: jump.hpp
 * Created Time: 2017-03-30 11:00:23
 * Last modified: 2017-03-30 12:12:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _JUMP_HPP_
#define _JUMP_HPP_

#include <functional>

class Jumper{
public:
    Jumper();
    ~Jumper();
    int  main(int argc, char **argv);
private:
    int  case_01(void);
    int  case_02(void);
private:
    int  cb_user(std::function<int (int)> visit);
};

#endif //_JUMP_HPP_

