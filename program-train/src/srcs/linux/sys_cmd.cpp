/*
 * Progarm Name: sys_cmd.cpp
 * Created Time: 2016-09-20 10:59:19
 * Last modified: 2016-10-28 13:14:45
 */

#include "sys_cmd.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <cstring>

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
            while(fgets(line, sizeof(line) - 1, fp) != NULL)
                cout << "line : " << line ;
        }else{
            if(NULL != in){
                cout << "input ..." << endl;
                int ret = fputs(in, fp);
                cout << "ret = " << ret << endl;
            }
        }
    };

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
        do_shell("cd ~/share/temp/test; ./a.out", "minphone1 minphone2 minphone3");
    }
    cout << "---------------------------" << endl;
    {
        //do_shell("~/share/qt-at-tester/python/main.py");
    }

    pclose(fp);
}


