/*
 * Progarm Name: ts-pmt.cpp
 * Created Time: 2017-06-27 15:28:34
 * Last modified: 2017-06-29 16:53:48
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-pmt.hpp"
#include <iostream>
#include "ts-parser.hpp"
#include <cstdio>

#include "ts-descriptor.hpp"
#include "CA_descriptor.hpp"
#include "ISO_639_language_descriptor.hpp"

using std::cout;
using std::endl;
using std::make_pair;

TsPMT::TsPMT()
{
}

TsPMT::~TsPMT()
{
    for(auto &u : this->m_programs) delete u.second;
}

int  TsPMT::info(void)
{
    return 0;
}

int  TsPMT::is_pmt_stream(int pid)
{
    auto iter = this->m_pid_prgs.find(pid);
    if(iter != this->m_pid_prgs.end()){
        return 0;
    }else{
        return -1;
    }
}

/*  
 * prg : pair<program_number, program_map_number>
 *  */
int  TsPMT::add_program(pair<int, int> &prg)
{
    auto iter = this->m_pid_prgs.find(prg.second);
    if(iter == this->m_pid_prgs.end()){
        this->m_pid_prgs.insert(make_pair(prg.second, prg.first));

        this->m_programs.insert(make_pair(prg.first, new TsPMTSection()));
    }

    return 0;
}

int  TsPMT::add_programs(vector<pair<int, int> >&prgs)
{
    for(auto &u : prgs) this->add_program(u); return 0;
}

int  TsPMT::load_data(int pid, const char *buf, int cnt)
{
    int program_number = this->m_pid_prgs[pid];

    TsPMTSection *ptr = this->m_programs[program_number];

    TsParser::get_instance()->hex_print("load_data - TsPMT", buf, cnt);

    return ptr->parser(program_number, buf, cnt);
}

