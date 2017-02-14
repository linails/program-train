/*
 * Progarm Name: server.hpp
 * Created Time: 2017-02-10 16:13:45
 * Last modified: 2017-02-14 10:23:04
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SERVER_HPP_
#define _SERVER_HPP_

class Server{
public:
    Server();
    ~Server();
    int  server_main(int argc, char **argv);
private:
    int  user_process(void);
    int  models(void);
};

#endif //_SERVER_HPP_

