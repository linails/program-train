/*
 * Progarm Name: main.c
 * Created Time: 2016-05-30 22:59:33
 * Last modified: 2016-11-27 10:34:38
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thread01.h"

void *thread_func(void *arg);

char msg[] = "hello world";

int thread01_main(void)
{
    int         ret;
    pthread_t   thread_a;
    pthread_t   thread_b;
    void       *thread_result;

    if(0 != (ret = pthread_create(&thread_a, NULL, thread_func, (void *)" - 001"))){
        perror("thread_a creation failed!");
        exit(EXIT_FAILURE);
    }
    if(0 != (ret = pthread_create(&thread_b, NULL, thread_func, (void *)" - 002"))){
        perror("thread_a creation failed!");
        exit(EXIT_FAILURE);
    }

    if(0 != (ret = pthread_join(thread_a, &thread_result))){
        perror("thread_a join failed!");
        exit(EXIT_FAILURE);
    }
    if(0 != (ret = pthread_join(thread_b, &thread_result))){
        perror("thread_a join failed!");
        exit(EXIT_FAILURE);
    }

    printf("thread joined , it returned : %s\n",(char *)thread_result);
    printf("msg is now : %s\n",msg);

    return 0;
}

void *thread_func(void *arg)
{
    for(int i=0; i<10; i++){
        printf("thread func is running , arg was : %s\n",(char *)arg);
        sleep(2);
#if 0
        memset(arg, 0, 11);
        memcpy(arg, "nice to", 8);
#endif
    }
    pthread_exit("Thank you for your cpu time");
}

