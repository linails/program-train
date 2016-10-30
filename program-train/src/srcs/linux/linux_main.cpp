/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-10-30 21:49:44
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"
#include "server-tcp.h"
#include "server-udp.h"
#include "fd-test.h"
#include "endian-conv.h"
#include "socket-opt.h"

using namespace std;

void linux_main(void)
{
    cout << "------------- linux_main --------------" << endl;
    {
        //sys_cmd_called();
    }
    cout << "---------------------------" << endl;
    {
        fd_test();
        endian_conv();
        sock_opt_main( 0, NULL);
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
            "9190"
        };

        if(-1 == server_udp_main(sizeof(argv)/sizeof(const char *), (char **)argv)){
            cout << "server - udp - main - failed !" << endl;
        }else{
            cout << "server - udp - main - successed !" << endl;
        }
#endif
    }
}

