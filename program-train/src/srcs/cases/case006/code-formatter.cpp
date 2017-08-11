/*
 * Progarm Name: code-formatter.cpp
 * Created Time: 2017-08-09 18:48:52
 * Last modified: 2017-08-09 23:08:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include "code-formatter.hpp"
#include <iostream>
#include "rfileoprt.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::endl;

CodeFormatter::CodeFormatter(string cfg, string dir)
    :m_cfg(cfg)
    ,m_dir(dir)
{
    /* 
     * update this->m_cfg 
     * eg. ~/cfg => /home/minphone/cfg
     * */
    {
        string home = getenv("HOME");

        int pos = -1;
        if((int)string::npos != (pos = this->m_cfg.find("~"))){
            string tail(this->m_cfg, pos + strlen("~"), string::npos);
            this->m_cfg = home + tail;
        }
        if((int)string::npos != (pos = this->m_dir.find("~"))){
            string tail(this->m_dir, pos + strlen("~"), string::npos);
            this->m_dir = home + tail;
        }
    }

//    if(true != dir.empty()){
//        this->m_rfo = new FileOperator(this->m_dir);
//        if(nullptr == this->m_fo){
//            cout << "[Error] new FileOperator() failed !" << endl;
//        }
//    }

    cout << "m_cfg : " << this->m_cfg << endl;
    cout << "m_dir : " << this->m_dir << endl;

}

CodeFormatter::~CodeFormatter()
{
}


