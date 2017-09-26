/*
 * Progarm Name: ts-pmt-header.h
 * Created Time: 2017-06-28 16:29:11
 * Last modified: 2017-06-29 17:27:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PMT_HEADER_H_
#define _TS_PMT_HEADER_H_
#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
typedef struct{
    /* byte[0] */
    unsigned char   table_id;

    /* byte[1] */
    unsigned char   section_length_high4 : 4;
    unsigned char   reserved0 : 2;
    unsigned char   reserved1 : 1;
    unsigned char   section_syntax_indicator : 1;

    unsigned char   section_length_low8;    // byte[2]
    unsigned char   program_number_high8;   // byte[3]
    unsigned char   program_number_low8;    // byte[4]

    /* byte[5] */
    unsigned char   current_next_indicator : 1;
    unsigned char   version_number : 5;
    unsigned char   reserved3 : 2;

    unsigned char   section_number;         // byte[6]
    unsigned char   last_section_number;    // byte[7]

    /* byte[8] */
    unsigned char   PCR_PID_high5 : 5;
    unsigned char   reserved4 : 3;

    unsigned char   PCR_PID_low8;           // byte[9]

    /* byte[10] */
    unsigned char   program_info_length_high4 : 4;
    unsigned char   reserved5 : 4;

    unsigned char   program_info_length_low8;// byte[11]
}TsPmtHeader_t;

typedef struct{
    unsigned char   stream_type;            // byte[0]

    /* byte[1] */
    unsigned char   elementary_PID_high5 : 5;
    unsigned char   reserved : 3;

    unsigned char   elementary_PID_low8;    // byte[2]

    /* byte[3] */
    unsigned char   ES_info_length_high4 : 4;
    unsigned char   reserved0 : 4;

    unsigned char   ES_info_length_low8;    // byte[4]
}PmtComponentsHeader_t;

#ifdef __cplusplus
}
#endif
#endif //_TS_PMT_HEADER_H_

