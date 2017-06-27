/*
 * Progarm Name: ts-pat.cpp
 * Created Time: 2017-06-27 15:20:07
 * Last modified: 2017-06-27 18:19:40
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-pat.hpp"
#include <iostream>
#include "ts-parser.hpp"

using std::cout;
using std::endl;

TsPAT::TsPAT()
{
}

TsPAT::~TsPAT()
{
}

int  TsPAT::load_data(const char *buf, int cnt)
{
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

    return 0;
}


