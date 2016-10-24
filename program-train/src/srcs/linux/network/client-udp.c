/*
 * Progarm Name: client-udp.c
 * Created Time: 2016-10-06 00:03:13
 * Last modified: 2016-10-24 21:21:09
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
        int client_udp_echo(int argc, char **argv);
        ret = client_udp_echo(argc, argv);
    }
    printf("-----------------------------\n");
    {
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



