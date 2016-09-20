/*
 * Progarm Name: sys_cmd.cpp
 * Created Time: 2016-09-20 10:59:19
 * Last modified: 2016-09-20 11:08:23
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
    char line[1024];
    FILE *fp = NULL;

    string cmd = "ls -l ~/share/temp";

    if(NULL == (fp = popen(cmd.c_str(), "r"))){
        cout << "error" << endl;
        return;
    }

    while(fgets(line, sizeof(line) - 1, fp) != NULL){
        cout << "line : " << line ;
    }

    pclose(fp);
}


