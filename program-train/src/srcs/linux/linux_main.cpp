/*
 * Progarm Name: linux_main.cpp
 * Created Time: 2016-08-24 09:17:33
 * Last modified: 2016-10-30 14:25:36
 * @author: minphone.linails linails@foxmail.com 
 */

#include "linux_main.h"
#include <iostream>
#include "sys_cmd.hpp"
#include "server-tcp.h"
#include "server-udp.h"
#include "fd-test.h"
#include "endian-conv.h"
#include "p2p-server.h"

using namespace std;

void linux_main(int argc, char **argv)
{
    cout << "------------- linux_main --------------" << endl;
    {
        //sys_cmd_called();
    }
    cout << "---------------------------" << endl;
    {
        fd_test();
        endian_conv();
    }
    cout << "---------------------------" << endl;
    {
#if 1
        //int server_tcp_main(int argc, char **argv);

        int ret = 0;

        const char *sargv[] = {
            "server_tcp_main",
            "9190",
        };

        if(1 != argc){
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

        int ret = 0;
        
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
}

