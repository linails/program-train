/*
 * Progarm Name: key-bind-main.hpp
 * Created Time: 2017-01-13 17:05:40
 * Last modified: 2017-01-17 10:23:47
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _KEY_BIND_MAIN_HPP_
#define _KEY_BIND_MAIN_HPP_

#include "disk.hpp"
#include "msg.hpp"

class KeyBind{
public:
    KeyBind();
    ~KeyBind();
    int  keybind_main(int argc, char **argv);
private:
    int  disk_init(void);
private:
    Disk   *m_disk = NULL;
};

#endif //_KEY_BIND_MAIN_HPP_

