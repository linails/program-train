/*
 * Progarm Name: ts-pat.hpp
 * Created Time: 2017-06-27 15:20:02
 * Last modified: 2017-06-28 12:26:48
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PAT_HPP_
#define _TS_PAT_HPP_

#include <map>

using std::map;

#pragma pack(1)
typedef struct{
    /* byte[0] */
    unsigned char   table_id;

    /* byte[1] */
    unsigned char   section_length_high4 : 4;
    unsigned char   reserved1 : 2;
    unsigned char   reserved0 : 1; // fixed valued '0'
    unsigned char   section_syntax_indicator : 1;

    /* byte[2] */
    unsigned char   section_length_low8;

    unsigned char   transport_stream_id_high8;/* byte[3] */
    unsigned char   transport_stream_id_low8; /* byte[4] */

    /* byte[5] */
    unsigned char   current_next_indicator : 1;
    unsigned char   version_number : 5;
    unsigned char   reserved3 : 2;

    unsigned char   section_number;           /* byte[6] */
    unsigned char   last_section_number;      /* byte[7] */
}TsPatHeader_t;
#pragma pack()

class TsPAT{
public:
    TsPAT();
    ~TsPAT();
    int  load_data(const char *buf, int cnt);
    int  info(void);
    int  parser(const char *buf);
private:
    int  crc(void);
private:
    char            m_buf[512] = {0, };
private:
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
     * 应置位 1，暂无其他意义
     * */
    unsigned char   m_section_syntax_indicator;

    /* 
     * 表示在字段 section_length 之后的此分段的字节数(include CRC)
     * */
    unsigned char   m_section_length;

    /*
     * 用户定义的 stream_id ，用于在一个网络中多路复用中识别此
     * 传送流
     * */
    unsigned short  m_transport_stream_id;

    /* 
     * 5 bit
     * PAT 的版本号，随着 PAT 的改变而 +1, range[0, 31]
     *  1> val = 1 : 为当前可用 PAT
     *  2> val = 0 : 为下一个可用的 PAT
     * */
    unsigned char   m_version_number;

    /* 
     *  1> val = 1 : 表示所发送的 PAT 当前有效
     *  2> val = 0 : 表示所发送的 PAT 不可用，下一个表才可以用
     * */
    unsigned char   m_current_next_indicator;

    /* 
     * PAT 的第一个分段的 section_number 应为 0x00
     * 它随着 PAT 的每一个附加分段而 +1
     * */
    unsigned char   m_section_number;

    /*
     * PAT 的最后一个分段的号码
     * */
    unsigned char   m_last_section_number;

    /* 
     * map<program_number, network_PID/program_map_number>
     *  1> 当 program_number = 0x0000
     *     map<>.second 为 network_PID，指定含有网络信息表(NIT)的传送流分组的 PID
     *  2> 当 program_number = other val
     *     map<>.second 为 program_map_number，指定了传送流分组的 PID
     * */
    map<int, int>   m_prg_num_pids;
};

#endif //_TS_PAT_HPP_

