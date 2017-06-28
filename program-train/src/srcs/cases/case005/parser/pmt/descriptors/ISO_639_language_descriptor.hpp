/*
 * Progarm Name: ISO_639_language_descriptor.hpp
 * Created Time: 2017-06-28 15:11:17
 * Last modified: 2017-06-28 15:32:58
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _ISO_639_LANGUAGE_DESCRIPTOR_HPP_
#define _ISO_639_LANGUAGE_DESCRIPTOR_HPP_

#include <vector>

using std::vector;

struct ISO_639_language_descriptor : public DescriptorBase{
public:
    ISO_639_language_descriptor(CA_descriptorHeader_t *header = nullptr)
        : DescriptorBase(&header->header){
        if(nullptr != header){

            char *ptr = (char *)header;
            ptr += sizeof(CA_descriptorHeader_t);
            int N = (this->m_descriptor_length - 1)/3;
            for(int i=0; i<N; i++){
                int 
                language_code  = *ptr++ << 16;
                language_code |= *ptr++ << 8;
                language_code |= *ptr++;

                this->m_ISO_639_language_codes.push_back(language_code);
            }

            this->m_audio_type = *ptr;
        }
    }
    ~ISO_639_language_descriptor(){}
public:
    vector<int>             m_ISO_639_language_codes;
    unsigned char           m_audio_type;
};

#endif //_ISO_639_LANGUAGE_DESCRIPTOR_HPP_

