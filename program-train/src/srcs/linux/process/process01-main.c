/*
 * Progarm Name: main.c
 * Created Time: 2015-08-25 11:26:05
 * Last modified: 2016-11-27 11:00:33
 * @author: minphone.linails linails@foxmail.com 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "process01-main.h"

int process01_main(void)
{
    pid_t result;
    printf("pid=%d\n",getpid());
    printf("ppid=%d\n",getppid());
    result = fork();
    if(result == -1){
        perror("fork");	
        exit(0);
    }else if(result == 0){
        printf("child process ...,pid=%d\n",getpid());
        printf("child process's father process ...,pid=%d\n",getppid());
        /*调用execlp函数，这里相当于调用了"ps -ef"命令*/
        if(execlp("ps","ps","-ef",NULL)<0){
            perror("execlp error!");
        }
    }else{
        printf("father process ...,pid=%d\n",getpid());
        printf("father process's father process ...,pid=%d\n",getppid());
    }
    return 0;
}

