/*
 * Progarm Name: mlinux.cpp
 * Created Time: 2016-12-21 09:39:00
 * Last modified: 2017-03-15 18:58:35
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mlinux.hpp"
#include <iostream>
#include "sys_cmd.hpp"
#include "server-tcp.h"
#include "server-udp.h"
#include "fd-test.h"
#include "endian-conv.h"
#include "process.hpp"
#include "cthread.hpp"
#include "io.hpp"
#include "server.hpp"
#include <cassert>
#include "mos.hpp"

using std::cout;
using std::endl;

mLinux::mLinux()
{
}

mLinux::~mLinux()
{
}

int  mLinux::mlinux_main(int argc, char **argv)
{
    int ret = 0;

    cout << "------------- linux_main --------------" << endl;
    {
#if 0
        sys_cmd_called();
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 0
        //fd_test();
        //endian_conv();
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 0
        //int server_tcp_main(int argc, char **argv);

        const char *argv[] = {
            "server_tcp_main",
            "9190",
        };

        if(-1 == server_tcp_main(sizeof(argv)/sizeof(const char *), (char **)argv)){
            cout << "server - tcp - main - failed !" << endl;
        }else{
            cout << "server - tcp - main - successed ! " << endl;
        }
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 0
        //int server_udp_main(int argc, char **argv);
        
        const char *argv[] = {
            "server_udp_main",
        };

        if(-1 == server_udp_main(sizeof(argv)/sizeof(const char *), (char **)argv)){
            cout << "server - udp - main - failed !" << endl;
        }else{
            cout << "server - udp - main - successed !" << endl;
        }
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 0
        Process process;

        ret = process.process_main(argc, argv);
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 0
        cThread cthread;

        ret = cthread.cthread_main(argc, argv);
#endif
    }
    cout << "---------------------------" << endl;
#if 0
    {
        Io io;

        ret = io.io_main(argc, argv);
    }
#endif
    cout << "---------------------------" << endl;
    {
#if 0
        ret = this->server(argc, argv); assert(-1 != ret);
#endif
    }

    return ret;
}

int  mLinux::server(int argc, char **argv)
{
    int ret = 0;

    Server  server;

    ret = server.server_main(argc, argv); assert(-1 != ret);

    return ret;
}

