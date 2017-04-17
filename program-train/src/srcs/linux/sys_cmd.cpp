/*
 * Progarm Name: sys_cmd.cpp
 * Created Time: 2016-09-20 10:59:19
 * Last modified: 2016-11-04 10:32:29
 */

#include "sys_cmd.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>

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

    pclose(fp);
}


