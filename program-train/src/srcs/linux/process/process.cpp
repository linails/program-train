/*
 * Progarm Name: process.cpp
 * Created Time: 2016-12-02 17:31:52
 * Last modified: 2016-12-10 20:53:54
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
#include <signal.h>
#include "timer.h"
#include "ipc_msgq.h"

using std::cout;
using std::endl;
using std::string;

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

    //ret = this->destroy_zombie(1);

    //ret = this->for_signal();

    //ret = this->for_sigaction();

    //ret = this->multiprocess_signal();

    //ret = this->multiprocess_signal(1);

    //ret = this->destroy_zombie_by_system();

    //ret = this->timing_create_process();

    //ret = this->communicate_by_pipe();

    //ret = this->communicate_by_pipe(1);

    ret = this->communicate_by_msg();

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

int Process::destroy_zombie_by_system(void)
{
    auto read_childproc = [](int sig) -> void{

        if(sig == SIGCHLD){
            int status;
            pid_t pid = 0;

            if(0 == (pid = waitpid(-1, &status, WNOHANG))){
                cout << "error ..." << endl;
            }else{
                if(WIFEXITED(status)){
                    printf("removed child pid : %d -  return : %d\n", pid, WEXITSTATUS(status));
                }
            }
        }
    };

    pid_t pid = 0;

    struct sigaction act;

    act.sa_handler  = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags    = 0;

    sigaction(SIGCHLD, &act, 0);

    if(0 == (pid = fork())){
        cout << "child process pid : " << getpid() << endl;
        sleep(1);
    }else{
        cout << "parent process - child pid : " << pid << endl;
        sleep(5);
    }

    if(0 == pid){
        cout << "end child , return 12" << endl;
        return 12;
    }else{
        cout << "end parent" << endl;
    }
    
    return 0;
}

int  Process::for_signal(void)
{
    /* 
     * 子进程终止的识别主体是操作系统
     * 因此从操作系统获得这些信息告诉父进程，有助于构建高效程序
     *
     *  -> 这里就引入信号处理机制
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     *  #include <signal.h>
     *  void (*signal(int signo, void(*func)(int)))(int);
     *      -> 返回注册的函数指针
     *      -- signo    : 表示特殊情况信息
     *      -- func     : 表示特殊情况下将要调用的函数的地址
     *
     *      [
     *          可以在 signal 函数中注册的部分特殊情况：
     *          1> SIGALRM  : 已到通过调用alarm函数注册的时间
     *          2> SIGINT   : 输入 CTRL + C
     *          3> SIGCHLD  : 子进程终止
     *      ]
     *
     *
     *  #include <unistd.h>
     *  unsigned int alarm(unsigned int seconds);
     *      -> 返回 0 或以秒为单位的距离 SIGALRM 信号发生所剩时间
     *      [
     *          1> 如果调用该函数的同时，向它传递一个正整数，相应时间后将产生 SIGALRM 信号发生所剩时间
     *          2> 如果传递0，则之前对 SIGALRM 信号的预约将取消
     *      ]
     * */

    cout << "For signal ..." << endl;

    signal(SIGALRM, Process::timeout_cb);
    signal(SIGINT, Process::keyctrl_cb);

    alarm(2);

    /* 
     * 这里需要注意一个问题：
     *
     *  产生信号时，系统会将处于 sleep 状态的进程唤醒；因此这个时候如果睡眠时间不到10s，则提前结束睡眠
     *  因此这里的 for 循环中在 CTRL+C 触发 SIGINT 的时候，会提前结束睡眠，就导致没有 sleep(10) 的效果
     * */
    for(int i=0; i<3; i++){
        cout << "sleeping" << endl;
        sleep(6);
        cout << "wake up" << endl;
    }

    return 0;
}

int  Process::for_sigaction(void)
{
    /*  
     *  signal 函数在 UNIX 系列的不同操作系统中可能存在区别，但 sigaction 函数完全相同
     *  因此 signal 函数很少使用，只是为了保持对旧程序的兼容
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     * 
     *  #include <signal.h>
     *  int sigaction(int signo, const struct sigaction *act, struct sigaction *oldact);
     *      -> 成功返回0 ，失败返回-1
     *      -- signo    : 与 signal 函数相同，传递信号消息
     *      -- act      : 对应于第一个参数的信号处理函数信息
     *      -- oldact   : 通过此参数获取之前注册的信号处理函数指针, 若不需要则传递0
     *
     *      struct sigaction{
     *          void (*sa_handler)(int);    // 保存信号处理函数的地址
     *          sigset_t    sa_mask;        // \__这2个成员用于指定信号相关的选项和特性
     *          int         sa_flags;       // /
     *      }
     *  */

    cout << "For sigaction ..." << endl;

    struct sigaction act;

    act.sa_handler  = Process::timeout_cb;
    sigemptyset(&act.sa_mask);
    act.sa_flags    = 0;

    sigaction(SIGALRM, &act, 0);

    alarm(2);

    for(int i=0; i<3; i++){
        sleep(4);
        cout << "wake up ..." << endl;
    }

    return 0;
}

