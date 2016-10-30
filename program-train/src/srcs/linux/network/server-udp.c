/*
 * Progarm Name: server-udp.c
 * Created Time: 2016-10-06 00:01:59
 * Last modified: 2016-10-29 14:13:43
 */

#include "server-udp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* 
 * * UDP 提供不可靠的数据传输服务
 *
 * * UDP 不会发送类似 ACK 的应答消息，也不会像 SEQ 那样给数据包分配序号
 *
 * * UDP 和 TCP 最主要差异(算核心差异了)只在于流控制
 *
 * * 每次交换的数据量越大，则 TCP 的传输速率就越接近 UDP 的传输速率
 *
 * * TCP 比 UDP 慢的原因通常有以下两点：
 *      <1> 收发数据前后进行的连接设置及清除过程
 *      <2> 收发数据过程中为保证可靠性而添加的流控制
 * */

/* 
 * * UDP 服务器端/客户端不像TCP那样在连接状态下交换数据，因此无需经过连接过程
 *   UDP 中只有创建套接字的过程 和 数据交换的过程
 *
 *******************************************************************************
 *
 * #include <sys/socket.h>
 * ssize_t sendto(int sock, void *buff, size_t nbytes, int flags,
 *                                      struct sockaddr *to, socklen_t addrlen);
 *
 *      --> 成功时返回传输的字节数，失败返回-1
 *
 *      - * sock    : 用于传输数据的UDP套接字文件描述符
 *      - * buff    : 保存待传输数据的缓冲地址值
 *      - * nbytes  : 待传输的数据长度，以字节为单位
 *      - * flags   : 可选项参数，若没有则传递0
 *      - * to      : 存有目标地址信息的 sockaddr 结构体变量的地址值
 *      - * addrlen : 传递给参数to的地址值结构体变量长度
 *
 * ssize_t recvfrom(int sock, void *buff, size_t nbytes, int flags,
 *                                        struct sockaddr *from, socklen_t *addrlen);
 *
 *      --> 成功时返回接收的字节数，失败返回-1
 *
 * */

int server_udp_main(int argc, char **argv)
{
    int ret = 0;
    printf("------ server_udp_main ------\n");
    {
        int server_udp_echo(int argc, char **argv);
        ret = server_udp_echo(argc, argv);
    }
    printf("-----------------------------\n");
    {
    }
    return ret;
}

int server_udp_echo(int argc, char **argv)
{
    printf("------ server-udp-echo ------\n");

    int serv_sock;
    int str_len;

    char message[512];
    char *padr = NULL;
    socklen_t clnt_addr_size;
    struct sockaddr_in serv_addr, client_addr;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



#if 0
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
#endif
    if(argc == 3){
        padr = argv[1];
    }


    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(-1 == serv_sock){
        printf("UDP socket creation error\n");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    if(NULL == padr){
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port        = htons(atoi(argv[1]));
    }else{
        serv_addr.sin_addr.s_addr = inet_addr(padr);
        serv_addr.sin_port        = htons(atoi(argv[2]));
    }


    if(-1 == bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))){
        printf("bind() error\n");
        exit(1);
    }


    while(1){
        clnt_addr_size = sizeof(client_addr);

        str_len = recvfrom(serv_sock, message, sizeof(message), 0,
                           (struct sockaddr *)&client_addr, &clnt_addr_size);
        
        printf("Client connect :\n");
        printf("    client addr : %s - port : %d\n",
                inet_ntoa(client_addr.sin_addr),
                client_addr.sin_port
                );

        message[str_len] = '\0';
        printf("Recvfrom message : %s - length : %d\n", message, str_len);

        sendto(serv_sock, message, str_len, 0, 
                           (struct sockaddr *)&client_addr, clnt_addr_size);
    }


    close(serv_sock);

    return 0;
}

