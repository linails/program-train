/*
 * Progarm Name: disk-dic.cpp
 * Created Time: 2017-02-27 15:35:36
 * Last modified: 2017-02-28 17:19:05
 * @author: minphone.linails linails@foxmail.com 
 */

#include "disk-dic.hpp"
#include <iostream>
#include "sqlite3.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

/*
 * Tables
 *
 * Note :
 *  01 word     : 词
 *  02 spell    : 拼音
 *  03 remark   : 备注
 *  04 source   : 出处
 *  05 mean     : 意义
 *  06 char     : 词性
 * */
const char *DiskDic::CorpusTables[] = {
"create table CorpusWordSpell(word text, spell text, remark text, plural integer default 0, unique(word,spell))",
"create table CorpusWordMeans(word text, mean text, source text, remark text)",
"create table CorpusWordChars(word text, char text, mean text, source text, remark text)"
};

DiskDic::SqlOprts_t DiskDic::CorpusTableOprts[] = {
{"full|insert-WS|single",           "insert into CorpusWordSpell values('%s','%s','%s')"},
{"full|insert-WS|plural",           "insert into CorpusWordSpell values('%s','%s','%s',1)"},
{"part|insert-WS-word",             "insert into CorpusWordSpell(word) values('%s')"},
{"part|insert-WS-words",            "insert into CorpusWordSpell(words, plural) values('%s',1)"},
{"part|insert-WS-word/spell",       "insert into CorpusWordSpell(word, spell) values('%s','%s')"},
{"update-WS-spell",                 "update CorpusWordSpell set spell='%s' where word='%s'"}
};

DiskDic::DiskDic(string db)
    :m_db(db)
{
    /*1.open database*/
    int result = sqlite3_open(m_db.c_str(), &this->m_conn);
    if(result != SQLITE_OK){
        sqlite3_close(this->m_conn);
        cout << "[ERROR] open db failed" << endl;
        return;
    }else{
        cout << "open succeed !" << endl;
    }

    for(size_t i=0; i<sizeof(CorpusTableOprts)/sizeof(*CorpusTableOprts); i++){
        this->m_sqlmap[CorpusTableOprts[i].tag] = CorpusTableOprts[i].sql;
    }
}

DiskDic::~DiskDic()
{
    if(nullptr != this->m_conn){
        sqlite3_close(this->m_conn);
    }
}

int  DiskDic::init_tables(void)
{
    int ret = 0;

    for(size_t i=0; i<sizeof(CorpusTables)/sizeof(*CorpusTables); i++){
        sqlite3_stmt *stmt = NULL;

        if(SQLITE_OK != sqlite3_prepare_v2(this->m_conn, CorpusTables[i], strlen(CorpusTables[i]), &stmt, NULL)){
            if(stmt){
                sqlite3_finalize(stmt);
            }
            cout << "[ERROR] Create Table failed : " << CorpusTables[i] << endl;
            ret = -1;
            continue;
        }

        if(SQLITE_DONE != sqlite3_step(stmt)){
            sqlite3_finalize(stmt);
            cout << "[ERROR] step failed " << endl;
            ret = -1;
            continue;
        }

        if(stmt){
            sqlite3_finalize(stmt);
            cout << "Create Table Successed : " << CorpusTables[i] << endl;
        }
    }

    return ret;
}

int  DiskDic::insert_ws_single_full(string word, string spell, string remark)
{
    return 0;
}

int  DiskDic::insert_ws_plural_full(string word, string spell, string remark)
{
    return 0;
}

int  DiskDic::insert_ws_word(string word)
{
    return 0;
}

int  DiskDic::insert_ws_word(vector<string> &v_word)
{
    return 0;
}

int  DiskDic::insert_ws_word_spell(string word, string spell)
{
    sqlite3_stmt *stmt = NULL;
    char sql[512]      = {0, };

    sprintf(sql, this->m_sqlmap["part|insert-WS-word/spell"], word.c_str(), spell.c_str());

    if(sqlite3_prepare_v2(this->m_conn, sql, strlen(sql), &stmt, NULL) != SQLITE_OK){
        if(stmt)
            sqlite3_finalize(stmt);
        return -1;
    }
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        return -1;
    }

    /* 
     * release stmt
     * */
    sqlite3_finalize(stmt);

    return 0;
}

/*
 * <word,spell>
 * */
int  DiskDic::insert_ws_word_spell(vector<pair<string, string> > &v_word_spell)
{
    return 0;
}

