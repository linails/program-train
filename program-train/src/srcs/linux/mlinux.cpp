/*
 * Progarm Name: mlinux.cpp
 * Created Time: 2016-12-21 09:39:00
 * Last modified: 2017-04-14 17:59:45
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
        sock_opt_main( 0, NULL);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if 0
        //int server_tcp_main(int argc, char **argv);

        const char *sargv[] = {
            "server_tcp_main",
            "9190",
        };

        if(1 == argc){
            ret = server_tcp_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            ret = server_tcp_main(argc, (char **)argv);
        }

        if(-1 == ret){
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

        const char *sargv[] = {
            "server_udp_main",
            "9190"
        };

        printf("argc : %d\n", argc);
        if((3 != argc) && (1 == argc)){
            printf("call 3 != argc\n");
            ret = server_udp_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            printf("call else\n");
            ret = server_udp_main(argc, (char **)argv);
        }

        if(-1 == ret){
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
    {
        #if 0
        Io io;

        ret = io.io_main(argc, argv);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if 0
        ret = this->server(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if 0
        //int p2p_server_main(int argc, char **argv);

        int ret = 0;
        
        const char *sargv[] = {
            "server_p2p_main",
            "9190"
        };

        if((3 != argc) && (1 == argc)){
            ret = p2p_server_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            ret = p2p_server_main(argc, (char **)argv);
        }

        if(-1 == ret){
            cout << "server - p2p - main - failed !" << endl;
        }else{
            cout << "server - p2p - main - successed !" << endl;
        }
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

int  mLinux::server_tcp(void)
{
    this->m_server_tcp = new ServerTcp();
    if(nullptr == this->m_server_tcp){
        cout << "[Error] new ServerTcp() failed !" << endl;
        exit(1);
    }

    this->m_server_tcp->echo();

    return 0;
}

