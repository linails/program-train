/*
 * Created Time: 2015-08-25 11:26:05
 * Last modified: 2016-11-27 11:04:29
 * @author: minphone.linails linails@foxmail.com 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "process03-main.h"

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

