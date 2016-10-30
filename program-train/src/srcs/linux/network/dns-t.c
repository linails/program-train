/*
 * Progarm Name: dns-t.c
 * Created Time: 2016-10-30 15:17:21
 * Last modified: 2016-10-30 20:00:14
 * @author: minphone.linails linails@foxmail.com 
 */

#include "dns-t.h"
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

/* 
 * struct hostent{
 *      char *  h_name;         // official name, 该变量存储官方域名
 *      char ** h_aliases;      // alias list, 可以通过多个域名访问同一个主页，同一个IP可以绑定多个域名，这些信息记录于此
 *      int     h_addrtype;     // host address type, IP类型，v4 / v6
 *      int     h_length;       // address length
 *      char ** h_addr_list;    // address list - 域名转IP只需要关注这个参数
 * }
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * #include <netdb.h>
 *
 * struct hostent * gethostbyname(const char *hostname);
 *      -> 成功时返回 hostent 结构体，失败时返回 NULL 指针
 *
 * struct hostent * gethostbyaddr(const char * addr, socklen_t len, int family);
 *      -> 成功时返回 hostent 结构体
 *      - * addr    : 含有IP地址信息的 in_addr 结构体指针，为了同时传递IPv4地址之外的其他信息，该变量的类声明为char指针
 *      - * len     : 向第一个参数传递的地址信息的字节数
 *      - * family  : AF_INET / AF_INET6
 * */

int dns_tmain(int argc, char **argv)
{
    int ret = 0;

    struct in_addr ip;
    ip.s_addr = 0;

    /* get host by name */
    {
        struct hostent *host;

        /* 
         * 用谷歌的地址可以，用百度的实验了不行
         * */
        char * name = "www.google.com";

        printf("name : %s\n", name);
        host = gethostbyname(name);

        printf("official name : %s\n", host->h_name);
        for(int i=0; host->h_aliases[i]; i++){
            printf("aliases %d : %s\n", i+1, host->h_aliases[i]);
        }
        printf("address type : %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
        for(int i=0; host->h_addr_list[i]; i++){
            printf("IP addr %d : %s \n", i+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
            if(0 == ip.s_addr){
                ip.s_addr = ((struct in_addr*)host->h_addr_list[i])->s_addr;
                break;
            }
        }
    }

    /* get host by addr */
    {
        struct hostent *host = NULL;
        struct sockaddr_in addr;

        addr.sin_addr.s_addr = ip.s_addr;

        printf("IP addr : %s \n", inet_ntoa(ip));
        host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
        if(NULL == host){
            printf("gethost ... error\n");
        }else{
            printf("official name : %s\n", host->h_name);
        }
    }

    return ret;
}


