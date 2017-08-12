/*
 * Progarm Name: process-xx.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

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




#include <string.h>
#include <fcntl.h>

#define MAXFILE 0xffff

/*  daemon 守护进程实验 */
int process03_main(void)
{
    pid_t result;
    int i,fd,len;
    char *buf="This is a Daemon\n";
    char *filename="/home/minphone/workspace/linux_space/test05/daemon.log";
    len=strlen(buf);

    printf("pid=%d\n",getpid());
    printf("ppid=%d\n",getppid());
    /*the first step*/
    result = fork();
    if(result == -1){
        perror("fork");	
        exit(1);
    }else if(result>0){
        printf("father process ...,pid=%d\n",getpid());
        printf("father process's father process ...,pid=%d\n",getppid());
        exit(0);
    }else{
        printf("process ...,pid=%d\n",getpid());
        printf("process's father process ...,pid=%d\n",getppid());
    }
    /*the sencond step*/
    setsid();
    /*the third step*/
    chdir("/");
    /*the forth step*/
    umask(0);
    for(i=0;i<MAXFILE;i++){
        /*the fifth step*/
        close(i);	
    }
    /*dameon progress start*/
    while(1){
        if((fd=open(filename,O_CREAT|O_WRONLY|O_APPEND,0600))<0){
            perror("open");
            exit(1);
        }
        write(fd,buf,len+1);
        close(fd);
        sleep(10);
    }
    return 0;
}


