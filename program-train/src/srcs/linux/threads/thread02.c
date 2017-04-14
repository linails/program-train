/*
 * Progarm Name: main.c
 * Created Time: 2016-05-30 22:59:33
 * Last modified: 2016-11-27 10:36:10
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thread02.h"

void *thread_func(void *arg);

volatile int flag = 1;

int thread02_main(void)
{
    int         ret;
    pthread_t   thread_a;
    void       *thread_result;
    int         count   = 1;

    if(0 != (ret = pthread_create(&thread_a, NULL, thread_func, NULL))){
        perror("thread_a creation failed!");
        exit(EXIT_FAILURE);
    }

    flag = 1;
    while(count++ <= 20){
        if(flag == 1){
            printf("1\n");
            flag = 2;
        }else{
            usleep(1000 * 1000);
        }
    }

    if(0 != (ret = pthread_join(thread_a, &thread_result))){
        perror("thread_a join failed!");
        exit(EXIT_FAILURE);
    }

    printf("thread joined , it returned : %s\n",(char *)thread_result);

    return 0;
}

void *thread_func(void *arg)
{
    printf("thread_fun running...\n");
    int count   = 1;

    while(count++ <= 20){
        if(flag == 2){
            printf("2\n");
            flag = 1;
        }else{
            sleep(1);
        }
    }
    pthread_exit("Thank you for your cpu time");
}

