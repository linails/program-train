/*
 * Progarm Name: ts-unit.hpp
 * Created Time: 2017-06-26 10:29:27
 * Last modified: 2017-06-27 17:21:54
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_UNIT_HPP_
#define _TS_UNIT_HPP_

#define TS_UNIT_LENGTH 188

#pragma pack(1)
typedef struct{
    /* byte[0] : sync_byte - fixed value 0x47 */
    unsigned char   sync_byte;

    /* byte[1] */
    unsigned char   PID_high5 : 5;
    unsigned char   transport_priority : 1;
    unsigned char   payload_unit_start_indicator : 1;
    unsigned char   transport_error_indicator : 1;

    /* byte[2] */
    unsigned char   PID_low8;

    /* byte[3] */
    unsigned char   continuity_counter : 4;
    unsigned char   adaptation_field_control : 2;
    unsigned char   transport_scrambling_control : 2;
}TsHeader_t;

typedef struct{
    TsHeader_t      header;
    unsigned char   data[TS_UNIT_LENGTH - 4];
}TsPacket_t;

typedef struct{
    unsigned char   adaptation_field_length;
}TsAdaptationField_t;


class TsUnit{
public:
    TsUnit(const char *unit = nullptr);
    ~TsUnit();
    int  info(void);
    int  parser(void);
private:
    char    m_buf[TS_UNIT_LENGTH] = {0, };
    int     m_spos = -1;    // data[m_spos] ... data[m_epos]
    int     m_epos = -1;    //

private: // TsAdaptationField_t
    /* 
     * */
    int     m_adaptation_field_length = -1;

private: // TsHeader_t
    /*
     * 表明在相关的传送分组中至少有一个不可纠正的错误位
     * */
    char    m_transport_error_indicator;

    /*
     * 用来指示 TS 分组带有 PES 或 PSI 数据的情况
     *  1> PES 分组
     *     val=1 : 表明传送流分组的有效负载将以 PES 分组的第一个字节开始
     *             (该位为 1，表明在所有传送流分组中，有且仅有一个以 PES 分组开始)
     *     val=0 : 表明传送流的开始不是 PES 分组
     *  2> PSI 分组
     *     val=1 : 传送流分组带有一个 PSI 部分的第一个字节
     *             (表明传送流分组的第一个字节带有 pointer_field)
     *     val=0 : 传送流分组不带有一个 PSI 部分的第一个字节
     *             (表明传送流分组的有效负载中没有 pointer_field)
     *  3> 空分组
     *     空分组应置为 0
     * */
    char    m_payload_unit_start_indicator;

    /* 
     * 当 val=1 时，表示该分组比具有相同 PID 的分组的优先级高
     * */
    char    m_transport_priority;

    /* 
     * 空分组的 PID = 0x1fff
     *  1> 0x0000 : PAT
     *  2> 0x0001 : CAT
     * */
    int     m_PID = -1;

    /* 
     * */
    char    m_transport_scrambling_control;

    /*
     * 用于指示 TsHeader_t 后面是否跟 "调整字段/负载"
     *  val = 0> 应丢弃
     *  val = 1> 无调整字段，仅含负载
     *  val = 2> 仅含调整字段
     *  val = 3> 含调整字段 + 负载
     * */
    char    m_adaptation_field_control;

    char    m_continuity_counter;
};

#endif //_TS_UNIT_HPP_

