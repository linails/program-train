/*
 * Progarm Name: endian-conv.c
 * Created Time: 2016-10-23 17:25:44
 * Last modified: 2016-10-29 11:06:39
 * @author: minphone.linails linails@foxmail.com 
 */

#include "endian-conv.h"
#include <stdio.h>
#include <arpa/inet.h>

/* 
 * 地址与字节转换：
 *      unsigned short htons(unsigned short);
 *      unsigned short ntohs(unsigned short);
 *      unsigned long htonl(unsigned long);
 *      unsigned long ntohl(unsigned long);
 * */

void endian_conv(void)
{
    printf("------------ endian-conv ------------\n");

    unsigned short host_port    = 0x1234;
    unsigned short net_port     = 0;

#if 0
    unsigned long host_addr     = 0x12345678;
    unsigned long net_addr      = 0;
#else
    unsigned int host_addr      = 0x12345678;
    unsigned int net_addr       = 0;
#endif

    net_port    = htons(host_port);
    net_addr    = htonl(host_addr);

    printf("Host ordered port : %#x\n", host_port);
    printf("Network ordered port : %#x\n", net_port);

    printf("Host ordered addr : %#x\n", host_addr);
    printf("Network ordered addr : %#x\n", net_addr);
}

