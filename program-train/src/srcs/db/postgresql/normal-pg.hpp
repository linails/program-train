/*
 * Progarm Name: normal-pg.hpp
 * Created Time: 2017-01-17 20:31:10
 * Last modified: 2017-01-17 20:46:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _NORMAL_PG_HPP_
#define _NORMAL_PG_HPP_

#include "pqxx/pqxx"

class NormalPg{
public:
    NormalPg();
    ~NormalPg();
    int  normalpg_main(int argc, char **argv);
private:
    pqxx::connection   *m_pqxx = NULL;
};

#endif //_NORMAL_PG_HPP_

