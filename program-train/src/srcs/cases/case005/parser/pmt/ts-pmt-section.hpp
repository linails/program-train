/*
 * Progarm Name: ts-pmt-section.hpp
 * Created Time: 2017-06-28 16:56:38
 * Last modified: 2017-06-28 17:02:22
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PMT_SECTION_HPP_
#define _TS_PMT_SECTION_HPP_

#include <vector>
#include "ts-descriptor.hpp"
#include "ts-pmt-header.h"

using std::vector;

struct TsPMTSection{
public:
    TsPMTSection(){}
    ~TsPMTSection(){}
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

