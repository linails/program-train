/*
 * Progarm Name: jump.hpp
 * Created Time: 2017-03-30 11:00:23
 * Last modified: 2017-03-30 13:59:38
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _JUMP_HPP_
#define _JUMP_HPP_

#include <functional>
#include <setjmp.h>

class VisitClass{
public:
    VisitClass(jmp_buf &jmp);
    ~VisitClass();
    int  operator()(int d) const;
private:
    jmp_buf     &m_jmp;
};

class Jumper{
public:
    Jumper();
    ~Jumper();
    int  main(int argc, char **argv);
private:
    int  case_01(void);
    int  case_02(void);
    int  case_03(void);
private:
    int  cb_user(std::function<int (int)> visit);
private:
    static int  visit_global(int d);
private:
    static jmp_buf jmp;
};

#endif //_JUMP_HPP_

