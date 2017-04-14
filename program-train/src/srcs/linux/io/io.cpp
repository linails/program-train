/*
 * Progarm Name: io.cpp
 * Created Time: 2016-12-10 21:31:16
 * Last modified: 2016-12-31 21:33:33
 * @author: minphone.linails linails@foxmail.com 
 */

#include "io.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <cstdio>
#include <cstdlib>
#include <string>

using std::cout;
using std::endl;
using std::string;

Io::Io()
{
}

Io::~Io()
{
}

int  Io::io_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->io_multiplexing();

    return ret;
}

int  Io::io_multiplexing(void)
{
    /* 
     * 引入IO复用技术，可以减少所需要的进程数，不过也只是针对一些情况适用
     *
     * [ 常用的IO复用方法：select / poll / epoll ]
     *
     * */

    int ret = 0;

    ret = this->io_multiplexing_select();

    //ret = this->io_multiplexing_poll();

    //ret = this->io_multiplexing_epoll();

    return ret;
}

int  Io::io_multiplexing_select(void)
{
    cout << "io_multiplexing_select ..." << endl;

    /*
     * 运用 select 函数是最具代表性的实现复用服务器端的方法
     *
     * 使用 select 函数时，可以将多个文件描述符集中到一起统一监视
     * 当监视项发生情况，为发生了事件 event
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * select 函数的使用方法与一般函数区别较大
     *  > step 1 :
     *            a>设置文件描述符
     *            b>指定监视范围
     *            c>设置超时
     *  > step 2 :
     *            调用 select 函数
     *  > step 3 :
     *            查看调用结果
     * */

    int ret = 0;

    /* 
     * 利用 select 函数可以同时监视多个文件描述符
     * 集中监视项按(接收、 传输、异常)进行区分
     *
     * 在 fd_set 结构体中，对需要进行监视的文件描述符的位置进行置1
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *  FD_ZERO(fd_set *fdset)          : 将 fd_set 变量的所有位初始化为0
     *  FD_SET(int fd, fd_set *fdset)   : 在参数 fdset 指向的变量中注册文件描述符 fd 的信息
     *  FD_CLR(int fd, fd_set *fdset)   : 从参数 fdset 指向的变量中清除文件描述符 fd 的信息
     *  FD_ISSET(int fd, fd_set *fdset) : 若参数 fdset 指向的变量中包含文件描述符 fd 的信息，则返回 "真"
     *
     *  #include <sys/select.h>
     *  #include <sys/time.h>
     *  int select(
     *      int maxfd, fd_set *readset, fd_set *writeset, fd_set *excetpset, const struct timeval *timeout);
     *          -> 成功时返回大于0的值，失败返回-1
     *          -- maxfd    : 监视对象文件描述符数量
     *          -- readset  : 将所有关注 "是否存在待读取数据" 的文件描述符注册到 fd_set 型变量，并传递其地址值
     *          -- writeset : 将所有关注 "是否可传输无阻塞数据" 的文件描述符注册到 fd_set 型变量，并传递其地址值
     *          -- excetpset: 将所有关注 "是否发生异常" 的文件描述符注册到 fd_set 型变量，并传递其地址值
     *          -- timeout  : 调用 select 函数后，为防止陷入无限阻塞的状态，传递超时 (timeout) 信息 !!!
     *                        不设置超时，则传递 NULL 即可
     *          [发生错误返回-1， 超时返回0， 因发生关注的事件返回时，返回大于0的值，该值是发生事件的文件描述符数]
     *
     *  struct timeval{
     *      long tv_sec;
     *      long tv_usec;
     *  }
     * */

    fd_set reads, temps;

    int result;

    struct timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads);  // 0 标准输入

    while(1){

        temps = reads;

        /*
         * 每次调用 select() need to init timeout 
         *
         * !!! 因为 select() 函数执行后，会替换为超时前剩余时间
         *
         * */
        timeout.tv_sec  = 3;
        timeout.tv_usec = 0;

        if(-1 == (result = select(1, &temps, 0, 0, &timeout))){
            cout << "[Error] select error !" << endl;
        }else if(0 == result){
            cout << "select timeout " << endl;
            cout << "[*] input : quit" << endl;
        }else{
            if(FD_ISSET(0, &temps)){
                char buf[128] = "";
                int len = read(0, buf, 128);

                buf[len] = '\0';
                cout << "read buf : " << buf << endl;

                string s(buf);
                if(string::npos != s.find("quit"))  break;
            }
        }
    }

    return ret;
}

