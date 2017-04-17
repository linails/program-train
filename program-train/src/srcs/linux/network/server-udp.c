/*
 * Progarm Name: server-udp.c
 * Created Time: 2016-10-06 00:01:59
 * Last modified: 2016-10-23 23:17:36
 */

#include "server-udp.h"
#include <stdio.h>

/* 
 * * UDP 提供不可靠的数据传输服务
 *
 * * UDP 不会发送类似 ACK 的应答消息，也不会像 SEQ 那样给数据包分配序号
 *
 * * UDP 和 TCP 最主要差异(算核心差异了)只在于流控制
 *
 * * 每次交换的数据量越大，则 TCP 的传输速率就越接近 UDP 的传输速率
 *
 * * TCP 比 UDP 慢的原因通常有以下两点：
 *      <1> 收发数据前后进行的连接设置及清除过程
 *      <2> 收发数据过程中为保证可靠性而添加的流控制
 * */

int server_udp_main(int argc, char **argv)
{
    printf("------ server_udp_main ------\n");
    {
    }
    printf("-----------------------------\n");
    {
    }
    return 0;
}

