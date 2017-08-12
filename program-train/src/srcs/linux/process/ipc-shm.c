/*
 * Progarm Name: ipc-shm.c
 * Created Time: 2017-07-15 21:50:00
 * Last modified: 2017-07-15 22:10:07
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ipc-shm.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

/* 
 * #include <sys/types.h>
 * #include <sys/shm.h>
 *
 * int shmget(key_t key, size_t size, int shmflg);
 *  -> returns shared memory segment identifier on success, or -1 on error
 *
 * */


int  shm_init(void)
{
    return 0;
}


