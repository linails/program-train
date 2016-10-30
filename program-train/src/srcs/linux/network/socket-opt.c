/*
 * Progarm Name: socket-opt.c
 * Created Time: 2016-10-30 20:15:28
 * Last modified: 2016-10-30 22:50:00
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
    int ret = 0;
    return ret;
}

int binding_error(void)
{
    printf("-------- binding_error --------\n");
    int ret = 0;
    return ret;
}

int tcp_nodelay(void)
{
    printf("-------- tcp_nodelay --------\n");
    int ret = 0;
    return ret;
}

