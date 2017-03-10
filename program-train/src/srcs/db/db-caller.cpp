/*
 * Progarm Name: db-caller.cpp
 * Created Time: 2016-12-20 17:32:32
 * Last modified: 2017-03-10 17:18:37
 * @author: minphone.linails linails@foxmail.com 
 */

#include "db-caller.hpp"
#include <iostream>
#include "normal.hpp"
#include "normal-pg.hpp"
#include "advanced.hpp"
#include "mos.hpp"
#include <string>
#include <cassert>
#include "normal-redis.hpp"

using std::cout;
using std::endl;
using std::string;

dbCaller::dbCaller()
{
}

dbCaller::~dbCaller()
{
}

int  dbCaller::dbcaller_main(int argc, char **argv)
{
    int ret = 0;

    //ret = this->sqlite_normal(argc, argv); assert(-1 != ret);
    
    //ret = this->sqlite_advanced(argc, argv); assert(-1 != ret);

    //ret = this->postgresql_normal(argc, argv); assert(-1 != ret);

    //ret = this->postgresql_advanced(argc, argv); assert(-1 != ret);

    ret = this->redis_normal(argc, argv); assert(-1 != ret);

    return ret;
}

int  dbCaller::sqlite_normal(int argc, char **argv)
{
    int ret = 0;

    Mos mos;
    string path = mos.pwd();
    cout << "get pwd : " << path << endl;

    path.clear();
    cout << "path : " << path << endl;

    mos.pwd(path);
    cout << "path : " << path << endl;

    NormalDB ndb(path, "first.db");
    //ndb.generic_insert();

    //ndb.bulk_insert();

    //ndb.get_schema();

#if 0
    if(-1 == ndb.query()){
        cout << "ndb.query() failed " << endl;
    }
#endif

    ndb.query(0);

    return ret;
}

int  dbCaller::sqlite_advanced(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

int  dbCaller::postgresql_normal(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

int  dbCaller::postgresql_advanced(int argc, char **argv)
{
    int ret = 0;

    return ret;
}

int  dbCaller::redis_normal(int argc, char **argv)
{
    int ret = 0;

    NormalRedis nreids;

    ret = nreids.main(argc, argv); assert(-1 != ret);

    return ret;
}

