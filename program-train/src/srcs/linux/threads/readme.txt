# readme.txt
# Created Time: 2016-05-30 23:01:30
# Last modified: 2016-05-31 21:22:46
#

* pthread_xxx 系列函数在失败时，返回错误代码，成功返回0

#--------------------------------------------------------------------

#include <pthread.h>

/*线程创建*/
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(start_routine)(void *), void *arg);
    thread  : 指向pthread_create类型的指针，用于引用新创建的线程
    attr    : 用于设置线程的属性，一般不需要特殊的属性，可以简单的设置为NULL
    void*(start_routine)(void *) : 传递新线程所要执行的函数地址
    arg     : 新线程所要执行的函数的参数

/*线程终止*/
int pthread_exit(void *retval);
    retval  : 返回指针，指向线程要返回的某个对象
    线程通过调用此函数终止执行，并返回一个指向某对象的指针

/*线程同步*/
int pthread_join(pthread_t th, void **thread_return);
    th      : 将要等待的线程，值为通过pthread_create返回的标识符来指定
    thread_return : 指向线程的返回值

#--------------------------------------------------------------------

* 用信号量进行同步
#include <semaphore.h>

/*信号创建*/
int sem_init(sem_t *sem, int pshared, unsigned int value);
    sem     : 信号量对象
    pshared : 控制信号量的类型，0表示这个信号量是当前进程的局部变量，否则，此信号量就可以在多个进程之间共享
    value   : 信号量的初始值

/*信号量控制*/
int sem_post(sem_t *sem);   //以原子操作的方式给信号量的值加1
int sem_wait(sem_t *sem);   //以原子操作的方式给信号量的值减1，但它会等到信号量非0时才会开始减法操作
                            //如果对值为0的信号量调用sem_wait，这个函数就会等待，直到有线程增加了该信号量的值使其
                            //不在为0 [即：一直阻塞等待，直到信号量>0]
int sem_trywait(sem_t *sem);
    errno : EAGAIN    操作不能执行而不阻塞(即当前信号量为0)
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
    errno : EINVAL    abs_timeout.tv_nsecs的值小于0,或者大于等于100million
            ETIMEDOUT 调用在信号量锁定之前超时

/*信号量销毁*/
int sem_destroy(sem_t *sem);//清理该信号量所拥有的资源，如果试图清理信号量正被一些线程等待，就会收到一个错误

#--------------------------------------------------------------------

* 用互斥量进行线程同步
#inlcude <pthread.h>

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#--------------------------------------------------------------------


