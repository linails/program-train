/*
 * Progarm Name: ts-pat.cpp
 * Created Time: 2017-06-27 15:20:07
 * Last modified: 2017-06-29 15:07:31
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-pat.hpp"
#include <iostream>
#include "ts-parser.hpp"
#include <cstring>

using std::cout;
using std::endl;
using std::make_pair;

TsPAT::TsPAT()
{
}

TsPAT::~TsPAT()
{
}

int  TsPAT::load_data(const char *buf, int cnt)
{
    memcpy(this->m_buf, buf, cnt);

    TsParser::get_instance()->hex_print("load_data", buf, cnt);

    this->parser(buf);

    this->info();

    return 0;
}

int  TsPAT::info(void)
{
    printf("%s: 0x%x\n", "table_id", this->m_table_id);
    printf("%s: 0x%x\n", "section_syntax_indicator", this->m_section_syntax_indicator);
    printf("%s: 0x%x\n", "section_length", this->m_section_length);
    printf("%s: 0x%x\n", "transport_stream_id", this->m_transport_stream_id);
    printf("%s: 0x%x\n", "version_number", this->m_version_number);
    printf("%s: 0x%x\n", "current_next_indicator", this->m_current_next_indicator);
    printf("%s: 0x%x\n", "section_number", this->m_section_number);
    printf("%s: 0x%x\n", "last_section_number", this->m_last_section_number);

    for(auto &u : this->m_prg_num_pids){
        printf("program_number = 0x%.4x - ", (unsigned short)u.first);
        if(0x0000 == (unsigned short)u.first){
            printf("network_PID     = 0x%.4x\n", (unsigned short)u.second);
        }else{
            printf("program_map_PID = 0x%.4x\n", (unsigned short)u.second);
        }
    }

    return 0;
}

int  TsPAT::parser(const char *buf)
{
    /* 
     * For TsPatHeader_t
     * */

    this->m_table_id = ((TsPatHeader_t *)buf)->table_id;
    this->m_section_syntax_indicator = ((TsPatHeader_t *)buf)->section_syntax_indicator;

    this->m_section_length = ((TsPatHeader_t *)buf)->section_length_high4 << 8;
    this->m_section_length|= ((TsPatHeader_t *)buf)->section_length_low8;

    this->m_transport_stream_id = ((TsPatHeader_t *)buf)->transport_stream_id_high8 << 8;
    this->m_transport_stream_id|= ((TsPatHeader_t *)buf)->transport_stream_id_low8;

    this->m_version_number = ((TsPatHeader_t *)buf)->version_number;
    this->m_current_next_indicator = ((TsPatHeader_t *)buf)->current_next_indicator;
    this->m_section_number = ((TsPatHeader_t *)buf)->section_number;
    this->m_last_section_number = ((TsPatHeader_t *)buf)->last_section_number;


    typedef struct{
        unsigned char program_number_high8;
        unsigned char program_number_low8;

        /* byte[2] */
        unsigned char pid_high5 : 5;
        unsigned char reserved : 3;

        unsigned char pid_low8;
    }Programs_t;

    cout << "sizeof(Programs_t) : " << sizeof(Programs_t) << endl;

    /* 
     * For progarms
     * */
    int program_N = (this->m_section_length - 5 - 4)/4;
    char *ptr = &this->m_buf[sizeof(TsPatHeader_t)];
    for(int i=0; i<program_N; i++){
        unsigned short
        program_number = ((Programs_t *)ptr)->program_number_high8 << 8;
        program_number |= ((Programs_t *)ptr)->program_number_low8;

        unsigned short
        pid = ((Programs_t *)ptr)->pid_high5 << 8;
        pid|= ((Programs_t *)ptr)->pid_low8;

        /* 
         * bug in map<int, int> !
         * */
        this->m_prg_num_pids.insert(make_pair((int)program_number, (int)pid));

        ptr += sizeof(Programs_t);
    }

    return 0;
}

int  TsPAT::get_programs(vector<pair<int, int> > &prgs)
{
    int ret = -1;

    for(auto &u : this->m_prg_num_pids){
        if(0x0000 != u.first){
            prgs.push_back(u);
            ret = 0;
        }
    }

    return ret;
}

int  TsPAT::get_nit(pair<int, int> &nit)
{
    int ret = -1;

    for(auto &u : this->m_prg_num_pids){
        if(0x0000 == u.first){
            nit = u;
            ret = 0;
            break;
        }
    }

    return ret;
}



