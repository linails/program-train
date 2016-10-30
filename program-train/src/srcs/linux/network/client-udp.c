/*
 * Progarm Name: client-udp.c
 * Created Time: 2016-10-06 00:03:13
 * Last modified: 2016-10-30 11:30:35
 * @author: minphone.linails linails@foxmail.com 
 */

#include "client-udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int client_udp_main(int argc, char **argv)
{
    int ret = 0;
    printf("------ client_udp_main ------\n");
    {
#if 0
        int client_udp_echo(int argc, char **argv);
        ret = client_udp_echo(argc, argv);
#endif
    }
    printf("-----------------------------\n");
    {
        int client_udp_echo2(int argc, char **argv);
        ret = client_udp_echo2(argc, argv);
    }
    return ret;
}

int client_udp_echo(int argc, char **argv)
{
    int  sock;
    char message[512];
    int  str_len;

    socklen_t addrlen;

    struct sockaddr_in serv_addr, from_addr;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



    if(3 != argc){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == sock){
        printf("socket() error\n");
        exit(1);
    }


    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));


    while(1){
        printf("Input message(q to Quit) : ");
        fgets(message, sizeof(message), stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) break;
        printf("Input message length : %d\n", (int)strlen(message));

        sendto(sock, message, strlen(message), 0,
                (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        addrlen = sizeof(from_addr);

        str_len = recvfrom(sock, message, sizeof(message), 0, 
                (struct sockaddr *)&from_addr, &addrlen);

        message[str_len] = '\0';
        printf("Message from server : %s\n", message);
    }

    close(sock);

    return 0;
}

/* 常连接的 UDP */
int client_udp_echo2(int argc, char **argv)
{
    int  sock;
    char message[512];
    int  str_len;

    struct sockaddr_in serv_addr;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



    if(3 != argc){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == sock){
        printf("socket() error\n");
        exit(1);
    }


    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));


    while(1){
        printf("Input message(q to Quit) : ");
        fgets(message, sizeof(message), stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) break;
        printf("Input message length : %d\n", (int)strlen(message));

#if 0
        sendto(sock, message, strlen(message), 0,
                (struct sockaddr *)&serv_addr, sizeof(serv_addr));
#else
        write(sock, message, strlen(message));
#endif

#if 0
        str_len = recvfrom(sock, message, sizeof(message), 0, 
                (struct sockaddr *)&from_addr, &addrlen);
#else
        str_len = read(sock, message, sizeof(message) - 1);
#endif

        message[str_len] = '\0';
        printf("Message from server : %s\n", message);
    }

    close(sock);

    return 0;
}


/* 
 * TCP 套接字中需要注册待传输数据的目标IP和端口号，
 * UDP 套接字中无需注册
 *
 * 因此，通过 sendto 函数传输数据的过程大致可分为以下 3 个阶段
 *  1> 第1阶段：向 UDP 套接字注册目标IP和端口号
 *  2> 第2阶段：传输数据
 *  3> 第3阶段：删除 UDP 套接字中注册的目标地址信息
 *  [注：第1和第3阶段占整个通信过程的近1/3的时间]
 *
 * UDP 默认是属于未连接套接字的 | 有些情况下就需要创建已连接的 UDP 套接字
 *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 创建已连接的 UDP 套接字 :
 *
 *  sock = socket(PF_INET, SOCK_DGRAM, 0);
 *  memset(&adr, 0, sizeof(adr));
 *  adr.sin_family  = AF_INET;
 *  adr.sin_addr.s_addr = ...;
 *  adr.sin_port    = ...;
 *  # Note : 这里调用connect函数不是与对方的UDP连接，只是向UDP套接字注册目标IP和端口号
 *  connect(sock, (struct sockaddr *)&adr, sizeof(adr));
 *
 * */


