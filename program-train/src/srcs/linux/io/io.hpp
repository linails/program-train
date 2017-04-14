/*
 * Progarm Name: io.hpp
 * Created Time: 2016-12-10 21:38:25
 * Last modified: 2016-12-31 21:17:08
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _IO_HPP_
#define _IO_HPP_

class Io{
public:
    Io();
    ~Io();
    int  io_main(int argc, char **argv);
private:
    int  io_multiplexing(void);
    int  io_multiplexing_select(void);
    int  io_multiplexing_poll(void);
    int  io_multiplexing_epoll(void);
    int  io_send_recv(void);
    int  io_readv_writev(void);
};

#endif //_IO_HPP_

