/*
 * Progarm Name: mlinux.hpp
 * Created Time: 2016-12-21 09:39:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MLINUX_HPP_
#define _MLINUX_HPP_

#define COMPILE_FLAG_mlinux_sys_cmd_casled 1
#define COMPILE_FLAG_mlinux_server_tcp     0
#define COMPILE_FLAG_mlinux_server_udp     0
#define COMPILE_FLAG_mlinux_process        0
#define COMPILE_FLAG_mlinux_cthread        0
#define COMPILE_FLAG_mlinux_io             0
#define COMPILE_FLAG_mlinux_server         0
#define COMPILE_FLAG_mlinux_other          0

class mLinux{
public:
    mLinux();
    ~mLinux();
    int  mlinux_main(int argc, char **argv);
private:
    int  server(int argc, char **argv);
};

#endif //_MLINUX_HPP_

