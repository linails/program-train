/*
 * Progarm Name: disk-dic.cpp
 * Created Time: 2017-02-27 15:35:36
 * Last modified: 2017-02-28 20:19:40
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
"create table CorpusWordMeans(word text, mean text, source text, remark text, unique(word,mean))",
"create table CorpusWordChars(word text, char text, mean text, source text, remark text, unique(word,char))"
};

DiskDic::SqlOprts_t DiskDic::CorpusTableOprts[] = {
{"full|insert-WS|single",           "insert into CorpusWordSpell values('%s','%s','%s')"},
{"full|insert-WS|plural",           "insert into CorpusWordSpell values('%s','%s','%s',1)"},
{"part|insert-WS-word",             "insert into CorpusWordSpell(word) values('%s')"},
{"part|insert-WS-words",            "insert into CorpusWordSpell(words, plural) values('%s',1)"},
{"part|insert-WS-word/spell",       "insert into CorpusWordSpell(word, spell) values('%s','%s')"},
{"update-WS-spell",                 "update CorpusWordSpell set spell='%s' where word='%s'"},
{"update-WS-remark",                "update CorpusWordSpell set remark='%s' where word='%s'"},
{"update-WS-plural",                "update CorpusWordSpell set plural='%d' where word='%s'"},
{"select-WS|full",                  "select * from CorpusWordSpell where word='%s'"}, // 可能返回多个 - 同音
{"select-WS-spell",                 "select spell from CorpusWordSpell where word='%s'"},
{"select-WS-remark",                "select remark from CorpusWordSpell where word='%s'"},
{"select-WS-plural",                "select plural from CorpusWordSpell where word='%s'"},
{"full|insert-WM",                  "insert into CorpusWordMeans values('%s','%s','%s','%s')"},
{"part|insert-WM-word",             "insert into CorpusWordMeans(word) values('%s')"},
{"part|insert-WM-word/mean",        "insert into CorpusWordMeans(word, mean) values('%s','%s')"},
{"part|insert-WM-word/mean/source", "insert into CorpusWordMeans(word, mean, source) values('%s','%s','%s')"},
{"part|insert-WM-word/remark",      "insert into CorpusWordMeans(word, remark) values('%s','%s')"},
{"update-WM-mean",                  "update CorpusWordMeans set mean='%s' where word='%s'"},
{"update-WM-source",                "update CorpusWordMeans set source='%s' where word='%s'"},
{"update-WM-remark",                "update CorpusWordMeans set remark='%s' where word='%s'"},
{"select-WM|full",                  "select * from CorpusWordMeans where word='%s'"}, // 可能返回多个 - 多义
{"select-WM-mean",                  "select mean from CorpusWordMeans where word='%s'"},
{"select-WM-source",                "select source from CorpusWordMeans where word='%s'"},
{"select-WM-remark",                "select remark from CorpusWordMeans where word='%s'"},
{"full|insert-WC",                  "insert CorpusWordChars into values('%s','%s','%s','%s','%s')"},
{"part|insert-WC-word",             "insert into CorpusWordChars(word) values('%s')"},
{"part|insert-WC-word/char",        "insert into CorpusWordChars(word, char) values('%s','%s')"},
{"part|insert-WC-word/mean",        "insert into CorpusWordChars(word, mean) values('%s','%s')"},
{"part|insert-WC-word/mean/source", "insert into CorpusWordChars(word, mean, source) values('%s','%s','%s')"},
{"part|insert-WC-word/remark",      "insert into CorpusWordChars(word, remark) values('%s','%s')"},
{"update-WC-char",                  "update CorpusWordChars set char='%s' where word='%s'"},
{"update-WC-mean",                  "update CorpusWordChars set mean='%s' where word='%s'"},
{"update-WC-source",                "update CorpusWordChars set source='%s' where word='%s'"},
{"update-WC-remark",                "update CorpusWordChars set remark='%s' where word='%s'"},
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

