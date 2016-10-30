/*
 * Progarm Name: p2p-server.c
 * Created Time: 2016-10-29 14:27:02
 * Last modified: 2016-10-29 22:11:38
 * @author: minphone.linails linails@foxmail.com 
 */

#include "p2p-server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int p2p_server_main(int argc, char **argv)
{
    int ret = 0;
    printf("------ p2p-server-main ------\n");
    {
        int server(int argc, char **argv);
        ret = server(argc, argv);
    }
    return ret;
}

typedef enum{
    MSGID_UNKNOWN = 0x00,
    MSGID_ADDR    = 0x01,
    MSGID_DATA    = 0x02,
    MSGID_RPT     = 0x03,
}MsgId_e;

typedef struct {
    int     msgid;
    int     dlen;
    char    data[128];
    struct sockaddr_in addr;
}TMsg_t;

int server(int argc, char **argv)
{
    TMsg_t msg = { 0, };

    int serv_sock;

    char *padr = NULL;
    socklen_t clnt_addr_size;
    struct sockaddr_in serv_addr;

    struct sockaddr_in client_addr;
    struct sockaddr_in clients[2] = { { 0, }, { 0, } };
    struct sockaddr_in *pdst_client = NULL;



    printf("\n");
    printf("Print argv[] List :\n{\n");
    for(int i=0; i<argc; i++){
        printf("    argv[%d] : %s\n", i, argv[i]);
    }
    printf("}\n\n");



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

        recvfrom(serv_sock, (char *)&msg, sizeof(msg), 0,
                           (struct sockaddr *)&client_addr, &clnt_addr_size);
        
        printf("Client connect :\n");
        printf("    client addr : %s - port : %d\n",
                inet_ntoa(client_addr.sin_addr),
                client_addr.sin_port
                );


        switch(msg.msgid){
            case MSGID_ADDR:
                {
                }
                break;
            case MSGID_DATA:
                {
                }
                break;
            case MSGID_RPT:
            default: 
                {
                    printf("client announce \n");

                    for(int i=0; i<2; i++){
                        if(0 == clients[i].sin_port){
                            memcpy((char *)&clients[i], (char *)&client_addr, sizeof(client_addr));
                            break;
                        }
                    }
                }
                break;
                break;
        }

#if 0
        for(int i=0; i<2; i++){
            if(0 != clients[i].sin_port){
                if(client_addr.sin_addr.s_addr != clients[i].sin_addr.s_addr){
                    pdst_client = &clients[i];
                    memcpy((char *)&msg.addr, (char *)&client_addr, sizeof(client_addr));
                    printf("pdst_client assignment !\n");
                }
                break;
            }
        }
#endif

        int exchange_flag = 0;
        printf("clietns list :\n");
        for(int i=0; i<2; i++){
            printf("    clients[%d].sin_port %d\n", i, clients[i].sin_port);
            if(0 == clients[i].sin_port){
                exchange_flag = -1;
            }
        }
        printf("\n");


        if(-1 != exchange_flag){

            {
                pdst_client = &clients[0];
                memcpy((char *)&msg.addr, (char *)&clients[1], sizeof(client_addr));
                printf("pdst_client assignment !\n");

                if(NULL != pdst_client){
                    sendto(serv_sock, (char *)&msg, sizeof(msg), 0, 
                                       (struct sockaddr *)pdst_client, clnt_addr_size);
                    pdst_client = NULL;
                }
            }
            {
                pdst_client = &clients[1];
                memcpy((char *)&msg.addr, (char *)&clients[0], sizeof(client_addr));
                printf("pdst_client assignment !\n");

                if(NULL != pdst_client){
                    sendto(serv_sock, (char *)&msg, sizeof(msg), 0, 
                                       (struct sockaddr *)pdst_client, clnt_addr_size);
                    pdst_client = NULL;
                }
            }

        }
    }


    close(serv_sock);

    return 0;
}



