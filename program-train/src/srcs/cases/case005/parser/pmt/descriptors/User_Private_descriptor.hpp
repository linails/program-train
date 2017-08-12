/*
 * Progarm Name: User_Private_descriptor.hpp
 * Created Time: 2017-06-29 19:20:16
 * Last modified: 2017-06-29 19:50:17
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _USER_PRIVATE_DESCRIPTOR_HPP_
#define _USER_PRIVATE_DESCRIPTOR_HPP_

#include "ts-descriptor.hpp"
#include <vector>

using std::vector;

struct UserPrivate_descriptor : public DescriptorBase{
public:
    UserPrivate_descriptor(User_Private_descriptorHeader_t *header = nullptr)
        : DescriptorBase(&header->header){
        if(nullptr != header){
            char *ptr = (char *)header;
            ptr += sizeof(User_Private_descriptorHeader_t);
            int N = this->m_descriptor_length;
            for(int i=0; i<N; i++){
                this->m_private_data_bytes.push_back(*ptr++);
            }
        }
    }
    ~UserPrivate_descriptor(){}
public:
    vector<unsigned char>   m_private_data_bytes;
};

#endif //_USER_PRIVATE_DESCRIPTOR_HPP_

