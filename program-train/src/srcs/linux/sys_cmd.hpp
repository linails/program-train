/*
 * Progarm Name: sys_cmd.hpp
 * Created Time: 2016-09-20 10:59:33
 * Last modified: 2017-10-08 09:00:15
 */

#ifndef _SYS_CMD_HPP_
#define _SYS_CMD_HPP_

extern void sys_cmd_called(void);

//--------------------------------------------------------------------------------------

/* 
 * Note! : redirect
 *
 * dup / dup2 函数常用于实现输入、输出的重定向
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * <unistd.h>
 * int dup(int oldfd);
 * int dup2(int oldfd, int newfd);
 *
 *  -> success return newfd, and fail return -1
 *
 * STDIN_FILENO  : 标准输入，其值为 0
 * STDOUT_FILENO : 标准输出，其值为 1
 * STDERR_FILENO : 标准错误输出，其值为 2
 *
 * 如果执行出错，返回错误值
 *  EBADF : oldfd 不是打开的文件描述符，或 newfd 超出了文件描述符允许的范围
 *  EBUSY : 在使用 open 函数和 dup 函数时发生了冲突，dup2 函数返回该错误
 *  EINTR : dup2 函数调用被信号中断
 *  EMFILE: 进程打开文件达到上限
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * dup 函数用于复制指定的文件描述符，函数返回的新描述符是当前进程最小的未使用的描述符
 * dup2 函数用于复制指定的文件描述符，只是参数与 dup 函数存在不同，当新的文件描述符已经打开，将会先关闭新的文件描述符
 *
 * */

class RedirecdShell{
public:
    RedirecdShell(const char *str);
    ~RedirecdShell();
private:
    int  redirect_stdout(int fd);
    int  redirect_stdin(int fd);
    int  reset_stdout(int fd);
    int  do_shell(const char *str);
};

#endif //_SYS_CMD_HPP_

