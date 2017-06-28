/*
 * Progarm Name: ts-pes.hpp
 * Created Time: 2017-06-27 15:28:38
 * Last modified: 2017-06-28 17:11:58
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PES_HPP_
#define _TS_PES_HPP_

#pragma pack(1)
typedef struct{
    unsigned char   packet_start_code_prefix_high8;
    unsigned char   packet_start_code_prefix_mid8;
    unsigned char   packet_start_code_prefix_low8;
    unsigned char   stream_id;
    unsigned char   PES_packet_length_high8;
    unsigned char   PES_packet_length_low8;
}TsPesHeader_t;

class TsPES{
public:
    TsPES();
    ~TsPES();
private:
    /* 
     * 与其后的 stream_id 一起构成标示一个分组开始的分组开始码字
     * fixed val : 0x000001     - 24-bits
     * */
    unsigned        m_packet_start_code_prefix;

    /*
     * */
    unsigned char   m_stream_id;

    /*
     * */
    unsigned short  m_PES_packet_length;
};

#endif //_TS_PES_HPP_

