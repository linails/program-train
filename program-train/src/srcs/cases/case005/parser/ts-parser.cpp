/*
 * Progarm Name: ts-parser.cpp
 * Created Time: 2017-06-22 13:22:28
 * Last modified: 2017-06-29 18:59:57
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
#include "ts-pat.hpp"
#include "ts-pmt.hpp"
#include "ts-pes.hpp"

using std::cout;
using std::endl;

TsParser *TsParser::instance = nullptr;

TsParser *TsParser::get_instance(TsParser *ptr)
{
    if(nullptr != ptr) instance = ptr; return instance;
}

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

    if(nullptr != this->m_tsbuf){ delete this->m_tsbuf; this->m_tsbuf = nullptr; }

    if(nullptr != this->m_pat){ delete this->m_pat; this->m_pat = nullptr; }
    if(nullptr != this->m_pmt){ delete this->m_pmt; this->m_pmt = nullptr; }
    if(nullptr != this->m_pes){ delete this->m_pes; this->m_pes = nullptr; }
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

    while(i--){
        usleep(100);

        ssize_t num = read(this->m_fd, (void *)(this->m_tsbuf->buf), BUF_MAX_SIZE);
        this->m_tsbuf->set_length(num);

        printf("i = %d | read num = %d - this->m_tsbuf.size() : %d\n",
                i, (int)num, (int)(this->m_tsbuf->size()));
        cout << "cur offset : " << lseek(this->m_fd, 0, SEEK_CUR) << endl;


        /* 
         * seperate data -> 188bytes
         * */
        {
            if(true != buf.empty()){
                this->m_tsbuf->top_remain(buf, buf.size());

                cout << "buf.size() = " << buf.size() << endl;
                assert(188 == buf.size());
                if(188 == buf.size()){
                    TsUnit unit(buf.buf);

                    {
                    std::unique_lock<std::mutex> lock(this->m_lock);
                    this->m_ts_units.push(unit);
                    }

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
            {
            std::unique_lock<std::mutex> lock(this->m_lock);
            this->m_tsbuf->cut_tsunit(this->m_ts_units);
            }


            assert(true == buf.empty());
            if(true == buf.empty()){
                if(-1 != this->m_tsbuf->tail_remain(buf, 0)){
                }else{
                    cout << "have no tail remain data ..." << endl;
                }
            }

            cout << "this->m_ts_units.size() : " << this->m_ts_units.size() << endl;
        }
    }


    /*
     * set flag For read all data done!
     * */
    this->m_done_flag  = 0;
    cout << "this->m_done_flag = 0" << endl;
}

void TsParser::parser(void)
{
    #if 1
    int i = 1000;
    while(i-- > 0){
    #else
    while(1){
    #endif

        usleep(5);

        if(true != this->m_ts_units.empty()){
            if(0 == this->m_done_flag){
                TsUnit &unit = this->m_ts_units.front();

                unit.parser();

                this->m_ts_units.pop();
            }else{
                std::unique_lock<std::mutex> lock(this->m_lock);
                TsUnit &unit = this->m_ts_units.front();

                unit.parser();

                this->m_ts_units.pop();
            }
        }else{
            if(0 == this->m_done_flag){
                break;
            }else{
                continue;
            }
        }

        //cout << " - this->m_ts_units.size() : " << this->m_ts_units.size() << endl;
        //unit.hex_print();
    }
}

TsPAT   *TsParser::get_pat(TsPAT *ptr)
{
    if(nullptr != ptr){
        if(nullptr != this->m_pat){
            cout << "[Error] new TsPAT() again ..." << endl;
            exit(1);
        }else{
            this->m_pat = ptr;
        }
    }

    return this->m_pat;
}

TsPMT   *TsParser::get_pmt(TsPMT *ptr)
{
    if(nullptr != ptr){
        if(nullptr != this->m_pmt){
            cout << "[Error] new TsPMT() again ..." << endl;
            exit(1);
        }else{
            this->m_pmt = ptr;
        }
    }

    return this->m_pmt;
}

TsPES   *TsParser::get_pes(TsPES *ptr)
{
    if(nullptr != ptr){
        if(nullptr != this->m_pes){
            cout << "[Error] new TsPES() again ..." << endl;
            exit(1);
        }else{
            this->m_pes = ptr;
        }
    }

    return this->m_pes;
}

int  TsParser::hex_print(const char *tag, const char *buf, size_t cnt)
{
    printf("%s : - cnt : %d\n", tag, (int)cnt);
    for(size_t i=0; i<cnt; i++){
        printf("%.2X ", (unsigned char)buf[i]);

        if(!((i + 1) % 20)) cout << endl;
        else if(!((i + 1) % 10)) cout << "- ";
    }
    printf("\n");

    return 0;
}

