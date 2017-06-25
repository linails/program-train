/*
 * Progarm Name: ts-parser.cpp
 * Created Time: 2017-06-22 13:22:28
 * Last modified: 2017-06-25 22:24:01
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-parser.hpp"
#include "ts-parser.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

using std::cout;
using std::endl;

TsParser::TsParser(string file)
    :m_file(file)
{
    //if(-1 == (this->m_fd = open(this->m_file.c_str(), O_RDONLY, 0766))){
    if(-1 == (this->m_fd = open(this->m_file.c_str(), O_RDONLY))){
        printf("can't open file : %s\n", this->m_file.c_str());
        printf("errno : %d\n", errno);
        printf("ERR : %s\n", strerror(errno));
    }else{
        cout << "opened file : " << this->m_file << endl;

        this->get_file_info();

        /*
         * create thread of load_data_loop
         * */
        {
            this->m_ld_thread = new pthread_t;

            if(0 != pthread_create(this->m_ld_thread, NULL, TsParser::load_data_loop, NULL)){
                printf("errno : %d\n", errno);
                printf("ERR : %s\n", strerror(errno));

                delete this->m_ld_thread;
                this->m_ld_thread = nullptr;
            }
        }
    }
}

TsParser::~TsParser()
{
    if(-1 != this->m_fd){
        if(0 != close(this->m_fd)){
            printf("can't close file : %s\n", this->m_file.c_str());
            printf("errno : %d\n", errno);
            printf("ERR : %s\n", strerror(errno));
        }else{
            cout << "close file ok" << endl;
        }
    }

    if(nullptr != this->m_ld_thread){
        void *tr = nullptr;

        if(0 != pthread_join(*this->m_ld_thread, &tr)){
            printf("errno : %d\n", errno);
            printf("ERR : %s\n", strerror(errno));
        }
    }
}

int  TsParser::get_file_info(void)
{
    int ret = 0;

    off_t start = -1;
    off_t end   = -1;
    off_t fsize = -1;

    if(-1 != (start = lseek(this->m_fd, 0, SEEK_SET))){
        if(-1 != (end = lseek(this->m_fd, 0, SEEK_END))){
            fsize = end - start;
            cout << "file-size : " << fsize << endl;
        }
    }

    return ret;
}

void *TsParser::load_data_loop(void *args)
{
    while(1){
        sleep(1);
        cout << "load_data_loop ..." << endl;
    }

    pthread_exit((void *)"end TsParser::load_data_loop() ...");
}

