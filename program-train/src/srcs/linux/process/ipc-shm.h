/*
 * Progarm Name: ipc-shm.h
 * Created Time: 2017-07-15 21:49:54
 * Last modified: 2017-07-15 22:08:11
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _IPC_SHM_H_
#define _IPC_SHM_H_
#ifdef __cplusplus
extern "C" {
#endif


    /*
     * printf("&i = 0x%x\n", (unsigned int)(unsigned long)&i);
     * */

    /*
     * 共享内存被认为是最快的IPC通信方式
     *
     * 与使用管道、消息队列等方式相比，共享内存不需要在内核空间与用户空间的数据之间进行复制操作
     * 而是直接进行内存的读写
     *
     * ->[ 由于一个共享内存段会成为一个进程用户空间内存的一部分，因此这种ipc 不需要内核介入 ]
     *
     *
     *
     * 多个进程同时对共享内存空间进行操作的时候，就必须对共享内存控制的访问做同步，可以使用如下其中一种
     *  -> 1. system v信号量
     *     2. posix 信号量
     *     3. 文件锁
     * */

    /*
     * 使用共享内存方法/步骤:
     *  1>  调用 shmget() 创建一个新共享内存段或取得一个既有共享内存段的标识符, 返回共享内存标志
     *  2>  使用 shmat() 来附上共享内存段，即让该段成为调用进程的虚拟内存的一部分, 返回共享内存段的起始指针 addr
     *  3>  此刻在程序可以像对待其他可以使用的内存那样对待这个共享内存段
     *  4>  调用 shmdt() 来分离共享内存段 | 这步是可选的，进程终止后，会自动完成这个步骤
     *  5>  调用 shmctl() 来删除共享内存段，只有当当前所有附加内存段的进程都与之分离之后，次内存段才会被销毁
     *      只有一个进程需要执行此步骤
     * */


#ifdef __cplusplus
}
#endif
#endif //_IPC_SHM_H_

