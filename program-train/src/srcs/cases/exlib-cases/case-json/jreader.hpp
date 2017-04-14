/*
 * Progarm Name: jreader.hpp
 * Created Time: 2017-01-20 22:01:20
 * Last modified: 2017-01-20 22:10:44
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _JREADER_HPP_
#define _JREADER_HPP_

template<typename T>
class JsonReader{
public:
    JsonReader(T data):m_data(data){};
    ~JsonReader(){};
    T  get_data(void){return this->m_data;};
private:
    T   m_data;
};

#endif //_JREADER_HPP_

