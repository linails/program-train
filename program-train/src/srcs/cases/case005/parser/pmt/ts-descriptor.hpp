/*
 * Progarm Name: ts-descriptor.hpp
 * Created Time: 2017-06-28 13:52:34
 * Last modified: 2017-06-29 19:06:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_DESCRIPTOR_HPP_
#define _TS_DESCRIPTOR_HPP_

#include "ts-descriptor.h"
#include <cstdio>

struct DescriptorBase{
public:
    DescriptorBase(DescripHeader_t *header = nullptr){

        // if (nullptr == &(xxx)->header){}

        if(nullptr != header){
            this->m_descriptor_tag = header->descriptor_tag;
            this->m_descriptor_length = header->descriptor_length;
        }
    }
    virtual ~DescriptorBase(){}
public:
    unsigned char   m_descriptor_tag    = 0x00;

    /* 
     * 规定在此字段之后的描述子的字节数
     * */
    unsigned char   m_descriptor_length = 0x00;
};

#endif //_TS_DESCRIPTOR_HPP_

