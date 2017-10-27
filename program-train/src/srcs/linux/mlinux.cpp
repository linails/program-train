/*
 * Progarm Name: mlinux.cpp
 * Created Time: 2016-12-21 09:39:00
 * Last modified: 2017-10-27 23:16:23
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
#include "backtrace.hpp"
#include <string>
#include "manager.hpp"
#include "file-manager.hpp"

using std::cout;
using std::endl;
using std::string;

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
        //fd_test();
        //endian_conv();


        //Backtrace   bt;
        //bt.segmentfault_test();

        ret = this->file_manager(); assert(-1 != ret);
        #endif
    }
    cout << "---------------------------" << endl;
    {
        #if COMPILE_FLAG_mlinux_server_tcp
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
        #if COMPILE_FLAG_mlinux_server_udp
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
        #if COMPILE_FLAG_mlinux_server
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

int  mLinux::file_manager(void)
{
    cout << "mlinux::file_manager() ..." << endl;

    string fn;
    
    Manager::get_instance()->get_xml_cfg()->register_RootChild("filemgr", "filecpp");
    Manager::get_instance()->get_xml_cfg()->getRoot_child(fn, "filemgr", "filecpp");

    cout << "fn = " << fn << endl;

    FileManager fm(fn.c_str());

    return 0;
}

