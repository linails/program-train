/*
 * Progarm Name: server-tcp.cpp
 * Created Time: 2017-04-14 16:55:04
 * Last modified: 2017-04-17 16:47:12
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
#include "cfg-loader.hpp"
#include "manager.hpp"

using std::cout;
using std::endl;

ServerTcp::ServerTcp()
{
    this->register_xml();

    this->init_socket();

    this->m_listener = new thread(&ServerTcp::listener, this);
    if(nullptr == this->m_listener){
        cout << "[Error] new failed in ServerTcp - m_listener !" << endl;
        exit(1);
    }
}

ServerTcp::~ServerTcp()
{
    this->m_listener->join();
    delete this->m_listener;
    this->m_listener= nullptr;

    if(nullptr != this->m_reader){
        this->m_reader->join();
        delete this->m_reader;
        this->m_reader  = nullptr;
    }

    if(nullptr != this->m_writer){
        this->m_writer->join();
        delete this->m_writer;
        this->m_writer  = nullptr;
    }

    /*
     * close socket
     * */
    {
        if(-1 != this->m_serv_sock){
            close(this->m_serv_sock); this->m_serv_sock = -1;
        }
    }
}

int  ServerTcp::register_xml(void)
{
    int ret = 0;

    Manager * mgr = Manager::get_instance();
    if(nullptr != mgr){

        CfgLoader *cfg = mgr->get_xml_cfg();
        if(nullptr != cfg){
            cfg->register_RootChild("network", "server_port");

            string port;
            cfg->getRoot_child(port, "network", "server_port");
            this->m_port = atoi(port.c_str());

            cout << "port = " << this->m_port << endl;
        }else
            ret = -1;

    }else
        ret = -1;

    return ret;
}

int  ServerTcp::init_socket(void)
{
    int ret = 0;

    /* Step 1 */
    this->m_serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == this->m_serv_sock){
        cout << "socket() error !!!" << endl;
        ret = -1;
        exit(1);
    }

    memset(&this->m_serv_addr, 0, sizeof(this->m_serv_addr));
    this->m_serv_addr.sin_family        = AF_INET;
    this->m_serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    this->m_serv_addr.sin_port          = htons(this->m_port);

    /* Step 2 */
    if(-1 == bind(this->m_serv_sock, (struct sockaddr*)&this->m_serv_addr, sizeof(this->m_serv_addr))){
        cout << "bind() error !!!" << endl;
        ret = -1;
        exit(1);
    }

    return ret;
}

int  ServerTcp::listener(void)
{
    int ret = 0;

    while(1){
        if(-1 != this->m_killed) break;

        usleep(500 * 1000);

        if(-1 != this->m_serv_sock){

            socklen_t clnt_addr_size;

            /* Step 3 */
            if(-1 == listen(this->m_serv_sock, 2)){
                cout << "listen() error !!!" << endl;
                ret = -1;
                exit(1);
            }

            /* Step 4 */
            clnt_addr_size          = sizeof(this->m_client_addr);
            this->m_client_sock     = accept(this->m_serv_sock,
                                             (struct sockaddr*)&this->m_client_addr,
                                             &clnt_addr_size);
            if(-1 == this->m_client_sock){
                cout << "accept() error !!!" << endl;
                ret = -1;
                exit(1);
            }else{

                printf("Client : %d -> port : %#x\n",
                        this->m_client_sock, 
                        this->m_client_addr.sin_port);


                this->m_reader = new thread(&ServerTcp::reader, this);
                if(nullptr == this->m_reader){
                    cout << "[Error] new failed in ServerTcp - m_reader !" << endl;
                    close(this->m_client_sock);
                    ret = -1;
                    exit(1);
                }

                this->m_writer = new thread(&ServerTcp::writer, this);
                if(nullptr == this->m_writer){
                    cout << "[Error] new failed in ServerTcp - m_writer !" << endl;
                    close(this->m_client_sock);
                    ret = -1;
                    exit(1);
                }

            }

            break;
        }
    }

    return ret;
}

int  ServerTcp::echo(int timeout_seconds)
{

    while(timeout_seconds--){
        sleep(1);

        std::unique_lock<std::recursive_mutex> lock(this->m_lock_read);
        if(false == this->m_reader_buf.empty()){
            string s = this->m_reader_buf.front();
            this->m_reader_buf.pop_front();

            cout << "insert ... write_buf ..." << endl;
            std::unique_lock<std::recursive_mutex> lock(this->m_lock_write);
            this->m_writer_buf.push_back(s);
        }
    }
    cout << "quit while ..." << endl;

    this->kill_thread();

    return 0;
}

int  ServerTcp::reader(void)
{
    while(1){
        if(-1 != this->m_killed) break;

        char buf[1024] = {0, };
        int  str_len   = read(this->m_client_sock, buf, sizeof(buf));

        cout << "str_len = " << str_len << endl;
        if(0 != str_len){
            buf[str_len] = '\0';
            string s = buf;

            std::unique_lock<std::recursive_mutex> lock(this->m_lock_read);
            this->m_reader_buf.push_back(s);
            cout << "reader s = " << s << endl;
        }

        usleep(100 * 1000);
    }

    shutdown(this->m_client_sock, SHUT_RD);

    return 0;
}

int  ServerTcp::writer(void)
{
    while(1){
        if(-1 != this->m_killed) break;

        if(false == this->m_writer_buf.empty()){
            std::unique_lock<std::recursive_mutex> lock(this->m_lock_write);

            string s = this->m_writer_buf.front();
            this->m_writer_buf.pop_front();

            write(this->m_client_sock, s.c_str(), s.size());
        }

        usleep(100 * 1000);
    }

    shutdown(this->m_client_sock, SHUT_WR);

    return 0;
}

int  ServerTcp::kill_thread(void)
{
    this->m_killed = 0; return 0;
}

