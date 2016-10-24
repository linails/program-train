/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-10-24 21:21:36
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"
#include "client-tcp.h"
#include "client-udp.h"
#include "inet-conv.h"

using namespace std;

void linux_main(void)
{
    cout << "------------- linux_main --------------" << endl;
    {
        //sys_cmd_called();
    }
    cout << "---------------------------" << endl;
    {
        inet_conv_test();
    }
    cout << "---------------------------" << endl;
    {
#if 0
        //int client_tcp_main(int argc, char **argv);
        const char *argv[] = {
            "client_tcp_main",
            "127.0.0.1",
            "9190",
        };

        if(-1 == client_tcp_main(sizeof(argv)/sizeof(const char *), (char **)argv)){
            cout << "server - tcp - main - failed !" << endl;
        }else{
            cout << "server - tcp - main - successed !" << endl;
        }
#endif
    }
    cout << "---------------------------" << endl;
    {
#if 1
        const char *argv[] = {
            "client_udp_main",
            "127.0.0.1",
            "9190"
        };

        if(-1 == client_udp_main(sizeof(argv)/sizeof(const char *), (char **)argv)){
            cout << "server - udp - main - failed !" << endl;
        }else{
            cout << "server - udp - main - successed !" << endl;
        }
#endif
    }
}

