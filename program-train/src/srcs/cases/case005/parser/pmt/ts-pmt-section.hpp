/*
 * Progarm Name: ts-pmt-section.hpp
 * Created Time: 2017-06-28 16:56:38
 * Last modified: 2017-06-29 19:34:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PMT_SECTION_HPP_
#define _TS_PMT_SECTION_HPP_

#include <vector>
#include "ts-descriptor.hpp"
#include "ts-pmt-header.h"
#include <cstdio>
#include "CA_descriptor.hpp"
#include "ISO_639_language_descriptor.hpp"
#include "User_Private.hpp"

using std::vector;

struct TsPMTSection{
public:
    TsPMTSection(){}

    ~TsPMTSection(){
        for(auto &u : this->m_descriptors)     delete u;
        for(auto &compent : this->m_compents){
            for(auto &u : compent.descriptors) delete u;
        }
    }

    int parser(int prg_num, const char *buf, int cnt){
        
        this->m_table_id = ((TsPmtHeader_t *)buf)->table_id;
        this->m_section_syntax_indicator = ((TsPmtHeader_t *)buf)->section_syntax_indicator;

        this->m_section_length  = ((TsPmtHeader_t *)buf)->section_length_high4 << 8;
        this->m_section_length |= ((TsPmtHeader_t *)buf)->section_length_low8;

        this->m_program_number  = ((TsPmtHeader_t *)buf)->program_number_high8 << 8;
        this->m_program_number |= ((TsPmtHeader_t *)buf)->program_number_low8;

        this->m_version_number  = ((TsPmtHeader_t *)buf)->version_number;

        this->m_current_next_indicator = ((TsPmtHeader_t *)buf)->current_next_indicator;
        if(1 == this->m_current_next_indicator){

            this->m_section_number      = ((TsPmtHeader_t *)buf)->section_number;
            this->m_last_section_number = ((TsPmtHeader_t *)buf)->last_section_number;

            this->m_PCR_PID  = ((TsPmtHeader_t *)buf)->PCR_PID_high5 << 8;
            this->m_PCR_PID |= ((TsPmtHeader_t *)buf)->PCR_PID_low8;

            this->m_program_info_length =((TsPmtHeader_t *)buf)->program_info_length_high4 << 8;
            this->m_program_info_length|= ((TsPmtHeader_t *)buf)->program_info_length_low8;


            printf("ts-pmt-section parser() ...- info_length = %d\n",
                    this->m_program_info_length);

            /* 
             * parser descriptors
             * */
            const char *ptr = &buf[sizeof(TsPmtHeader_t)];
            for(int i=0; i<this->m_program_info_length; ){

                unsigned char tag = ((DescripHeader_t *)ptr)->descriptor_tag;
                printf("tag = 0x%.2x length = 0x%.2x\n", tag,
                        ((DescripHeader_t *)ptr)->descriptor_length);

                switch(tag){
                    case 9: // CA_descriptor
                        this->m_descriptors.push_back(
                                new CA_descriptor((CA_descriptorHeader_t *)ptr));
                        break;
                    case 10:// ISO_639_language_descriptor
                        this->m_descriptors.push_back(
                                new ISO_639_language_descriptor(
                                    (ISO_639_language_descriptorHeader_t *)ptr
                                    ));
                        break;
                    case 64 ... 255: // User Private
                        this->m_descriptors.push_back(
                                new UserPrivate((User_PrivateHeader_t *)ptr));
                        break;
                    default:
                        break;
                }

                i += ((DescripHeader_t *)ptr)->descriptor_length + 2;
                ptr += ((DescripHeader_t *)ptr)->descriptor_length + 2;
            }

            this->info();
        }

        return 0;
    }

    int  info(void){
        printf("%s: 0x%x\n", "table_id", this->m_table_id);
        printf("%s: 0x%x\n", "section_syntax_indicator", this->m_section_syntax_indicator);
        printf("%s: 0x%x\n", "section_length", this->m_section_length);
        printf("%s: 0x%x\n", "program_number", this->m_program_number);
        printf("%s: 0x%x\n", "version_number", this->m_version_number);
        printf("%s: 0x%x\n", "current_next_indicator", this->m_current_next_indicator);
        printf("%s: 0x%x\n", "section_number", this->m_section_number);
        printf("%s: 0x%x\n", "last_section_number", this->m_last_section_number);
        printf("%s: 0x%x\n", "PCR_PID", this->m_PCR_PID);
        printf("%s: 0x%x\n", "program_info_length", this->m_program_info_length);

        for(auto &u : this->m_descriptors){
            switch(u->m_descriptor_tag){
                case 9: // CA_descriptor
                    printf("%s: 0x%x\n", " CA-descriptor_tag", u->m_descriptor_tag);
                    printf("%s: 0x%x\n", " CA-descriptor_length", u->m_descriptor_length);

                    printf("%s: 0x%x\n", " CA-ca_system_id",
                            ((CA_descriptor *)u)->m_CA_system_ID);
                    printf("%s: 0x%x\n", " CA-CA_PID", ((CA_descriptor *)u)->m_CA_PID);
                    printf("%s: 0x%x\n", " CA-private_length",(unsigned)((CA_descriptor *)u)
                            ->m_private_data_bytes.size());
                    printf("%s: ", " CA-private_data");
                    for(unsigned char du :
                        ((CA_descriptor  *)u)->m_private_data_bytes) printf("0x%X ", du);
                    printf("\n");
                    printf("---------------------------------------------\n");
                    break;
                case 10:// ISO_639_language_descriptor
                    printf("%s: 0x%x\n", " ISO-descriptor_tag", u->m_descriptor_tag);
                    printf("%s: 0x%x\n", " ISO-descirptor_length", u->m_descriptor_length);

                    printf("%s: ", " ISO-639_language_code");
                    for(int code :((ISO_639_language_descriptor *)u)->m_ISO_639_language_codes){
                        unsigned char low8  = code & 0x000000ff;
                        unsigned char mid8  = (code >> 8) & 0x000000ff;
                        unsigned char high8 = (code >> 8) & 0x000000ff;
                        printf("0x%.2X 0x%.2X 0x%.2X ", high8, mid8, low8);
                    }
                    printf("%s: 0x%x\n", " ISO-audio_type",
                            ((ISO_639_language_descriptor *)u)->m_audio_type);
                    printf("---------------------------------------------\n");
                    break;
                case 64 ... 255: // User Private
                    printf("%s: 0x%x\n", " User-descriptor_tag", u->m_descriptor_tag);
                    printf("%s: 0x%x\n", " User-descriptor_length", u->m_descriptor_length);
                    printf("%s: ", " User-descriptor-data");
                    for(unsigned char du : ((UserPrivate *)u)->m_private_data_bytes){
                        printf("0x%.2X ", du);
                    }
                    printf("\n");
                    printf("---------------------------------------------\n");
                    break;
                default:
                    break;
            }
        }

        return 0;
    }
