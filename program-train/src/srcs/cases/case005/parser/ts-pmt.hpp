/*
 * Progarm Name: ts-pmt.hpp
 * Created Time: 2017-06-27 15:28:29
 * Last modified: 2017-06-28 16:57:30
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PMT_HPP_
#define _TS_PMT_HPP_

#include <map>
#include <vector>
#include "ts-pmt-section.hpp"

using std::map;

class TsPMT{
public:
    TsPMT();
    ~TsPMT();
    int  info(void);
private:
private:
    /*
     * map<program_number, TsPmtHeader_t>
     * */
    map<int, TsPMTSection>    m_programs;
};

#endif //_TS_PMT_HPP_

