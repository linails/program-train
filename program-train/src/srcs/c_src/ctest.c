/*
 * Progarm Name: ctest.c
 * Created Time: 2016-05-14 19:56:38
 * Last modified: 2016-05-14 20:12:23
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include "ctest.h"
#include <stdlib.h>
#include <stdio.h>

/*ctest*/
void ctest(void)
{
    printf("--------------------------- ctest ---------------------------\n");
    {
        int test01(void);
        printf("test01 return : %d\n",test01());
    }
    printf("--------------------------- ----- ---------------------------\n");
}

int test01(void)
{
    printf("sizeof(int) : %d - 0x%x\n",sizeof(int),sizeof(int));
    printf("1 - sizeof(int) : %d - 0x%x\n",1 - sizeof(int),1 - sizeof(int));
    printf("(1 - sizeof(int)) >> 32 : %d - 0x%x\n",(1 - sizeof(int)) >> 32,(1 - sizeof(int)) >> 32);
    return ((1 - sizeof(int)) >> 32);
}

