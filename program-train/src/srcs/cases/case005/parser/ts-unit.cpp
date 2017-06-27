/*
 * Progarm Name: ts-unit.cpp
 * Created Time: 2017-06-26 10:29:32
 * Last modified: 2017-06-27 18:17:14
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-unit.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "ts-parser.hpp"
#include "ts-pat.hpp"

using std::cout;
using std::endl;

TsUnit::TsUnit(const char *unit)
{
    if(nullptr != unit){
        memcpy(this->m_buf, unit, TS_UNIT_LENGTH);

        assert(0x47 == this->m_buf[0]);
        if(0x47 != this->m_buf[0]){
            cout << "[Error] TsUnit false!" << endl;
        }

        this->parser();


        this->info();
        printf("pid = 0x%.4x\n\n", (unsigned short)this->m_PID);

        /*
         * For Test only
         * */
        if(0 == this->m_PID){

            if(nullptr == TsParser::get_instance()->get_pat()){

                if(nullptr != TsParser::get_instance()->get_pat(new TsPAT())){
                    TsParser::get_instance()
                        ->get_pat()
                        ->load_data(&this->m_buf[5], TS_UNIT_LENGTH-5);
                }

            }else{
            }

            exit(0);
        }
    }
}

TsUnit::~TsUnit()
{
}

int  TsUnit::info(void)
{
    TsParser::get_instance()->hex_print("HexPrint", this->m_buf, TS_UNIT_LENGTH);

    /* 
     * */
    printf("%s: 0x%x\n", "sync_byte", ((TsPacket_t *)(this->m_buf))->header.sync_byte);
    printf("%s: 0x%x\n", "transport_error_indicator", this->m_transport_error_indicator);
    printf("%s: 0x%x\n", "payload_unit_start_indicator", this->m_payload_unit_start_indicator);
    printf("%s: 0x%x\n", "transport_priority", this->m_transport_priority);
    printf("%s: 0x%x\n", "transport_scrambling_control", this->m_transport_scrambling_control);
    printf("%s: 0x%x\n", "adaptation_field_control", this->m_adaptation_field_control);
    printf("%s: 0x%x\n", "continuity_counter", this->m_continuity_counter);

    return 0;
}

int  TsUnit::parser(void)
{
    /* 
     * Parser for TsHeader_t
     * */
    {
    this->m_transport_error_indicator =
        ((TsPacket_t *)(this->m_buf))->header.transport_error_indicator;
    this->m_payload_unit_start_indicator =
        ((TsPacket_t *)(this->m_buf))->header.payload_unit_start_indicator;
    this->m_transport_priority =
        ((TsPacket_t *)(this->m_buf))->header.transport_priority;


    this->m_PID  = ((TsPacket_t *)(this->m_buf))->header.PID_high5 << 8;
    this->m_PID |= ((TsPacket_t *)(this->m_buf))->header.PID_low8;

    this->m_transport_scrambling_control =
        ((TsPacket_t *)(this->m_buf))->header.transport_scrambling_control;

    this->m_adaptation_field_control =
        ((TsPacket_t *)(this->m_buf))->header.adaptation_field_control;

    this->m_continuity_counter =
        ((TsPacket_t *)(this->m_buf))->header.continuity_counter;
    }

    return 0;
}

