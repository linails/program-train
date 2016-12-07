/*
 * Progarm Name: process.cpp
 * Created Time: 2016-12-02 17:31:52
 * Last modified: 2016-12-06 23:04:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "process.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/wait.h>

using std::cout;
using std::endl;

Process::Process()
{
    cout << " ... process init ... " << endl;
}

Process::~Process()
{
}

int Process::process_main(int argc, char **argv)
{
    int ret = 0;

    //ret = this->fork_child_porc();

    //ret = this->zombie();

    //ret = this->destroy_zombie();

    ret = this->destroy_zombie(1);

    return ret;
}

/* 
 * 所有分配到的进程ID，都是一个大于2的整数，1是分配给系统的启动后的首个进程(非用户进程)
 * */
int Process::fork_child_porc(void)
{
    /* 
     *  #include <unistd.h>
     *  pid_t fork(void);
     *      -> 成功时返回进程ID，失败返回-1
     *         父进程: fork()返回进程ID
     *         子进程: fork()返回0
     *
     *  fork()函数创建调用的进程的副本
     * */

    pid_t   pid = 0;

    this->m_global = 0;

    int local = 0;

    if(0 == (pid = fork())){
        cout << "child proc ..." << endl;
        this->m_global += 1;
        local += 1;
    }else{
        cout << "parent proc ..." << " child pid = " << pid << endl;
        this->m_global += 2;
        local += 2;
    }


    if(0 == pid){
        printf("child proc m_global : %d - local : %d\n", this->m_global, local);
    }else{
        printf("parent proc m_global : %d - local : %d\n", this->m_global, local);
    }

    return 0;
}

int Process::zombie(void)
{
    /* 
     * 1> 操作系统不会主动把这些值传递给父进程
     *    只有父进程主动发起请求时，操作系统才传递该值
     *
     * 2> 如果父进程未主动要求获得子进程的结束状态值，操作系统将一直保存，并让子进程长时间处于僵尸进程状态
     *    因此父进程有负责回收子进程的责任
     * */

    pid_t   pid = 0;

    if(0 == (pid = fork())){
        cout << "child proc ..." << endl;
    }else{
        /*  
         *  在父进程未退出的情况下，可以 ps -au 查看子进程状态
         *  */
        cout << "parent proc ..." << " child pid = " << pid << endl;
        sleep(5);
    }

    if(0 == pid){
        cout << "End child process" << endl;
    }else{
        cout << "End parent process" << endl;
    }

    return 0;
}

/*
 * 为了销毁子进程，父进程应主动请求获取子进程的返回值
 * */
int Process::destroy_zombie(void)
{
    cout << " wait() " << endl;

    /* 
     *
     *  #include <sys/wait.h>
     *  pid_t wait(int *statloc);
     *      -> 成功时返回终止的子进程ID，失败返回-1
     *
     *  [调用 wait 函数时，如果没有已终止的子进程，那么程序将阻塞，直到有子进程终止]
     * */

    pid_t   pid = 0;

    if(0 == (pid = fork())){
        cout << "child proc ..." << endl;
    }else{
        printf("parent proc pid [%d] - child pid [%d]\n", getpid(), pid);

        if(0 == (pid = fork())){
            cout << "sub child proc ..." << endl;
            /* 
             * 向exit()函数传递的参数值和main()函数的return语句返回的值都会传递给操作系统
             * */
            exit(20);
        }else{
            printf("parent proc pid [%d] - child pid [%d]\n", getpid(), pid);

            int status;

            /* 
             * WIFEXITED    : 子进程是否正常终止，是则返回 true
             * WEXITSTATUS  : 返回子进程的返回值
             * */
            wait(&status);
            if(WIFEXITED(status)){
                printf("child return : %d\n", WEXITSTATUS(status));
            }
            wait(&status);
            if(WIFEXITED(status)){
                printf("child return : %d\n", WEXITSTATUS(status));
            }
            sleep(5);
        }
    }

    if(0 == pid){
        cout << "child exit , return 10" << endl;
        return 10;
    }else{
        cout << "parent exit" << endl;
    }
    return 0;
}

int Process::destroy_zombie(int)
{
    cout << " waitpid() " << endl;

    /* 
     *
     *  #include <sys/wait.h>
     *  pid_t waitpid(pid_t pid, int *statloc, int options);
     *      -> 成功时返回终止的子进程ID，失败返回-1
     *      -- pid     : 等待终止的目标子进程的ID，若传递-1，则与wait函数相同，可以等待任意子进程终止
     *      -- statloc : 与wait函数的statloc参数具有相同含义
     *      -- options : 传递头文件 sys/wait.h 中声明的常量 WNOHANG, 即使没有终止的子进程也不会进入阻塞状态，
     *                   而是返回0并退出函数 <-
     *
     *  [调用wait函数会引起程序阻塞，则waitpid函数则不会]
     *  [没有终止的子进程的时候，会返回0]
     *  
     * */

    pid_t   pid = 0;

    if(0 == (pid = fork())){
        cout << "child proc ..." << endl;
        sleep(5);
    }else{
        printf("parent proc pid [%d] - child pid [%d]\n", getpid(), pid);

        if(0 == (pid = fork())){
            cout << "sub child proc ..." << endl;
            sleep(3);
            /* 
             * 向exit()函数传递的参数值和main()函数的return语句返回的值都会传递给操作系统
             * */
            exit(20);
        }else{
            printf("parent proc pid [%d] - child pid [%d]\n", getpid(), pid);

            int status;

            while(0 == waitpid(-1, &status, WNOHANG)){
                sleep(1);
                cout << "waiting ..." << endl;
            }

            if(WIFEXITED(status)){
                printf("child return : %d\n", WEXITSTATUS(status));
            }

            while(0 == waitpid(-1, &status, WNOHANG)){
                sleep(1);
                cout << "waiting ..." << endl;
            }
            if(WIFEXITED(status)){
                printf("child return : %d\n", WEXITSTATUS(status));
            }
            sleep(1);
        }
    }

    if(0 == pid){
        cout << "child exit , return 10" << endl;
        return 10;
    }else{
        cout << "parent exit" << endl;
    }
    return 0;
}




