/*
 * Progarm Name: ts-parser.h
 * Created Time: 2017-06-22 13:23:10
 * Last modified: 2017-06-23 19:35:46
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_PARSER_H_
#define _TS_PARSER_H_
#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

    typedef struct{
        char    sync_byte;
    }TsHeader_t;

#ifdef __cplusplus
}
#endif
#endif //_TS_PARSER_H_

