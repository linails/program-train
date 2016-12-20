/*
 * Progarm Name: db-caller.hpp
 * Created Time: 2016-12-20 17:32:38
 * Last modified: 2016-12-20 17:39:38
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DB_CALLER_HPP_
#define _DB_CALLER_HPP_

class dbCaller{
public:
    dbCaller();
    ~dbCaller();
    int  dbcaller_main(int argc, char **argv);
private:
    int  sqlite_normal(int argc, char **argv);
    int  sqlite_advanced(int argc, char **argv);
};

#endif //_DB_CALLER_HPP_

