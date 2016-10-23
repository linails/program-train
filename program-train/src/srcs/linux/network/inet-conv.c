/*
 * Progarm Name: inet-addr.c
 * Created Time: 2016-10-23 17:44:16
 * Last modified: 2016-10-23 20:08:27
 * @author: minphone.linails linails@foxmail.com 
 */

#include "inet-conv.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

/* 
 * #include <arpa/inet.h>
 *
 *
 * in_addr_t  inet_addr(const char *string);
 *      --> successed Return : 32 bit Network ordered int 
 *      --> failed Return    : INADDR_NONE
 *
 * * 此函数可以将字符串形式的IP地址转换成32位整型数据，同时进行网络字节序转换
 * * 还可以进行地址验证是否合法
 *
 *
 * int  inet_aton(const char *string, strut in_addr *addr);
 *      - * string  : 含有需转换的IP地址信息的字符串地址值
 *      - * addr    : 将保存转换结果的 in_addr 结果体变量的地址值
 *
 *      --> successed Return 1
 *      --> failed Return 0
 *      这个返回得注意
 *
 *
 * char *inet_ntoa(struct in_addr adr);
 *      --> 成功返回字符串地址，失败返回-1
 *      注意：内部有缓存，不可重入
 * */

void inet_conv_test(void)
{
    char *addr[] = {
        "1.2.3.4",
        "192.168.56.101",
        "1.2.3.256",
    };

    {
        printf(" -- inet_addr() Exercise :\n");
        for(int i=0; i<sizeof(addr)/sizeof(char *); i++){

            printf("addr[%d] : %s\n", i, addr[i]);

            unsigned int conv_addr = inet_addr(addr[i]);
            if(INADDR_NONE == conv_addr){
                printf("Error occured - addr[%d] error!\n", i);
            }else{
                printf("Network ordered integer addr : %#x  --> ", conv_addr);
                printf("(int)%d.%d.%d.%d\n", 
                        (int)(((unsigned char *)&conv_addr)[0]), 
                        (int)(((unsigned char *)&conv_addr)[1]), 
                        (int)(((unsigned char *)&conv_addr)[2]), 
                        (int)(((unsigned char *)&conv_addr)[3])
                        );
            }
            printf("\n");
        }
    }
    printf("\n");
    {
        printf(" -- inet_aton() Exercise :\n");
        for(int i=0; i<sizeof(addr)/sizeof(char *); i++){

            printf("addr[%d] : %s\n", i, addr[i]);

            //struct in_addr conv_addr;
            unsigned int conv_addr = 0;
            int ret = inet_aton(addr[i], &conv_addr);    // 这个返回得注意 , 0表示失败
            if(0 == ret){
                printf("Error occured - addr[%d] error!\n", i);
            }else{
                printf("Network ordered integer addr : %#x  --> ", conv_addr);
                printf("(int)%d.%d.%d.%d\n", 
                        (int)(((unsigned char *)&conv_addr)[0]), 
                        (int)(((unsigned char *)&conv_addr)[1]), 
                        (int)(((unsigned char *)&conv_addr)[2]), 
                        (int)(((unsigned char *)&conv_addr)[3])
                        );
            }
            printf("\n");
        }
    }
    printf("\n");
    {
        printf(" -- inet_ntoa() Exercise :\n");

        struct sockaddr_in addr1, addr2;
        char *str_ptr = NULL;

        addr1.sin_addr.s_addr = htonl(0x01020304);
        addr2.sin_addr.s_addr = htonl(0x01010101);

        str_ptr = inet_ntoa(addr1.sin_addr);
        printf("addr1.sin_addr : %s\n", str_ptr);

        inet_ntoa(addr2.sin_addr);
        printf("addr2.sin_addr : %s\n", str_ptr);
    }
}

