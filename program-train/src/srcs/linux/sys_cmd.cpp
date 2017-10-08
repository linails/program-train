/*
 * Progarm Name: sys_cmd.cpp
 * Created Time: 2016-09-20 10:59:19
 * Last modified: 2017-10-08 10:29:01
 */

#include "sys_cmd.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>

using namespace std;

void sys_cmd_called(void)
{
    FILE *fp = NULL;

    auto do_shell = [&](const char *str,
                 const char *in = NULL,
                 const char *judge = NULL){
        char line[1024];
        char wr[2] = "r";
        if(NULL != in) wr[0] = 'w';
        if(NULL == (fp = popen(str, wr))){
            cout << "error" << endl;
            return;
        }

        if(NULL == in){
            int lines = 0;
            cout << endl;
            while(fgets(line, sizeof(line) - 1, fp) != NULL){
                printf("line %.4d : %s", lines++, line);
            }
            cout << endl;
        }else{
            if(NULL != in){
                cout << "input ..." << endl;
                int ret = fputs(in, fp);
                cout << "ret = " << ret << endl;
            }
        }
    };

    #if 0
    {
        do_shell("ls -l ~/share/temp");
    }
    cout << "---------------------------" << endl;
    {
        do_shell("ls ~/share/temp");
    }
    cout << "---------------------------" << endl;
    {
        do_shell("ls ~/share/temp; ls -l ~/share/temp");
    }
    #endif
    #if 0
    cout << "---------------------------" << endl;
    {
        //do_shell("cd ~/share/workspace/wt-space/wt-server/build/LINUX; ./build-wt-server.sh");
        do_shell("cd ~/share/workspace/wt-space/wt-server/build/LINUX; ./exe.sh");
        //do_shell("cd ~/share/workspace/wt-space/wt-gateway/build/LINUX; ./exe.sh");
    }
    #endif
    cout << "---------------------------" << endl;
    {
        //do_shell("cd ~/share/temp/test; ./a.out", "minphone1 minphone2 minphone3");
    }
    cout << "---------------------------" << endl;
    #if 0
    {
        cout << " ** python script **" << endl;
        char buf[128];
        getcwd(buf, sizeof(buf));
        cout << "pwd : " << buf << endl;

        string pwd(buf);
        string script = "numpy-exercise.py";
        //string script = "traitsui-default-view.py";

        /* python script path */
        pwd += "/../src/srcs/linux/python/";

        pwd += script;

        do_shell(pwd.c_str());
    }
    cout << "---------------------------" << endl;
    {
        cout << " ** shell script **" << endl;
        char buf[128];
        getcwd(buf, sizeof(buf));
        cout << "pwd : " << buf << endl;

        string pwd(buf);
        string script = "base-bash.sh";

        /* python script path */
        pwd += "/../src/srcs/linux/shell/";

        pwd += script;

        do_shell(pwd.c_str());
    }
    #endif
    cout << "---------------------------" << endl;
    {
        /* 
         * 运行的结果是，每次都当前路径并没有改变，等于是每一次都是新的 shell 环境
         * */
        do_shell("pwd");
        do_shell("cd ..");
        do_shell("pwd");
    }
    cout << "---------------------------" << endl;
    {
        RedirecdShell("ls -l");
        RedirecdShell("pwd");
        RedirecdShell("find . -type f -name \"*.*\"");
    }

    pclose(fp);
}

RedirecdShell::RedirecdShell(const char *str)
{
    int ret = 0;

    int p2c[2] = {-1, -1};
    int c2p[2] = {-1, -1};

    if((0 == (ret = pipe(p2c))) && (0 == (ret = pipe(c2p)))){

        pid_t pid = 0;

        if(0 == (pid = fork())){
            cout << "child process pid : " << getpid() << endl;

            cout << "this->redirect_stdout() ..." << endl;

            ret = this->redirect_stdout(c2p[1]); assert(-1 != ret);
            ret = this->redirect_stdin(p2c[0]); assert(-1 != ret);

            cout << "hello world!" << endl;
            cout << "nice to meet you , stdout !" << endl;

            this->do_shell(str);

            string in ; cin >> in;

            cout << "in = " << in << endl;

        }else{
            cout << "parent process pid : " << getpid() << endl;

            string s("hello-client! ");
            write(p2c[1], s.c_str(), s.length());
            usleep(100 * 1000);

            char buf[1024] = {0, }; // 这里只是实验，只读一次
            read(c2p[0], buf, 1024);

            cout << "buf = " << buf << endl;
            cout << "end buf read !" << endl;
        }

        if(0 == pid){
            cout << "end child " << endl;
        }else{
            cout << "end parent " << endl;
        }

    }else{
        cout << "[Error] failed open pipe(fds) !" << endl;
        exit(-1);
    }
}

RedirecdShell::~RedirecdShell()
{
    cout << "~RedirecdShell() | pid = " << getpid() << endl;
}

int  RedirecdShell::redirect_stdout(int fd)
{
    int ret = 0;

    close(STDOUT_FILENO);
    if(-1 == (ret = dup2(fd, STDOUT_FILENO))){
        ret = -1;
    }

    return ret;
}

int  RedirecdShell::redirect_stdin(int fd)
{
    int ret = 0;

    close(STDIN_FILENO);
    if(-1 == (ret = dup2(fd, STDIN_FILENO))){
        ret = -1;
    }

    return ret;
}

int  RedirecdShell::reset_stdout(int fd)
{
    return 0;
}

int  RedirecdShell::do_shell(const char *str)
{
    FILE *fp = NULL;
    char wr[2] = "w";

    if(NULL == (fp = popen(str, wr))){
        cout << "error" << endl;
        exit(-1);
    }

    return pclose(fp);
}

