/*
 * Progarm Name: process-rela.c
 * Created Time: 2017-02-14 09:39:50
 * Last modified: 2017-02-14 13:45:03
 * @author: minphone.linails linails@foxmail.com 
 */

#include "process-rela.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

static int process_group(void);

static int process_session(void);

//---------------------------------------------------------------------------------------

int process_rela(void)
{
    int ret = 0;

    printf("process-rela ... \n");
    {
        ret = process_group();
    }
    printf("---------------------------\n");
    {
        ret = process_session();
    }

    printf("---------------------------\n");

    return ret;
}

/* 
 * linux 下每个进程都隶属于一个进程组，因此它们除了 PID 信息外，还有进程组 ID(PGID)
 *
 *  #include <unistd.h>
 *  pid_t getpgrp(void);
 *   -> 返回调用进程的进程组ID
 *
 *  #include <unistd.h>
 *  pid_t getpgid(pid_t pid);
 *   -> 返回进程组ID
 *   -> 每个进程组都有一个首领进程，其 PGID 和 PID 相同, 进程组将一直存在，
 *   -> 直到其中所有进程都退出，或者加入到其他进程组
 *
 *  #include <unistd.h>
 *  int setpgid(pid_t pid, pid_t pgid);
 *   -> 将 PID 为 pid 的进程的 PGID 设置为 pgid。
 *
 * */
int process_group(void)
{
    /*
     * Note :
     *  一个进程只能设置自己或者其子进程的 PGID
     *  并且，当子进程调用 exec 系列函数后，也不能再在父进程中对它设置 PGID
     * */

    /* 
     *  #include <sys/types.h>
     *  #include <unistd.h>
     *  pid_t fork(void);
     *      -> 成功时返回进程ID，失败返回-1
     *         父进程: fork()返回进程ID
     *         子进程: fork()返回0
     * */

    int ret = 0;

    pid_t pid = 0;

    if(0 > (pid = fork())){
        printf("[Error] : fork error !\n");
    }else if (0 == pid){
        printf("\n");
        printf("child proc ... pid = %d\n", getpid());
        printf("The Group ID is %d - getpgrp()\n", getpgrp());
        printf("The Group ID is %d - getpgid(0)\n", getpgid(0));
        printf("The Group ID is %d - getpgid(getpid())\n", getpgid(getpid()));
        exit(0);
    }else{
        usleep(1000 * 10);
        printf("The parent process PID is %d \n", getpid());
        printf("The Group ID is %d - getpgrp()\n", getpgrp());
    }

    return ret;
}

/* 
 * 进程会话
 *
 *  一些有关联的进程组将形成一个会话(session)
 *
 *  #include <unistd.h>
 *  pid_t setsid(void);
 *  *  01. 此函数不能由进程组的首领进程调用，否则将产生一个错误
 *  *  02. 对于非组首领的进程调用，会产生如下结果
 *       ->创建新会话
 *       ->调用进程成为会话的首领，此时该进程是新会话的唯一成员
 *       ->新建一个进程组，其PGID就是调用进程的PID，调用进程成为该组的首领
 *       ->调用进程将甩开终端
 *       ->返回新的进程组的PGID
 *
 *  #include <unistd.h>
 *  pid_t getsid(pid_t pid);
 * */
int process_session(void)
{
    int ret = 0;

    return ret;
}


