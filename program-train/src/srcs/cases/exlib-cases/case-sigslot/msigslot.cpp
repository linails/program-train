/*
 * Progarm Name: msigslot.cpp
 * Created Time: 2017-09-28 11:20:32
 * Last modified: 2017-09-28 13:07:09
 * @author: minphone.linails linails@foxmail.com 
 */

#include "msigslot.hpp"
#include <iostream>
#include "sigslot/sigslot.h"
#include <cstdio>

using std::cout;
using std::endl;

Msigslot::Msigslot()
{
}

Msigslot::~Msigslot()
{
}

int  Msigslot::main(int argc, char **argv)
{
    int ret = 0;

    cout << "Msigslot::main() ..." << endl;

    ret = this->light_switch();

    return ret;
}

int  Msigslot::light_switch(void)
{
    Switch sw_all_on;
    Switch sw_all_off;
    Switch sw_toggle0;
    Switch sw_toggle1;
    Light light0(0, "light-0");
    Light light1(1, "light-1");

    /* 
     * connect signal - slot
     * */
    sw_toggle0.clicked.connect(&light0, &Light::toggle);
    sw_toggle1.clicked.connect(&light1, &Light::toggle);
    sw_all_on.clicked.connect(&light0, &Light::turn_on);
    sw_all_on.clicked.connect(&light1, &Light::turn_on);
    sw_all_off.clicked.connect(&light0, &Light::turn_off);
    sw_all_off.clicked.connect(&light1, &Light::turn_off);


    /* 
     * operation
     * */
    sw_toggle0.clicked();
    sw_toggle1.clicked();

    sw_all_on.clicked();
    sw_all_off.clicked();


    /*
     * disconnect signal - slot
     * */
    sw_toggle0.clicked.disconnect(&light0);
    sw_toggle1.clicked.disconnect(&light1);
    sw_all_on.clicked.disconnect(&light0);
    sw_all_on.clicked.disconnect(&light1);
    sw_all_off.clicked.disconnect(&light0);
    sw_all_off.clicked.disconnect(&light1);

    return 0;
}

Switch::Switch()
{
}

Switch::~Switch()
{
}

Light::Light(int state, const char *light_name)
    :m_state(state)
    ,m_light_name(light_name)
{
    this->disp_state();
}

Light::~Light()
{
}

void Light::turn_on(void)
{
    this->m_state = 1;
    this->disp_state();
}

void Light::turn_off(void)
{
    this->m_state = 0;
    this->disp_state();
}

void Light::toggle(void)
{
    if(0 == this->m_state){
        this->m_state = 1;
    }else{
        this->m_state = 0;
    }

    this->disp_state();
}

void Light::disp_state(void)
{
    printf("%s - state = %d\n", this->m_light_name.c_str(), this->m_state);
}