int  Io::io_multiplexing_poll(void)
{
    cout << "io_multiplexing_poll ..." << endl;

    int ret = 0;

    return ret;
}

int  Io::io_multiplexing_epoll(void)
{
    cout << "io_multiplexing_epoll ..." << endl;

    /* 
     * select 的I/O复用技术速度慢的原因 :
     *
     *  1> 调用 select() 函数后常见的针对所有文件描述符的循环语句
     *     { 调用 select() 函数后，并不是把发生变化的文件描述符单独集中到一起，
     *       而是通过观察作为监视对象的 fd_set 变量的变化，找出发生变化的文件描述符，
     *       因此无法避免针对所有监视对象的循环语句 }
     *
     *  2> 每次调用 select() 函数时都需要向该函数传递监视对象信息
     *     { 每次传递监视对象信息，会产生比较大的耗时 
     *       因为应用程序向操作系统传递数据将对程序造成很大的负担，而且无法通过优化代码解决
     *       [ 因此如果可以通过传递1次监视对象，那样会显著提高效率 - epoll ]
     *     }
     * 
     * */

    /* 
     * 能够克服 select() 函数缺点的 epoll() 函数具有如下优点:
     *  1> 无需编写以监视状态变化为目的的针对所有文件描述符的循环语句
     *  2> 调用对应于 select() 函数的 epoll_wait() 函数时无需每次传递监视对象信息
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * epoll服务器端实现中需要3个函数：
     *  1> epoll_create : 创建保存 epoll 文件描述符的空间
     *  2> epoll_ctl    : 向空间注册并注销文件描述符
     *  3> epoll_wait   : 与 select 函数类似，等待文件描述符发生变化
     * */

    int ret = 0;

    return ret;
}

int  Io::io_send_recv(void)
{
    cout << "io_send_recv ..." << endl;

    /* 
     *  #include <sys/socket.h>
     *  ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags);
     *      -> 成功时返回发送的字节数，失败返回-1
     *      -- sockfd   : 表示与数据传输对象的连接的套接字文件描述符
     *      -- buf      : 保存待传输数据的缓冲地址值
     *      -- nbytes   : 待传输的字节数
     *      -- flags    : 传输数据时指定的可选项信息
     *
     *  #include <sys/socket.h>
     *  ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);
     *      -> 成功时返回接收的字节数(收到EOF时返回0)，失败时返回-1
     *      -- sockfd   : 表示与数据传输对象的连接的套接字文件描述符
     *      -- buf      : 保存接收数据的缓冲地址值
     *      -- nbytes   : 可接收的最大字节数
     *      -- flags    : 接收数据时指定的可选项信息
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  send / recv 函数的最后一个参数是收发数据时的可选项，可进行或操作
     *
     *      可选项       |                含义                |  send  |  recv
     *  -----------------+------------------------------------+--------+----------
     *    MSG_OOB        |  用于传输带外数据                  |    O   |    O
     *    MSG_PEEK       |  验证输入缓冲中是否存在接收的数据  |    X   |    O
     *    MSG_DONTROUTE  |  数据传输过程中不参照路由表，在本  |    O   |    X
     *                   |  地寻找目的地                      |        |        
     *    MSG_DONTWAIT   |  调用I/O函数时不阻塞，用于使用非   |    O   |    O
     *                   |  阻塞IO                            |        |        
     *    MSG_WAITALL    |  防止函数返回，直到接收全部请求的  |    X   |    O
     *                   |  字节数                            |        |    
     * */

    int ret = 0;

    return ret;
}

int  Io::io_readv_writev(void)
{
    cout << "io_readv_writev ..." << endl;

    int ret = 0;

    return ret;
}

