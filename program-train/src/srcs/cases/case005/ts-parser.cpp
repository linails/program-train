/*
 * Progarm Name: ts-parser.cpp
 * Created Time: 2017-06-22 13:22:28
 * Last modified: 2017-06-26 17:13:49
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
#include <cassert>

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

        this->m_tsbuf = new TsBuffer(BUF_MAX_SIZE);
        if(nullptr == this->m_tsbuf){
            cout << "[Error] new failed TsBuffer()" << endl;
        }

        /*
         * create thread of load_data_loop
         * */
        {
            this->m_ld_thread = new thread(&TsParser::load_data_loop, this);
            if(nullptr == this->m_ld_thread){
                cout << "[Error] new failed in TsParser!" << endl;
            }

            this->m_parser_thread = new thread(&TsParser::parser, this);
            if(nullptr == this->m_parser_thread){
                cout << "[Error] new failed in TsParser!" << endl;
            }
        }
    }
}

TsParser::~TsParser()
{
    if(nullptr != this->m_ld_thread){
        this->m_ld_thread->join();
        delete this->m_ld_thread;
        this->m_ld_thread = nullptr;
    }

    if(nullptr != this->m_parser_thread){
        this->m_parser_thread->join();
        delete this->m_parser_thread;
        this->m_parser_thread = nullptr;
    }

    if(-1 != this->m_fd){
        if(0 != close(this->m_fd)){
            printf("can't close file : %s\n", this->m_file.c_str());
            printf("errno : %d\n", errno);
            printf("ERR : %s\n", strerror(errno));
        }else{
            cout << "close file ok" << endl;
        }
    }

    if(nullptr != this->m_tsbuf){
        delete this->m_tsbuf;
        this->m_tsbuf = nullptr;
    }
}

int  TsParser::get_file_info(void)
{
    int ret = 0;

    off_t start = -1;
    off_t end   = -1;

    if(-1 != (start = lseek(this->m_fd, 0, SEEK_SET))){
        if(-1 != (end = lseek(this->m_fd, 0, SEEK_END))){
            this->m_filesize = end - start;
            cout << "file-size : " << this->m_filesize << endl;
        }
    }

    /* 
     * reset read point
     * */
    if(0 == lseek(this->m_fd, 0, SEEK_SET)){
        cout << "reset point successed !" << endl;
    }

    return ret;
}

void TsParser::load_data_loop(void)
{
    int  i = this->m_filesize/BUF_MAX_SIZE;

    TsBuffer buf;

    if(this->m_filesize % BUF_MAX_SIZE) i++;

    auto pre_num_bytes = [](const char *tag, char *buf, size_t cnt){
        printf("%s : \n", tag);
        for(size_t i=0; i<cnt; i++){
            printf("%.2X ", (unsigned char)buf[i]);
            if(!((i + 1) % 20)){
                cout << endl;
            }
        }
        printf("\n");
    };

    while(i--){
        usleep(100);

        ssize_t num = read(this->m_fd, (void *)(this->m_tsbuf->buf), BUF_MAX_SIZE);
        this->m_tsbuf->set_length(num);

        printf("i = %d | read num = %d - this->m_tsbuf.size() : %d\n",
                i, (int)num, (int)(this->m_tsbuf->size()));
        cout << "cur offset : " << lseek(this->m_fd, 0, SEEK_CUR) << endl;
        pre_num_bytes("BUF", this->m_tsbuf->buf, 100);
        //pre_num_bytes("BUF", this->m_tsbuf->buf, BUF_MAX_SIZE);


        /* 
         * seperate data -> 188bytes
         * */
        {
            if(true != buf.empty()){
                this->m_tsbuf->top_remain(buf, buf.size());
                //pre_num_bytes("top_remain", buf.buf, buf.size());

                cout << "buf.size() = " << buf.size() << endl;
                assert(188 == buf.size());
                if(188 == buf.size()){
                    TsUnit unit(buf.buf);
                    this->m_ts_units.push_back(unit);

                    buf.clear();
                }else{
                    cout << "[Error] Line : " << __LINE__ << endl;
                }

            }else{
                this->m_tsbuf->top_remain(buf, 0);
                buf.clear();
            }


            /* 
             * get all ts-units
             * */
            this->m_tsbuf->cut_tsunit(this->m_ts_units);


            assert(true == buf.empty());
            if(true == buf.empty()){
                if(-1 != this->m_tsbuf->tail_remain(buf, 0)){
                }else{
                    cout << "have no tail remain data ..." << endl;
                }

                //pre_num_bytes("tail_remain", buf.buf, buf.size());
            }

            cout << "this->m_ts_units.size() : " << this->m_ts_units.size() << endl;
        }
    }
}

void TsParser::parser(void)
{
    while(true != this->m_ts_units.empty()){
        sleep(1);


        cout << "TsParser::parser() ..." << endl;
    }
}

