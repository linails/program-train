/*
 * Progarm Name: User_Private.hpp
 * Created Time: 2017-06-29 19:20:16
 * Last modified: 2017-06-29 19:25:21
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _USER_PRIVATE_HPP_
#define _USER_PRIVATE_HPP_

#include "ts-descriptor.hpp"
#include <vector>

using std::vector;

struct UserPrivate : public DescriptorBase{
public:
    UserPrivate(User_PrivateHeader_t *header = nullptr)
        : DescriptorBase(&header->header){
        if(nullptr != header){
            char *ptr = (char *)header;
            ptr += sizeof(User_PrivateHeader_t);
            int N = this->m_descriptor_length;
            for(int i=0; i<N; i++){
                this->m_private_data_bytes.push_back(*ptr++);
            }
        }
    }
    ~UserPrivate(){}
public:
    vector<unsigned char>   m_private_data_bytes;
};

#endif //_USER_PRIVATE_HPP_

