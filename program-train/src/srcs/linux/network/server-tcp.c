/*
 * Progarm Name: server-tcp.c
 * Created Time: 2016-10-06 00:01:30
 * Last modified: 2016-10-23 20:55:52
 */

#include "server-tcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/* 
 * linux 文件操作
 *
 * 01. #include <sys/types.h>
 *     #include <sys/stat.h>
 *     #include <fcntl.h>
 *     int open(const char *path, int flag);
 *            - * path  : 文件名的字符串地址
 *            - * flag  : 文件打开模式信息
 *            -------------------------------
 *            O_CREAT   : 必要时创建文件
 *            O_TRUNC   : 删除全部现有数据
 *            O_APPEND  : 维持现有数据，保存到其后面
 *            O_RDONLY  : 只读打开
 *            O_WRONLY  : 只写打开
 *            O_RDWR    : 读写打开
 *            -------------------------------
 *
 * 02. #include <unistd.h>
 *     int close(int fd);
 *
 * 03. #include <unistd.h>
 *     ssize_t write(int fd, const void *buf, size_t nbytes);
 *          - * fd     : 显示数据传输对象的文件描述符
 *          - * buf    : 保存要传输数据的缓冲地址值
 *          - * nbytes : 要传输数据的字节数
 *
 *            * ssize_t: signed size_t
 *            * size_t : unsigned int
 *
 * 04. #include <unistd.h>
 *     ssize_t read(int fd, void *buf, size_t nbytes);
 *
 * */

/*
 * IPv4 : [网络地址] : [主机地址]
 *     A> [ 1 byte ] : [ 3 byte ] | 首字节范围： 0 ~ 127   | 0
 *     B> [ 2 byte ] : [ 2 byte ] | 首字节范围： 128 ~ 191 | 10
 *     C> [ 3 byte ] : [ 1 byte ] | 首字节范围： 192 ~ 223 | 110
 *     D> [ 4 byte ] : [ 0 byte ]
 *
 * 端口号：[2 byte] | 0 - 1023 是知名端口号，一般分配给特定应用程序
 * */

int server_tcp_main(int argc, char **argv)
{
    printf("------ server_tcp_main ------\n");

    /* 
     * 文件描述符是系统分配给 '文件' 或 '套接字' 的整数
     * -------------------------------
     *  0   标准输入：standard Input
     *  1   标准输出：standard Output
     *  2   标准错误：standard Error
     * -------------------------------
     *
     *  * 新创建的描述符是从3开始，由小到大的顺序编号
     *  * [ 0 , 1 , 2 ]三个文件描述符是系统自动分配的
     *  * "文件描述符" 在 Windows 中称为 "文件句柄"
     * */
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    socklen_t clnt_addr_size;

    char message[] = "Hello World!";



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



    if(2 != argc){
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    /******************************************************************************/

    /* Step 1 */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == serv_sock){
        printf("socket() error !!!\n");
        exit(1);
    }

    /* 
     * 常数：INADDR_ANY 分配服务器端IP地址
     *    采用这种方式，则可以自动获取运行服务器端的计算机IP地址，不必再亲自输入
     *    服务器中优先考虑这种方式 (只有一个NIC的时候)
     * */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family        = AF_INET;
    serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    serv_addr.sin_port          = htons(atoi(argv[1]));

    /* Step 2 */
    if(-1 == bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))){
        printf("bind() error !!!\n");
        exit(1);
    }

    /* Step 3 */
    if(-1 == listen(serv_sock, 5)){
        printf("listen() error !!!\n");
        exit(1);
    }

    /* Step 4 */
    clnt_addr_size  = sizeof(client_addr);
    client_sock     = accept(serv_sock, (struct sockaddr*)&client_addr, &clnt_addr_size);
    if(-1 == client_sock){
        printf("accept() error\n");
        exit(1);
    }

    /******************************************************************************/

    printf("Message To client : %s\n", message);
    write(client_sock, message, sizeof(message));

    /* Close all fd */
    close(client_sock);
    close(serv_sock);

    return 0;
}

/* 
 * function list :
 *
 * 01. #include <sys/socket.h>
 *     int socket(int domain, int type, int protocol);
 *              - * domain   : 套接字中使用的协议族信息
 *                  {
 *                      1> PF_INET   : IPv4 协议族 **
 *                      2> PF_INET6  : IPv6 协议族
 *                      3> PF_LOCAL  : 本地通信的UNIX协议族
 *                      4> PF_PACKET : 底层套接字的协议族
 *                      5> PF_IPX    : IPX Novell 协议族
 *                  }
 *              - * type     : 套接字数据传输类型信息
 *                  {
 *                      1> SOCK_STREAM  : 面向连接的套接字 TCP
 *                      2> SOCK_DGRAM   : 面向消息的套接字 UDP
 *                  }
 *              - * protocol : 计算机间通信中使用的协议信息
 *                  {
 *                      大部分情况下，这个参数传递0, 除非 "同一种协议族中存在多个数据传输方式相同的协议"
 *                  }
 *
 * 02. #include <sys/socket.h>
 *     int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
 *
 * 03. #include <sys/socket.h>
 *     int listen(int sockfd, int backlog);
 *          - * sockfd
 *          - * backlog : 连接请求等待队列的长度，若为5，则队列长度为5，表示最多使5个连接请求进入队列
 *                        像频繁接收请求的Web服务器端至少应设为15个
 *
 * 04. #include <sys/socket.h>
 *     int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 *          --> 成功时返回创建的套接字文件描述符，失败时返回-1
 *          - * sock    : 服务器套接字
 *          - * addr    : 保存发起连接请求的客户端地址
 *          - * addrlen : addr长度
 *
 * 以上总结步骤如下：
 *  1>调用 socket 函数创建套接字
 *  2>调用 bind 函数分配IP地址和端口号
 *  3>调用 listen 函数转为可接收请求状态
 *  4>调用 accept 函数受理连接请求
 * */

/* 
 * 总结：
 *
 * 01. 服务端创建的套接字又称为："服务器端套接字" 或 "监听套接字"
 *
 * 02. 调用 bind 函数给套接字分配了地址后，接下来就要通过调用 listen 函数进入等待连接请求状态
 *     只有调用了 listen 函数， 客户端才能进入可发出连接请求的状态(即客户端这时才可以调用 connect 函数)
 *
 * 03. accept 函数受理连接请求等待队列中待处理的客户端连接请求
 *     函数调用成功时，accept 函数内部将产生用于数据I/O的套接字，并返回其文件描述符
 *
 * */

