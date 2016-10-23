/*
 * Progarm Name: fd-test.c
 * Created Time: 2016-10-23 14:54:01
 * Last modified: 2016-10-23 15:01:47
 * @author: minphone.linails linails@foxmail.com 
 */

#include "fd-test.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

void fd_test(void)
{
    int fds[3];

    fds[0] = socket(PF_INET, SOCK_STREAM, 0);
    fds[1] = open("/home/minphone/linux_cmd.txt", O_RDONLY);
    fds[2] = socket(PF_INET, SOCK_DGRAM, 0);

    for(int i=0; i<3; i++){
        printf("fds[%d] : %d\n", i, fds[i]);
    }

    for(int i=0; i<3; i++){
        close(fds[i]);
    }
}



