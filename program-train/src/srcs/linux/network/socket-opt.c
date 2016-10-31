/*
 * Progarm Name: socket-opt.c
 * Created Time: 2016-10-30 20:15:28
 * Last modified: 2016-10-31 22:29:32
 * @author: minphone.linails linails@foxmail.com 
 */

#include "socket-opt.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

int sock_opt_main(int argc, char **argv)
{
    printf("-------- sock_opt_main --------\n");
    int ret = 0;

    {
        int socket_type(void);
        ret = socket_type();
    }
    {
        int io_buf(void);
        ret = io_buf();
    }
    {
        int binding_error(void);
        ret = binding_error();
    }
    {
        int tcp_nodelay(void);
        ret = tcp_nodelay();
    }

    return ret;
}

int socket_type(void)
{
    printf("-------- sock_type --------\n");
    int ret = 0;

    int tcp_sock;
    int udp_sock;
    int sock_type;

    socklen_t optlen;
    int state;

    optlen = sizeof(sock_type);

    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);

    printf("SOCK_STREAM : %d \n", SOCK_STREAM);
    printf("SOCK_DGRAM : %d \n", SOCK_DGRAM);

    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if(state){
        printf("getsockopt() error\n");
        ret = -1;
    }else{
        printf("sock_type : %d\n", sock_type);
    }

    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if(state){
        printf("getsockopt() error\n");
        ret = -1;
    }else{
        printf("sock_type : %d\n", sock_type);
    }

    return ret;
}

int io_buf(void)
{
    printf("-------- io_buf --------\n");

    /*
     * 创建套接字的同时将生成I/O缓冲
     *  1> SO_RCVBUF    是输入缓冲大小可选项
     *  2> SO_SNDBUF    是输出缓冲大小可选项
     * */

    int ret = 0;

    int sock;
    int snd_buf, rcv_buf, state;
    socklen_t   len;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    len  = sizeof(snd_buf);
    state= getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, &len);
    if(0 != state){
        printf("getsockopt() error\n");
        ret = -1;
    }

    len = sizeof(rcv_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, &len);
    if(0 != state){
        printf("getsockopt() error\n");
        ret = -1;
    }

    printf("Input buffer size : %d\n", rcv_buf);
    printf("Output buffer size : %d\n", snd_buf);



    /* 
     * */
    printf("----------- set io-buf -----------\n");

    snd_buf = 1024 * 3;
    rcv_buf = 1024 * 3;

    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, sizeof(rcv_buf));
    if(0 != state){
        printf("setsockopt() error \n");
        ret = -1;
    }

    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, sizeof(snd_buf));
    if(0 != state){
        printf("setsockopt() error \n");
        ret = -1;
    }



    /* 
     * 设置过后，缓冲区就会减小，但是并没有减小到 1024*3 大小，而是把设置输入的大小作为参考
     * */
    state= getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, &len);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, &len);
    if(0 == state){
        printf("Input buffer size : %d\n", rcv_buf);
        printf("Output buffer size : %d\n", snd_buf);
    }

    return ret;
}

int binding_error(void)
{
    /* 
     * 这一部分主要是和 SO_REUSEADDR 相关, 这个和 Time-wait 相关
     * 
     * 只有先断开连接的(先发送FIN消息的)主机才经过 Time-wait 状态，因此
     * 若服务器端先断开连接，则无法立即重新运行；套接字处在 Time-wait 过程
     * 中，相应端口是正在使用的状态
     * 如果这时候再运行进行 bind 相应端口，会发生错误
     *
     * * SO_REUSEADDR 默认值是 0 
     *   修改为 1 ，即可重新分配
     * */
    printf("-------- binding_error --------\n");
    int ret = 0;
    int option;
    socklen_t   optlen = sizeof(option);
    int state;

    int sock;

    sock = socket(PF_INET, SOCK_STREAM, 0);

    state = getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, &optlen);
    if(0 != state){
        printf("getsockopt() error!\n");
        ret = -1;
    }

    printf("SO_REUSEADDR default val : %d\n", option);

    /*
     * option = 1; 将不处于 Time-wait 状态
     * */
    option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, optlen);

    getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, &optlen);
    printf("SO_REUSEADDR update val : %d\n", option);

    return ret;
}

int tcp_nodelay(void)
{
    /*
     * Nagle算法 应用于TCP层
     *
     * * 只有收到前一数据的ACK消息时，Nagle算法才发送下一个数据
     * * TCP套接字默认使用Nagle算法交换数据，因此最大限度地进行缓冲, 知道收到ack
     * * 不使用 Nagle 算法讲对网络流量产生负面影响 | 为了提高网络传输效率，必须使用此算法
     *
     * * 但 Nagle 算法并不是什么时候都适用， 根据传输数据的特性，网络流量未受太大影响时，不
     * * 使用此算法要比使用它时传输速度快
     *
     * */
    printf("-------- tcp_nodelay --------\n");
    int ret = 0;

    /*
     * 禁用 Nagle 算法
     *
     * int opt_val = 1;
     * setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (void *)&opt_val, sizeof(opt_val));
     * */

    return ret;
}

