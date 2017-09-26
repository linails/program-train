/*
 * Progarm Name: ts-unit.cpp
 * Created Time: 2017-06-26 10:29:32
 * Last modified: 2017-06-30 11:25:25
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-unit.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "ts-parser.hpp"
#include "ts-pat.hpp"
#include "ts-pmt.hpp"
#include "ts-pes.hpp"

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


    if(0x1fff != this->m_PID){

        /*
         * PAT
         * */
        if(0x0000 == this->m_PID){

            this->info();
            printf("pid = 0x%.4x\n\n", (unsigned short)this->m_PID);

            int idx = this->m_payload_unit_start_indicator;
            if(1 == idx)        idx = 5;
            else if(0 == idx)   idx = 4;

            /* 
             * create TsPAT
             * */
            if(nullptr == TsParser::get_instance()->get_pat()){

                if(nullptr != TsParser::get_instance()->get_pat(new TsPAT())){

                    TsParser::get_instance()
                        ->get_pat()
                        ->load_data(&this->m_buf[idx], TS_UNIT_LENGTH - idx);
                }

            }else{
                TsParser::get_instance()
                    ->get_pat()
                    ->load_data(&this->m_buf[idx], TS_UNIT_LENGTH - idx);
            }


            /* 
             * create TsPMT
             * */
            vector<pair<int, int> > prgs;
            if(0 == TsParser::get_instance()
                        ->get_pat()
                        ->get_programs(prgs)){

                if(nullptr == TsParser::get_instance()->get_pmt()){
                    if(nullptr != TsParser::get_instance()->get_pmt(new TsPMT())){
                        TsParser::get_instance()
                            ->get_pmt()
                            ->add_programs(prgs);

                        cout << "create pmt and add programs successed !" << endl;
                    }
                }
            }





        /* 
         * CAT
         * */
        }else if(0x0001 == this->m_PID){
            cout << "cat ..." << endl;

            // Todo !
        





        /*
         * PMT
         * */
        }else if((nullptr != TsParser::get_instance()->get_pmt()) &&
                 (0 == TsParser::get_instance()->get_pmt()->is_pmt_stream(this->m_PID))){

            this->info();

            int idx = this->m_payload_unit_start_indicator;
            if(1 == idx)        idx = 5;
            else if(0 == idx)   idx = 4;

            printf("PMT parser ... pid = 0x%.4x\n", this->m_PID);
            TsParser::get_instance()
                ->get_pmt()
                ->load_data(this->m_PID, &this->m_buf[idx], TS_UNIT_LENGTH - idx);


            cout << "out PMT parser() ..." << endl;


        /*
         * PES
         * */
        }else if((nullptr != TsParser::get_instance()->get_pes()) &&
                 (0 == TsParser::get_instance()->get_pes()->is_pes_stream(this->m_PID))){
            #if 0
            if(0x0150 == this->m_PID){
                this->info();
                printf("pid = 0x%.4x\n\n", (unsigned short)this->m_PID);

                static int i = 1000;
                if(! i--) exit(0);
                else cout << "i = " << i << endl;
            }
            #endif
        }

    }else{
        //this->info();
        //printf("pid = 0x%.4x\n\n", (unsigned short)this->m_PID);
    }

    return 0;
}

