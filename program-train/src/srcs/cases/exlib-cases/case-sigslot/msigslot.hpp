/*
 * Progarm Name: msigslot.hpp
 * Created Time: 2017-09-28 11:20:40
 * Last modified: 2017-09-28 13:04:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSIGSLOT_HPP_
#define _MSIGSLOT_HPP_

#include <string>

using std::string;

class Msigslot{
public:
    Msigslot();
    ~Msigslot();
    int  main(int argc, char **argv);
private:
    int  light_switch(void);
};

//---------------------------------------------------------------

#include "sigslot/sigslot.h"

using namespace sigslot;

class Switch{
public:
    Switch();
    ~Switch();
    signal0<> clicked;
    /*
     * signal0 表示不带参数，signalx 中的 x 为多少就可以带几个参数
     * x 取值为 0 ~ 8
     *
     * signal 称为信号，用来发出信号，而继承 has_slots<> 的类称为 slot，是信号的处理函数
     * */
};

class Light : public has_slots<>{
public:
    Light(int state, const char *light_name);
    ~Light();
    void turn_on(void);
    void turn_off(void);
    void toggle(void);
    void disp_state(void);
private:
    int     m_state;
    string  m_light_name;
};

#endif //_MSIGSLOT_HPP_

