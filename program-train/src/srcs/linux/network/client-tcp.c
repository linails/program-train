/*
 * Progarm Name: client-tcp.c
 * Created Time: 2016-10-06 00:02:55
 * Last modified: 2016-10-24 21:09:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "client-tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int client_tcp_main(int argc, char **argv)
{
    int ret = 0;
    printf("------ client_tcp_main ------\n");
    {
#if 0
        int client_tcp_base(int argc, char **argv);
        ret = client_tcp_base(argc, argv);
#endif
    }
    printf("-----------------------------\n");
    {
#if 1
        int client_tcp_echo(int argc, char **argv);
        ret = client_tcp_echo(argc, argv);
#endif
    }

    return ret;
}

int client_tcp_base(int argc, char **argv)
{
    printf("------ server-udp-base ------\n");

    /* 
     * 客户端的步骤(2个步骤)：
     *
     * 1. 调用 socket 函数创建套接字
     *
     * 2. 调用 connect 函数向服务器端发送连接请求
     *
     * */

    /* 
     *  TCP 客户端的默认函数调用顺序
     *      01. socket()
     *      02. connect()
     *      03. read()/write()
     *      04. close()
     *
     *  * 客户端的IP地址和端口号在调用connect函数时自动分配，无需调用标记的bind函数进行分配
     *  * 且端口号是随机的
     * */

    int  sock;
    struct sockaddr_in serv_addr;
    
    char message[32];
    int  str_len;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



    if(3 != argc){
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    /******************************************************************************/

    /* Step 1 */
    sock    = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock){
        printf("socket() error !\n");
        exit(1);
    }

    /* Step 2 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))){
        printf("connect() error!\n");
        exit(1);
    }

    /******************************************************************************/

#if 0
    {
        str_len = read(sock, message, sizeof(message) - 1);
        if(-1 == str_len){
            printf("read() error!\n");
            exit(1);
        }
    }
#endif

    {
        /*  
         *  TCP 传输的数据不存在边界, 只要有数据，就一直接收
         *
         *  * server 端 write 的次数与 client 端 read 次数没有关系
         *
         *  */

        int idx = 0;
        int read_len = 0;
        while((read_len = read(sock, &message[idx++], 1))){
            if(-1 == read_len){
                printf("read() error!\n");
                exit(1);
            }
            printf("read a byte : %c\n", message[idx - 1]);

            str_len += read_len;
        }
    }

    printf("Message from server : %s \n", message);

    /* Close fd */
    close(sock);

    return 0;
}

int client_tcp_echo(int argc, char **argv)
{
    printf("------ server-udp-echo ------\n");

    int  sock;
    struct sockaddr_in serv_addr;
    
    char message[512];
    int  str_len;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



    if(3 != argc){
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    /******************************************************************************/

    /* Step 1 */
    sock    = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock){
        printf("socket() error !\n");
        exit(1);
    }

    /* Step 2 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = inet_addr(argv[1]);
    serv_addr.sin_port          = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))){
        printf("connect() error!\n");
        exit(1);
    }else{
        printf("Connected ...\n");
    }

    /******************************************************************************/

    while(1){
        printf("while ...\n");

        fputs("Input message(Q to quit) :", stdout);
        fgets(message, sizeof(message), stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) break;
        printf("Input message length : %d\n", (int)strlen(message));

        str_len = write(sock, message, strlen(message));

        int read_len = 0;
        while(read_len < str_len){
            int read_cnt = read(sock, &message[read_len], sizeof(message)-1);
            if(-1 == read_cnt){
                printf("read() error !\n");
                exit(1);
            }
            read_len += read_cnt;
        }

        message[str_len] = '\0';
        printf("Message from server : %s  - strlen : %d\n", message, str_len);
    }

    /* Close fd */
    close(sock);

    return 0;
}

/* 
 * function list :
 *
 * 01. #include <sys/socket.h>
 *     int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
 *          --> 成功返回0
 *              成功返回不意味着服务器端调用了accept函数，只是服务器端把连接请求信息记录到等待队列中
 *              因此 connect 函数返回后并不立即进行数据交换
 *
 * * socket 建立之后，就直接调用 connect 函数成为客户端
 *
 * */

