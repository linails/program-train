/*
 * Progarm Name: ipc_msgq.c
 * Created Time: 2016-05-05 14:17:02
 * Last modified: 2016-05-25 10:15:39
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.2
 */

#include "ipc_msgq.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_KEYID_READ  0x0001
#define MSG_KEYID_WRITE 0x0002

#define MSG_FLAG   IPC_CREAT | 0666

typedef struct{
    long    msgType;
    int     dlen;       /* user data length : [0,2048]*/
    char    buf[2048];  /* user data buffer */
}msgQueue_t;

/*ipc - msg queue send - success return 0*/
int ipc_msg_send(char *sbuf,int len)
{
    int         msgid = 0;
    msgQueue_t  *psend = NULL;

    if((msgid = msgget(MSG_KEYID_WRITE,MSG_FLAG)) < 0){
        printf("failed to get msg queue id!\n");
        return -1;
    }else{
        psend = (msgQueue_t *)malloc(sizeof(msgQueue_t));
        if(psend == NULL){
            printf("failed malloc psend data \n");
            return -1;
        }

        static int i = 0;
        memset((char *)psend,0,sizeof(msgQueue_t));
        psend->msgType  =  i++;
        psend->dlen     =  len;
        memcpy(psend->buf,(void *)sbuf,len);

        if(msgsnd(msgid,(void *)psend,sizeof(msgQueue_t),IPC_NOWAIT) < 0){
            printf("failed msgsnd!\n");
            free(psend);
            return -1;
        }
        free(psend);
    }
    return 0;
}

/*ipc - msg queue recv - success return 0*/
int ipc_msg_recv(char *rbuf,int *len)
{
    int         msgid = 0;
    msgQueue_t  *precv = NULL;

    if((msgid = msgget(MSG_KEYID_READ,MSG_FLAG)) < 0){
        printf("failed to get msg queue id!\n");
        return -1;
    }else{
        precv = (msgQueue_t *)malloc(sizeof(msgQueue_t));
        if(precv == NULL){
            printf("failed malloc precv data \n");
            return -1;
        }

        memset((char *)precv,0,sizeof(msgQueue_t));
        if(msgrcv(msgid,(void *)precv,sizeof(msgQueue_t),0,IPC_NOWAIT) < 0){
            free(precv);
            return -1;
        }

        *len = precv->dlen;
        memcpy(rbuf,(void *)precv->buf,precv->dlen);

        free(precv);
    }
    return 0;
}

