/*
 * Progarm Name: server-tcp.h
 * Created Time: 2016-10-06 00:01:40
 * Last modified: 2016-10-30 20:13:58
 */

#ifndef _SERVER_TCP_H_
#define _SERVER_TCP_H_
#ifdef __cplusplus
extern "C" {
#endif

    extern int server_tcp_main(int argc, char **argv);

/*  
 *  POSIX 中定义的数据类型
 *
 *  sa_family_t    |    地址族(address family)       |      sys/socket.h
 *  socklen_t      |    长度(length of struct)       |      sys/socket.h
 *  --------------------------------------------------------------------
 *  in_addr_t      |    IP地址，uint32_t             |      netinet/in.h
 *  in_port_t      |    port , uint16_t              |      netinet/in.h
 *
 *  */

/*  
 *  IPv4 地址结构体
 *
 *  struct sockaddr_in{
 *      sa_family_t     sin_family;     // 地址族(Address Family)  取值：{ AF_INET / AF_INET6 / AF_LOCAL }
 *      uint16_t        sin_port;       // 16 bit TCP/UDP port
 *      struct in_addr  sin_addr;       // 32 bit IP addr
 *      char            sin_zero[8];    // 不使用, 必须填充0
 *                                      // 只是为了使该结构体与 sockaddr 结构体保持一致
 *                                      // struct sockaddr 见 readme.txt 说明
 *  }
 *
 *  struct in_addr{
 *      In_addr_t       s_addr;         // 32 bit IPv4 addr
 *  }
 *  */

/*
 * IP 本身是面向消息的，不可靠的协议
 *
 * TCP和UDP存在与IP之上，决定主机之间的数据传输方式，TCP协议确认后向不可靠的IP协议赋予可靠性
 * */

#ifdef __cplusplus
}
#endif //_SERVER_TCP_H_
#endif

