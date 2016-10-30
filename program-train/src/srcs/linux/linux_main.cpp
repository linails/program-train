/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-10-30 15:38:18
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"
#include "client-tcp.h"
#include "client-udp.h"
#include "inet-conv.h"
#include "p2p-client.h"
#include "dns-t.h"

using namespace std;

void linux_main(int argc, char **argv)
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
#if 0
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
#if 0
        int ret = 0;

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
}

