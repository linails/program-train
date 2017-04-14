/*
 * Progarm Name: server-tcp.cpp
 * Created Time: 2017-04-14 16:55:04
 * Last modified: 2017-04-14 17:15:18
 * @author: minphone.linails linails@foxmail.com 
 */

#include "server-tcp.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;

ServerTcp::ServerTcp()
{
    this->m_reader = new thread(&ServerTcp::reader, this);
    if(nullptr == this->m_reader){
        cout << "[Error] new failed in ServerTcp !" << endl;
        exit(1);
    }

    this->m_writer = new thread(&ServerTcp::writer, this);
    if(nullptr != this->m_writer){
        cout << "[Error] new failed in ServerTcp !" << endl;
        exit(1);
    }
}

ServerTcp::~ServerTcp()
{
    this->m_reader->join();
    this->m_writer->join();

    delete this->m_reader;
    delete this->m_writer;

    this->m_reader = nullptr;
    this->m_writer = nullptr;
}

int  ServerTcp::echo(int timeout_seconds)
{

    while(timeout_seconds--){
        sleep(1);
    }

    return 0;
}

int  ServerTcp::reader(void)
{
    while(1){

        if(-1 != this->m_killed) break;
    }

    return 0;
}

int  ServerTcp::writer(void)
{
    while(1){

        if(-1 != this->m_killed) break;
    }

    return 0;
}

int  ServerTcp::kill_thread(void)
{
    this->m_killed = 0; return 0;
}

