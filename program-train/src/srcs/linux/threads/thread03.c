/*
 * Progarm Name: main.c
 * Created Time: 2016-05-30 22:59:33
 * Last modified: 2016-11-27 10:37:14
 * @author: minphone.linails linails@foxmail.com 
 * @version 0.0.1
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include "thread03.h"

void *thread_func(void *arg);

#define SIZE 1024

char buffer[SIZE];
sem_t   sem;

int thread03_main(void)
{
    int         ret;
    pthread_t   thread_a;
    void       *thread_result;

    if(0 != (ret = sem_init(&sem, 0, 0))){
        perror("sem init failed");
        exit(EXIT_FAILURE);
    }

    if(0 != (ret = pthread_create(&thread_a, NULL, thread_func, NULL))){
        perror("thread_a creation failed!");
        exit(EXIT_FAILURE);
    }

    printf("input some test . enter 'end' to finish\n");
    while(scanf("%s",buffer)){
        sem_post(&sem);
        if(0 == strncmp("end", buffer, 3))  break;
    }

    if(0 != (ret = pthread_join(thread_a, &thread_result))){
        perror("thread_a join failed!");
        exit(EXIT_FAILURE);
    }

    printf("thread joined , it returned : %s\n",(char *)thread_result);

    sem_destroy(&sem);

    return 0;
}

void *thread_func(void *arg)
{
    printf("thread_fun running...\n");
    sem_wait(&sem);

    while(0 != strncmp("end", buffer, 3)){
        printf("You input %d characters\n", (int)strlen(buffer));
        sem_wait(&sem);
    }
    pthread_exit("Thank you for your cpu time");
}