public:
    /* 
     * 表示 PSI 分段的内容
     *  1> 0x00 : PAT
     *  2> 0x01 : CAT
     *  3> 0x02 : PMT
     *  4> 0x03 ~ 0x3F : reserved
     *  5> 0x40 ~ 0xFE : used for user private
     *  6> 0xFF : forbidden
     * */
    unsigned char   m_table_id;

    /* 
     * fixed val = 1
     * */
    unsigned char   m_section_syntax_indicator;

    /* 
     * 此字段之后的字节数，包括 CRC
     * */
    unsigned short  m_section_length;

    /*
     * 规定 program_map_PID 所对应的 program
     * */
    unsigned char   m_program_number;

    /* 
     * 表示 PMT 的版本号
     * 版本号随着此分段中信息的每一次改变而 +1
     * */
    unsigned char   m_version_number;

    /* 
     * 1> val = 1 : 表示所发送的 PMT 是当前可用的
     * 2> val = 0 : 表示所发送的 PMT 当前不可用，下一个 PMT 为有效
     * */
    unsigned char   m_current_next_indicator;

    unsigned char   m_section_number;
    unsigned char   m_last_section_number;

    /* 
     * 表示包括由 program_number 指定的 program 中包含有效 PCR 字段的
     * 传送流分组的 PID
     *
     * 如果一个 private stream 中的 PMT 定义无 PCR 与之相连，则此字段
     * 应为 0x1fff
     * */
    unsigned short  m_PCR_PID;

    /* 
     * 此字段之后的 descriptor 的字节数
     * */
    unsigned short  m_program_info_length;

    vector<DescriptorBase *> m_descriptors;

    typedef struct{
        /*
         * 规定由 elementary_PID 制定的 PID 值的分组中原始流或有效负载的类型
         * ---------------------------------------------
         *  0x00                reserved
         *  0x01                ISO/IEC 11172 video
         *  0x02                ITU-T Rec. H.262|ISO/IEC 13818-2 video
         *                      or ISO/IEC 11172-2 constrained parameter video stream
         *  0x04                ISO/IEC 13818-3 Audio
         *  ...
         * */
        unsigned char            stream_type;

        /*
         * 指定带有相关原始流或有效负载的传送流分段的 PID
         * */
        unsigned short           elementary_PID;

        /* 
         * 规定此字段之后相关原始流 descriptor 的字节数
         * */
        unsigned short           ES_info_length;

        vector<DescriptorBase *> descriptors;
    }PmtCompent_t;

    vector<PmtCompent_t>     m_compents;
};

#endif //_TS_PMT_SECTION_HPP_

