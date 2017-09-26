/*
 * Progarm Name: ts-descriptor.h
 * Created Time: 2017-06-28 14:26:13
 * Last modified: 2017-06-29 19:47:44
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_DESCRIPTOR_H_
#define _TS_DESCRIPTOR_H_
#ifdef __cplusplus
extern "C" {
#endif

/* 
 * program and program element descriptors are structures which may be used
 * to extend the definitions of programs and program elements
 *
 * All descriptors have a format which begins with an 8-bits tag value
 *
 * descriptor tag 之后为8位描述符长度和数据字段
 *
 * ---------------------------------------------------------
 *  descriptor_tag  |   Identification
 * ---------------------------------------------------------
 *        9         |   CA_descriptor
 *        10        |   ISO_639_language_descriptor
 * */

#pragma pack(1)
typedef struct{
    unsigned char   descriptor_tag;
    unsigned char   descriptor_length;
}DescripHeader_t;


/* 
 * */
typedef struct{
    DescripHeader_t header;
    unsigned char   CA_system_ID_high8;
    unsigned char   CA_system_ID_low8;

    unsigned char   CA_PID_high5 : 5;
    unsigned char   reserved : 3;

    unsigned char   CA_PID_low8;
}CA_descriptorHeader_t;


typedef struct{
    DescripHeader_t header;
}ISO_639_language_descriptorHeader_t;

typedef struct{
    DescripHeader_t header;
}User_Private_descriptorHeader_t;

#ifdef __cplusplus
}
#endif
#endif //_TS_DESCRIPTOR_H_

