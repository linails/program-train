/*
 * Progarm Name: normal-pg.cpp
 * Created Time: 2017-01-17 20:31:13
 * Last modified: 2017-02-10 14:54:46
 * @author: minphone.linails linails@foxmail.com 
 */

#include "normal-pg.hpp"
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

NormalPg::NormalPg()
{
    try{
        string dbstr = "dbname=exampledb user=dbuser password=123456 hostaddr=127.0.0.1 port=5432";

        this->m_pqxx = new pqxx::connection(dbstr);
        if(NULL == this->m_pqxx){
            cout << "[Error] : new pqxx failed !" << endl;
        }else{
            cout << "connection successed !" << endl;

            /*
             * */
            //this->m_pqxx->prepare("xxxx", "select max(id) from bind_devices");

        }
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        exit(1);
    }
}

NormalPg::~NormalPg()
{
}

int  NormalPg::normalpg_main(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

