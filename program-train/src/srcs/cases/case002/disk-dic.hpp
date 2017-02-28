/*
 * Progarm Name: disk-dic.hpp
 * Created Time: 2017-02-27 15:35:40
 * Last modified: 2017-02-28 16:48:24
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DISK_DIC_HPP_
#define _DISK_DIC_HPP_

#include "sqlite3.h"
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;
using std::pair;

class DiskDic{
public:
    DiskDic(string db);
    ~DiskDic();
    int  init_tables(void);
    int  insert_ws_single_full(string word, string spell, string remark);
    int  insert_ws_plural_full(string word, string spell, string remark);
    int  insert_ws_word(string word);
    int  insert_ws_word(vector<string> &v_word);
    int  insert_ws_word_spell(string word, string spell);
    int  insert_ws_word_spell(vector<pair<string, string> > &v_word_spell); // <word,spell>
private:
    typedef struct{ const char *tag; const char *sql; }SqlOprts_t;
    typedef map<const char *, const char *> SqlMap_t;
    static const char *CorpusTables[];
    static SqlOprts_t CorpusTableOprts[];
private:
    string      m_db;
    sqlite3    *m_conn = nullptr;
    SqlMap_t    m_sqlmap;
};

#endif //_DISK_DIC_HPP_
