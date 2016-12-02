/*
 * Progarm Name: db_test.cpp
 * Created Time: 2016-11-23 21:53:39
 * Last modified: 2016-12-01 22:17:24
 * @author: minphone.linails linails@foxmail.com 
 */

#include "normal.hpp"
#include "normal-pg.hpp"
#include "advanced.hpp"
#include "db_test.hpp"
#include <iostream>
#include "mos.hpp"

using std::cout;
using std::endl;

void db_test(void)
{
    cout << "----------- db_test -----------" << endl;

    Mos mos;
    string path = mos.pwd();
    cout << "get pwd : " << path << endl;

    path.clear();
    cout << "path : " << path << endl;

    mos.pwd(path);
    cout << "path : " << path << endl;

    NormalDB ndb(path, "first.db");
    ndb.generic_insert();

    ndb.bulk_insert();

    ndb.get_schema();

    if(-1 == ndb.query()){
        cout << "ndb.query() failed " << endl;
    }
}



