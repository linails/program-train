/*
 * Progarm Name: normal.hpp
 * Created Time: 2016-11-23 21:53:14
 * Last modified: 2017-01-05 22:06:35
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _NORMAL_HPP_
#define _NORMAL_HPP_

#include "sqlite3.h"
#include <string>

using std::string;

class NormalDB {
public:
    NormalDB(string path, string db);
    ~NormalDB();
    int generic_insert(void);
    int bulk_insert(void);
    int get_schema(void);
    int query(void);
    int query(int);
private:
    char *strlwr(char *str);
private:
    string   m_path;
    string   m_db;
    sqlite3 *m_conn = NULL;
};

#endif //_NORMAL_HPP_

