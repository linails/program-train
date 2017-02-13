/*
 * Progarm Name: server.cpp
 * Created Time: 2017-02-10 16:13:41
 * Last modified: 2017-02-13 14:14:10
 * @author: minphone.linails linails@foxmail.com 
 */

#include "server.hpp"
#include "log.h"
#include "user.h"
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

    ret = user(); assert(-1 != ret);

    if(0 != (ret = switch_to_user(2000, 20))){
        cout << "switch_to_user failed !" << endl;
    }else{
        cout << "switch_to_user success !" << endl;
    }

    ret = user(); assert(-1 != ret);

    return ret;
}

