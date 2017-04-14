/*
 * Progarm Name: log.c
 * Created Time: 2017-02-10 16:22:39
 * Last modified: 2017-02-10 16:54:11
 * @author: minphone.linails linails@foxmail.com 
 */

#include "log.h"
#include <stdio.h>
#include <syslog.h>

/* 
 * Note : 
 *  应用程序使用 syslog 函数与 rsyslogd 守护进程通信
 *
 *  #include <syslog.h>
 *  void syslog(int priority, const char *message, ...);
 *
 *  priority 默认值是：LOG_USER
 *      #define LOG_EMERG   0   // 系统不可用
 *      #define LOG_ALERT   1   // 报警，需要立即采取动作
 *      #define LOG_CRIT    2   // 非常严重的情况
 *      #define LOG_ERR     3   // 错误
 *      #define LOG_WARNING 4   // 警告
 *      #define LOG_NOTICE  5   // 通知
 *      #define LOG_INFO    6   // 信息
 *      #define LOG_DEBUG   7   // 调试
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  #include <syslog.h>
 *  void openlog(const char *ident, int logopt, int facility);
 *      -> ident    : 此参数指定的字符串将被添加到日志消息的日期和时间之后，它通常设置为程序的名字
 *      -> logopt   : 此参数对后续的 syslog 调用的行为进行配置，可以取值如下
 *                    #define LOG_PID       0x01    // 在日志消息中包含程序 PID
 *                    #define LOG_CONS      0x02    // 如果消息不能记录到日志文件，则打印至终端
 *                    #define LOG_ODELAY    0x04    // 延迟打开日志功能直到第一次调用 syslog
 *                    #define LOG_NDELAY    0x08    // 不延迟打开日志功能
 *      -> facility : 此参数可用来修改 syslog 函数中的默认设施值
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  #include <syslog.h>
 *  int setlogmask(int maskpri);
 *
 *  #include <syslog.h>
 *  void closelog();
 * */