int  Process::multiprocess_signal(void)
{
    cout << "multiprocess signal ..." << endl;

    /* 
     * multiprocess signal
     *
     * 信号在哪一个进程中注册，仅对哪一个进程有效
     *
     * 父进程提前退出后，子进程的父进程就变成了 pid = 1 进程
     * */

    pid_t pid = 0;

    struct sigaction act;

    act.sa_handler  = Process::timeout_cb;
    sigemptyset(&act.sa_mask);
    act.sa_flags    = 0;

    sigaction(SIGALRM, &act, 0);

    alarm(2);

    if(0 == (pid = fork())){
        cout << "child process -> pid : " << getpid() << endl;
        for(int i=0; i<10; i++){
            sleep(1);
            cout << "child -> parent pid : " << getppid() << endl;
            /* 
             * 此处在父进程的 SIGALRM 信号触发退出后，子进程的父进程变成了 PID = 1 的进程
             * */
        }
    }else{
        cout << "parent process -> pid : " << getpid() << " - child-pid : " << pid << endl;
        sleep(10);
    }

    if(0 == pid){
        cout << "end child process" << endl;
    }else{
        cout << "end parent process" << endl;
    }

    return 0;
}

int  Process::multiprocess_signal(int)
{
    cout << "multiprocess signal ..." << endl;

    pid_t pid = 0;
    
    if(0 == (pid = fork())){
        cout << "child process -> pid : " << getpid() << endl;
        sleep(1);
    }else{
        cout << "parent process -> pid : " << getpid() << " - child-pid : " << pid << endl;
        sleep(1);
    }

    struct sigaction act;

    act.sa_handler  = Process::timeout_cb;
    sigemptyset(&act.sa_mask);
    act.sa_flags    = 0;

    /* 此处注册的信号函数，分别作用于父进程和子进程 */
    sigaction(SIGALRM, &act, 0);

    alarm(2);

    sleep(10);

    if(0 == pid){
        cout << "end child process" << endl;
    }else{
        cout << "end parent process" << endl;
    }

    return 0;
}

void Process::timeout_cb(int sig)
{
    if(sig == SIGALRM){
        printf("Time out - pid : %d ! \n", getpid());
    }
}

void Process::keyctrl_cb(int sig)
{
    if(sig == SIGINT){
        printf("CTRL+C pressed - pid : %d ! \n", getpid());
    }
}

/* 
 * 用于粗略检测创建线程所需要的时间 
 *  
 *  本机测试创建进程需要 3-8ms 的时间
 * */
int  Process::timing_create_process(void)
{
    cout << "Timing create process !" << endl;

    auto read_childproc = [](int sig) -> void{

        if(sig == SIGCHLD){
            int status;
            pid_t pid = 0;

            if(0 == (pid = waitpid(-1, &status, WNOHANG))){
                cout << "error ..." << endl;
            }else{
                if(WIFEXITED(status)){
                    printf("removed child pid : %d -  return : %d\n", pid, WEXITSTATUS(status));
                }
            }
        }
    };

    pid_t pid = 0;

    {
#if 1
        struct sigaction act;

        act.sa_handler  = read_childproc;
        sigemptyset(&act.sa_mask);
        act.sa_flags    = 0;

        sigaction(SIGCHLD, &act, 0);
#endif
    }

    Timer timer;

    /* Timing ... */
    timer.timing();

    if(0 == (pid = fork())){
        cout << "child process create successed : " << getpid() << endl;
    }else{
        cout << "parent process : " << getpid() << endl;
    }

    /* Timing Stop ... For created process successed */
    cout << endl;
    cout << "pid : " << getpid() << "  ->  ";
    timer.timing();
    cout << endl;

    if(0 != pid){ sleep(1); }

    return 0;
}

