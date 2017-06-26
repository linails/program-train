/*
 * Progarm Name: ts-unit.hpp
 * Created Time: 2017-06-26 10:29:27
 * Last modified: 2017-06-26 11:37:13
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _TS_UNIT_HPP_
#define _TS_UNIT_HPP_

#define TS_UNIT_LENGTH 188

class TsUnit{
public:
    TsUnit(const char *unit = nullptr);
    ~TsUnit();
private:
    char    m_buf[TS_UNIT_LENGTH] = {0, };
};

#endif //_TS_UNIT_HPP_

