/*
 * Progarm Name: mlinux.hpp
 * Created Time: 2016-12-21 09:39:08
 * Last modified: 2017-04-14 17:54:39
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MLINUX_HPP_
#define _MLINUX_HPP_

#include "server-tcp.hpp"

class mLinux{
public:
    mLinux();
    ~mLinux();
    int  mlinux_main(int argc, char **argv);
private:
    int  server(int argc, char **argv);
    int  server_tcp(void);
private:
    ServerTcp   *m_server_tcp = nullptr;
};

#endif //_MLINUX_HPP_

