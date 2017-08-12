/*
 * Progarm Name: mlinux.cpp
 * Created Time: 2016-12-21 09:39:00
 * Last modified: 2017-08-12 08:17:45
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mlinux.hpp"
#include <iostream>
#include "sys_cmd.hpp"
#include "fd-test.h"
#include "endian-conv.h"
#include "process.hpp"
#include "cthread.hpp"
#include "io.hpp"
#include <cassert>
#include "mos.hpp"
#include "client-tcp.h"
#include "client-udp.h"
#include "inet-conv.h"
#include "p2p-client.h"
#include "dns-t.h"

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
        #if COMPILE_FLAG_mlinux_sys_cmd_casled
        sys_cmd_called();
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_other
        inet_conv_test();
        //fd_test();
        //endian_conv();
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_server_tcp
        //int client_tcp_main(int argc, char **argv);
        
        int ret = 0;

        const char *sargv[] = {
            "client_tcp_main",
            "127.0.0.1",
            "9190",
        };

        if((3 != argc) && (1 == argc)){
            ret = client_tcp_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            ret = client_tcp_main(argc, (char **)argv);
        }

        if(-1 == ret){
            cout << "server - tcp - main - failed !" << endl;
        }else{
            cout << "server - tcp - main - successed !" << endl;
        }
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_server_udp
        int ret = 0;

        const char *sargv[] = {
            "client_udp_main",
            "127.0.0.1",
            "9190"
        };

        if((3 != argc) && (1 == argc)){
            ret = client_udp_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            ret = client_udp_main(argc, (char **)argv);
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
        #if COMPILE_FLAG_mlinux_process
        Process process;

        ret = process.process_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_cthread
        cThread cthread;

        ret = cthread.cthread_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_io
        Io io;

        ret = io.io_main(argc, argv); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        const char *sargv[] = {
            "client_udp_main",
            "127.0.0.1",
            "9190"
        };

        if((3 != argc) && (1 == argc)){
            ret = p2p_client_main(sizeof(sargv)/sizeof(const char *), (char **)sargv);
        }else{
            ret = p2p_client_main(argc, (char **)argv);
        }

        if(-1 == ret){
            cout << "server - p2p client - main - failed !" << endl;
        }else{
            cout << "server - p2p client - main - successed !" << endl;
        }
#endif
    }
    cout << "---------------------------" << endl;
    {
        extern int dns_tmain(int argc, char **argv);
        dns_tmain(argc, argv);
    }

    return ret;
}

