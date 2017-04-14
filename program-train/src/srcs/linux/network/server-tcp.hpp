/*
 * Progarm Name: server-tcp.hpp
 * Created Time: 2017-04-14 16:55:08
 * Last modified: 2017-04-14 17:09:57
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SERVER_TCP_HPP_
#define _SERVER_TCP_HPP_

#include <thread>
#include <string>
#include <list>

using std::thread;
using std::string;
using std::list;

class ServerTcp{
public:
    ServerTcp();
    ~ServerTcp();
    int  echo(int timeout_seconds = 30);
private:
    int  reader(void);
    int  writer(void);
    int  kill_thread(void);
private:
    thread      *m_reader = nullptr;
    thread      *m_writer = nullptr;
    int          m_killed = -1;
    list<string> m_reader_buf;
    list<string> m_writer_buf;
};

#endif //_SERVER_TCP_HPP_

