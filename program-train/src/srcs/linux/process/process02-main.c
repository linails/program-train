/*
 * Created Time: 2015-08-25 11:26:05
 * Last modified: 2016-11-27 11:02:37
 * @author: minphone.linails linails@foxmail.com 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "process02-main.h"

int process02_main(void)
{
    /*命令参数列表，必须以NULL结尾*/
    char *envp[]={"PATH=/tmp","USER=sunq",NULL};
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
        /*调用execle函数，注意这里也要指出env的完整路径*/
        if(execle("/bin/env","env",NULL,envp)<0){
            perror("execle error!");
        }
    }else{
        printf("father process ...,pid=%d\n",getpid());
        printf("father process's father process ...,pid=%d\n",getppid());
    }
    return 0;
}

