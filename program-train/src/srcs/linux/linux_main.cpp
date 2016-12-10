/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-12-10 12:05:41
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"
#include "server-tcp.h"
#include "server-udp.h"
#include "fd-test.h"
#include "endian-conv.h"
#include "process.hpp"
#include "cthread.hpp"

using namespace std;

int linux_main(int argc, char **argv)
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
#if 1
        cThread cthread;

        ret = cthread.cthread_main(argc, argv);
#endif
    }

    return ret;
}

