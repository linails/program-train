/*
 * Progarm Name: server.cpp
 * Created Time: 2017-02-10 16:13:41
 * Last modified: 2017-02-14 13:34:11
 * @author: minphone.linails linails@foxmail.com 
 */

#include "server.hpp"
#include "log.h"
#include "user.h"
#include "process-rela.h"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

Server::Server()
{
}

Server::~Server()
{
}

int  Server::server_main(int argc, char **argv)
{
    int ret = 0;

    cout << "server-main ..." << endl;

    cout << "---------------------------" << endl;

    ret = this->user_process(); assert(-1 != ret);

    cout << "---------------------------" << endl;

    ret = this->models(); assert(-1 != ret);

    return ret;
}

/* 
 * 用户、进程组、会话等
 * */
int  Server::user_process(void)
{
    int ret = 0;

    ret = user(); assert(-1 != ret);

    if(0 != (ret = switch_to_user(2000, 20))){
        cout << "switch_to_user failed !" << endl;
    }else{
        cout << "switch_to_user success !" << endl;
    }

    ret = user(); assert(-1 != ret);

    cout << "---------------------------" << endl;

    ret = process_rela(); assert(-1 != ret);

    return ret;
}

/* 
 * 服务器模型
 * */
int  Server::models(void)
{
    int ret = 0;

    return ret;
}

