/*
 * Progarm Name: ts-pmt.hpp
 * Created Time: 2017-06-27 15:28:29
 * Last modified: 2017-06-29 15:41:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PMT_HPP_
#define _TS_PMT_HPP_

#include <unordered_map>
#include <vector>
#include "ts-pmt-section.hpp"

using std::unordered_map;
using std::pair;
using std::vector;

class TsPMT{
public:
    TsPMT();
    ~TsPMT();
    int  add_program(pair<int, int> &prg); // pair<program_number, program_map_number>
    int  add_programs(vector<pair<int, int> >&prgs); //
    int  is_pmt_stream(int pid);
    int  info(void);
    int  load_data(int pid, const char *buf, int cnt);
private:
    /*
     * unordered_map<program_number, TsPmtHeader_t>
     * */
    unordered_map<int, TsPMTSection *>  m_programs;

    /*
     * pair<program_map_number, program_number>
     * */
    unordered_map<int, int>             m_pid_prgs;
};

#endif //_TS_PMT_HPP_

