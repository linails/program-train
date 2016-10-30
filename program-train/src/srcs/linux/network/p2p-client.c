/*
 * Progarm Name: p2p-client.c
 * Created Time: 2016-10-29 14:22:58
 * Last modified: 2016-10-30 09:51:17
 * @author: minphone.linails linails@foxmail.com 
 */

#include "p2p-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

/* 
 * 这个 P2P 的实例原理是基于 UDP 通信原理
 * */

int p2p_client_main(int argc, char **argv)
{
    int ret = 0;
    printf("------ client_p2p_main ------\n");
    {
        int client(int argc, char **argv);
        ret = client(argc, argv);
    }
    return ret;
}

typedef enum{
    MSGID_UNKNOWN   = 0x00,
    MSGID_ADDR      = 0x01,
    MSGID_DATA      = 0x02,
    MSGID_RPT       = 0x03,
}MsgId_e;

typedef struct {
    int  msgid;
    int  dlen;
    char data[128];
    struct sockaddr_in addr;
}TMsg_t;

pthread_mutex_t mutex;

TMsg_t msg = { 0, };

int  sock;

int  quit_flag = -1;

socklen_t addrlen;

struct sockaddr_in serv_addr = { 0, };
struct sockaddr_in from_addr = { 0, };

int client(int argc, char **argv)
{
    int ret = 0;

    pthread_t   thread;
    void       *thread_result;

    /* init recv thread */
    {
        if(0 != (ret = pthread_mutex_init(&mutex, NULL))){
            perror("mutex init failed");
            exit(EXIT_FAILURE);
        }

        void *thread_recv(void *arg);
        if(0 != (ret = pthread_create(&thread, NULL, thread_recv, NULL))){
            perror("thread_a creation failed!");
            exit(EXIT_FAILURE);
        }
    }


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


    /* client announce to cloud server  */
    {
        printf("client announce to cloud server\n");
        msg.msgid = MSGID_RPT;
        sendto(sock, (char *)&msg, sizeof(msg), 0,
                (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        addrlen = sizeof(from_addr);
        recvfrom(sock, (char *)&msg, sizeof(msg), 0, 
                (struct sockaddr *)&from_addr, &addrlen);

        /* serv_addr = another client */
        memcpy((char *)&serv_addr, (char *)&msg.addr, sizeof(from_addr));

        printf("another client addr : %s - %d \n", 
                inet_ntoa(serv_addr.sin_addr),
                serv_addr.sin_port);
    }


    while(1){
        printf("Input message(q to Quit) : ");
        fgets(msg.data, sizeof(msg.data), stdin);

        if(!strcmp(msg.data, "q\n") || !strcmp(msg.data, "Q\n")){
            quit_flag = 0;
            break;
        }
        printf("Input message length : %d\n", (int)strlen(msg.data));


        msg.msgid = MSGID_DATA;
        msg.dlen = strlen(msg.data);

        sendto(sock, (char *)&msg, sizeof(msg), 0,
                (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    }

    close(sock);

    /* uninit thread recv  */
    {
        if(0 != (ret = pthread_join(thread, &thread_result))){
            perror("thread join failed!");
            exit(EXIT_FAILURE);
        }
        pthread_mutex_destroy(&mutex);
    }

    return ret;
}

void *thread_recv(void *arg)
{
    printf("thread_recv running...\n");

    while(1){
        if(0 == quit_flag){
            break;
        }

        addrlen = sizeof(from_addr);
        recvfrom(sock, (char *)&msg, sizeof(msg), 0, 
                (struct sockaddr *)&from_addr, &addrlen);

        printf("Msg from %s - %d - Recvmsg : %s\n", 
                inet_ntoa(from_addr.sin_addr),
                from_addr.sin_port,
                msg.data);
    }

    pthread_exit("recv thread exit!");
}



