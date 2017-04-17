/*
 * Progarm Name: server-tcp.hpp
 * Created Time: 2017-04-14 16:55:08
 * Last modified: 2017-04-17 14:45:06
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SERVER_TCP_HPP_
#define _SERVER_TCP_HPP_

#include <thread>
#include <string>
#include <list>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mutex>

using std::thread;
using std::string;
using std::list;
using std::recursive_mutex;

class ServerTcp{
public:
    ServerTcp();
    ~ServerTcp();
    int  echo(int timeout_seconds = 30);
private:
    int  register_xml(void);
    int  init_socket(void);
    int  reader(void);
    int  writer(void);
    int  listener(void);
    int  kill_thread(void);
private:
    thread            *m_reader      = nullptr;
    thread            *m_writer      = nullptr;
    thread            *m_listener    = nullptr;
    int                m_killed      = -1;
    list<string>       m_reader_buf;
    list<string>       m_writer_buf;
    struct sockaddr_in m_serv_addr;
    struct sockaddr_in m_client_addr;
    int                m_serv_sock   = -1;
    int                m_client_sock = -1;
    int                m_port        = -1;
    recursive_mutex    m_lock_read;
    recursive_mutex    m_lock_write;
};

#endif //_SERVER_TCP_HPP_

