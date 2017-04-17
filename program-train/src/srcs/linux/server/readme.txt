# readme.txt
# Created Time: 2017-02-10 16:06:21
# Last modified: 2017-02-10 16:10:58
#

[服务器的一些开发规范]

01. Linux服务器程序一般以后台进程形式运行

02. Linux服务器程序通常有一套日志系统，或至少能够输出日志到文件，且大部分后台进程都在/var/log目录下拥有自己的日志目录文件

03. Linux服务器程序一般以某个专门的非root身份运行

04. 一般可配置 eg. /etc/squid3/squid.conf   |   /etc/postgresql.conf

05. Linux服务器进程通常会在启动的时候生成一个PID文件并存入/var/run目录中，以记录该后台进程的PID
    et. /var/run/syslogd.pid

