/*
 * Progarm Name: ipc_msgq.h
 * Created Time: 2016-05-05 14:17:06
 * Last modified: 2016-05-05 14:51:53
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#ifndef _IPC_MSGQ_H_
#define _IPC_MSGQ_H_
#ifdef __cplusplus
extern "C" {
#endif

/*ipc - msg queue send - success return 0*/
extern int ipc_msg_send(char *sbuf,int len);

/*ipc - msg queue recv - success return 0*/
extern int ipc_msg_recv(char *rbuf,int *len);

#ifdef __cplusplus
}
#endif
#endif //_IPC_MSGQ_H_

