/*
 * Progarm Name: socket-opt.h
 * Created Time: 2016-10-30 20:15:32
 * Last modified: 2016-10-30 21:46:17
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _SOCKET_OPT_H_
#define _SOCKET_OPT_H_
#ifdef __cplusplus
extern "C" {
#endif

/* 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *     协议层      |        选项名         |        读取       |     设置
 *----------------------------------------------------------------------------
 *                         SO_SNDBUF                  O                O
 *                         SO_RCVBUF                  O                O
 *                         SO_REUSEADDR               O                O
 *                         SO_KEEPALIVE               O                O
 *   SOL_SOCKET            SO_BROADCAST               O                O
 *                         SO_DONTROUTE               O                O
 *                         SO_OOBINLINE               O                O
 *                         SO_ERRORF                  O                X
 *                         SO_TYPE                    O                X
 *----------------------------------------------------------------------------
 *                         IP_TOS                     O                O
 *                         IP_TTL                     O                O
 *   IPPROTO_IP            IP_MULTICAST_TTL           O                O
 *                         IP_MULTICAST_LOOP          O                O
 *                         IP_MULTICAST_IF            O                O
 *----------------------------------------------------------------------------
 *                         TCP_KEEPALIVE              O                O
 *   IPPROTO_TCP           TCP_NODELAY                O                O
 *                         TCP_MAXSEG                 O                O
 *----------------------------------------------------------------------------
 *
 * #include <sys/socket.h>
 *
 * int getsockopt(int sock, int level, void *optval, socklen_t *optlen);
 *      - * sock    : 用于查看选项套接字文件描述符
 *      - * level   : 要查看的可选项的协议层
 *      - * optname : 要查看的可选项名
 *      - * optval  : 保存查看结果的缓冲地址值
 *      - * optlen  : 向第四个参数optval传递的缓冲大小，调用函数后，该变量中保存通过第四个参数返回的可
 *                    选项信息的字节数
 *
 * int setsockopt(int sock, int level, int optname, const void *optval, socklen_t optlen);
 *      - * sock    : 用于更改可选项的套接字文件描述符
 *      - * level   : 要更改的可选项协议层
 *      - * optname : 要更改的可选项名
 *      - * optval  : 保存要更改的选项信息的缓冲地址值
 *      - * optlen  : 向第四个参数optval传递的可选项信息的字节数
 *
 * */

extern int sock_opt_main(int argc, char **argv);

#ifdef __cplusplus
}
#endif
#endif //_SOCKET_OPT_H_

