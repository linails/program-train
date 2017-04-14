/*
 * Progarm Name: main.c
 * Created Time: 2016-05-30 22:59:33
 * Last modified: 2016-11-27 10:38:32
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include "thread04.h"

void *thread_func(void *arg);

#define SIZE 1024

char buffer[SIZE];

pthread_mutex_t mutex;

int thread04_main(void)
{
    int         ret;
    pthread_t   thread_a;
    void       *thread_result;

    if(0 != (ret = pthread_mutex_init(&mutex, NULL))){
        perror("mutex init failed");
        exit(EXIT_FAILURE);
    }

    if(0 != (ret = pthread_create(&thread_a, NULL, thread_func, NULL))){
        perror("thread_a creation failed!");
        exit(EXIT_FAILURE);
    }

    printf("input some test . enter 'end' to finish\n");
    while(1){
        pthread_mutex_lock(&mutex);
        scanf("%s",buffer);
        pthread_mutex_unlock(&mutex);
        if(0 == strncmp("end", buffer, 3))  break;
        usleep(100);
    }

    if(0 != (ret = pthread_join(thread_a, &thread_result))){
        perror("thread_a join failed!");
        exit(EXIT_FAILURE);
    }

    printf("thread joined , it returned : %s\n",(char *)thread_result);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void *thread_func(void *arg)
{
    printf("thread_fun running...\n");

    while(1){
        pthread_mutex_lock(&mutex);
        printf("You input %d characters\n", (int)strlen(buffer));
        pthread_mutex_unlock(&mutex);
        if(0 == strncmp("end", buffer, 3))  break;
        usleep(100);
    }

    pthread_exit("Thank you for your cpu time");
}