/* 单个管道的通信 */
int  Process::communicate_by_pipe(void)
{
    /* 
     * 管道不是进程资源，和套接字一样，属于操作系统
     * 进入管道的数据任何进程都可以读取，包括自身进程
     *
     *  #include <unistd.h>
     *  int pipe(int filedes[2]);
     *      -> 成功时返回0， 失败时返回-1
     *      -- filedes[0] : 通过管道接收数据时使用的文件描述符，即管道出口 out
     *      -- filedes[1] : 通过管道传输数据时使用的文件描述符，即管道入口 in
     *
     *  fds[0]-<----+  +-->-fds[0]
     *           +--+--+
     *  fds[1]->-+  +-----<-fds[1]
     *
     * */

    int ret = 0;

    int fds[2];

    if(0 == (ret = pipe(fds))){

        pid_t pid = 0;

        if(0 == (pid = fork())){
            cout << "child process pid : " << getpid() << endl;

            string s("child write data !");
            write(fds[1], s.c_str(), s.length());

            /* 
             * 此处的延时是保证了自己写入管道的数据不会被自己读取
             * 如果去掉，则写入的数据，会被自身读取
             * */
            sleep(2);

            char buf[128];
            read(fds[0], buf, 128);
            cout << "read from parent process buf : " << buf << endl;

        }else{
            cout << "parent process pid : " << getpid() << endl;

            char buf[128];
            read(fds[0], buf, 128);
            cout << "read from child process buf : " << buf << endl;

            sleep(3);
            string s("parent write data !");
            write(fds[1], s.c_str(), s.length());
        }

        if(0 == pid){
            cout << "end child " << endl;
        }else{
            cout << "end parent " << endl;
        }

    }else{
        cout << "[Error] create pipe failed !" << endl;
    }

    return ret;
}

/* 两个管道的通信 */
int  Process::communicate_by_pipe(int)
{
    /* 
     *  #include <unistd.h>
     *  int pipe(int filedes[2]);
     *      -> 成功时返回0， 失败时返回-1
     *      -- filedes[0] : 通过管道接收数据时使用的文件描述符，即管道出口 out
     *      -- filedes[1] : 通过管道传输数据时使用的文件描述符，即管道入口 in
     *
     *  fds1[0]-<----+  +-->-fds2[0]
     *           +--+--+
     *  fds2[1]->-+  +-----<-fds1[1]
     *
     * */

    int ret = 0;

    int p2c[2];
    int c2p[2];

    if((0 == (ret = pipe(p2c))) && (0 == (ret = pipe(c2p)))){

        pid_t pid = 0;

        if(0 == (pid = fork())){
            cout << "child process pid : " << getpid() << endl;

            string s("child write data !");
            write(c2p[1], s.c_str(), s.length());

            char buf[128];
            read(p2c[0], buf, 128);
            cout << "read from parent process buf : " << buf << endl;

        }else{
            cout << "parent process pid : " << getpid() << endl;

            char buf[128];
            read(c2p[0], buf, 128);
            cout << "read from child process buf : " << buf << endl;

            string s("parent write data !");
            write(p2c[1], s.c_str(), s.length());
            sleep(1);
        }

        if(0 == pid){
            cout << "end child " << endl;
        }else{
            cout << "end parent " << endl;
        }

    }else{
        cout << "[Error] create pipe failed !" << endl;
    }

    return ret;
}

/* 通过消息队列通信 */
int  Process::communicate_by_msg(void)
{
    int ret = 0;

    pid_t pid = 0;

    if(0 == (pid = fork())){
        cout << "child process pid : " << getpid() << endl;

        string s("data write from child");
        while(1){
            if(0 == ipc_msg_send((char *)s.c_str(), s.length())){
                cout << "ipc msg send successed" << endl;
                break;
            }else{
                cout << "[Error] ipc msg send error" << endl;
            }
            usleep(100 * 1000);
        }
        sleep(1);

    }else{
        cout << "parent process pid : " << getpid() << endl;

        int  rlen = 0;
        char buf[128] = "";
        while(1){
            if(0 == ipc_msg_recv(buf, &rlen)){
                cout << "read data : " << buf << endl;
                break;
            }else{
                cout << "[Error] ipc msg read error" << endl;
            }
            usleep(100 * 1000);
        }

        sleep(2);
    }

    if(0 == pid){
        cout << "end child process " << endl;
    }else{
        cout << "end parent process" << endl;
    }

    return ret;
}

