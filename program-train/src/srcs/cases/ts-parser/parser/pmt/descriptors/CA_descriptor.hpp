/*
 * Progarm Name: CA_descriptor.hpp
 * Created Time: 2017-06-28 15:08:44
 * Last modified: 2017-06-29 19:06:01
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CA_DESCRIPTOR_HPP_
#define _CA_DESCRIPTOR_HPP_

#include "ts-descriptor.hpp"
#include <vector>

using std::vector;

struct CA_descriptor : public DescriptorBase{
public:
    CA_descriptor(CA_descriptorHeader_t *header = nullptr)
        : DescriptorBase(&header->header){
        if(nullptr != header){
            this->m_CA_system_ID = header->CA_system_ID_high8 << 8;
            this->m_CA_system_ID|= header->CA_system_ID_low8;

            this->m_CA_PID       = header->CA_PID_high5 << 8;
            this->m_CA_PID      |= header->CA_PID_low8;

            char *ptr = (char *)header;
            ptr += sizeof(CA_descriptorHeader_t);
            int N = this->m_descriptor_length - 4;
            for(int i=0; i<N; i++){
                this->m_private_data_bytes.push_back(*ptr++);
            }
        }
    }
    ~CA_descriptor(){}
public:
    unsigned short          m_CA_system_ID;
    unsigned short          m_CA_PID;
    vector<unsigned char>   m_private_data_bytes;
};

#endif //_CA_DESCRIPTOR_HPP_

