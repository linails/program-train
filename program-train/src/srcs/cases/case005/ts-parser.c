/*
 * Progarm Name: ts-parser.c
 * Created Time: 2017-06-22 13:23:06
 * Last modified: 2017-06-26 09:52:29
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-parser.h"
#include <stdio.h>


    this->m_ld_thread = new pthread_t;

    if(0 != pthread_create(this->m_ld_thread, NULL, TsParser::load_data_loop, NULL)){
        printf("errno : %d\n", errno);
        printf("ERR : %s\n", strerror(errno));

        delete this->m_ld_thread;
        this->m_ld_thread = nullptr;
    }

    if(nullptr != this->m_ld_thread){
        void *tr = nullptr;

        if(0 != pthread_join(*this->m_ld_thread, &tr)){
            printf("errno : %d\n", errno);
            printf("ERR : %s\n", strerror(errno));
        }else{
            delete this->m_ld_thread;
            this->m_ld_thread = nullptr;
        }
    }
