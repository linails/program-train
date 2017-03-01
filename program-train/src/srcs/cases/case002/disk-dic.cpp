/*
 * Progarm Name: disk-dic.cpp
 * Created Time: 2017-02-27 15:35:36
 * Last modified: 2017-03-01 17:43:22
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
"create table CorpusWordSpell(\
    id integer primary key unique,\
    word text,\
    spell text,\
    remark text,\
    plural integer default 0,\
    unique(word,spell))",
"create table CorpusWordMeans(\
    id integer primary key unique,\
    word text,\
    mean text,\
    source text,\
    remark text,\
    unique(word,mean))",
"create table CorpusWordChars(\
    id integer primary key unique,\
    word text,\
    char text,\
    mean text,\
    source text,\
    remark text,\
    unique(word,char))"
};

DiskDic::SqlOprts_t DiskDic::CorpusTableOprts[] = {
{"full|insert-WS|single",           "insert into CorpusWordSpell values('%s','%s','%s')"},
{"full|insert-WS|plural",           "insert into CorpusWordSpell values('%s','%s','%s',1)"},
{"full|insert-WS|bulk",             "insert into CorpusWordSpell values(?,?,?,?)"},
{"part|insert-WS-word",             "insert into CorpusWordSpell(word) values('%s')"},
{"part|insert-WS-words",            "insert into CorpusWordSpell(word, plural) values('%s',1)"},
{"part|insert-WS-word/spell",       "insert into CorpusWordSpell(word, spell) values('%s','%s')"},
{"part|insert-WS-words/spell",      "insert into CorpusWordSpell(word, spell, plural) values('%s','%s',1)"},
{"part|insert-WS-words/spell|bulk", "insert into CorpusWordSpell(word, spell, plural) values(?,?,?)"},
{"update-WS-spell",                 "update CorpusWordSpell set spell='%s' where word='%s'"},
{"update-WS-remark",                "update CorpusWordSpell set remark='%s' where word='%s'"},
{"update-WS-plural",                "update CorpusWordSpell set plural='%d' where word='%s'"},
{"select-WS|full-all",              "select * from CorpusWordSpell"},
{"select-WS|full-by(id)",           "select * from CorpusWordSpell where id='%d'"},
{"select-WS|full-by(word)",         "select * from CorpusWordSpell where word='%s'"}, // 可能返回多个 - 同音
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
{"select-WM|full-by(id)",           "select * from CorpusWordMeans where id='%d'"},
{"select-WM|full-by(word)",         "select * from CorpusWordMeans where word='%s'"}, // 可能返回多个 - 多义
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
{"select-WC|full-by(id)",           "select * from CorpusWordChars where id='%d'"},
{"select-WC|full-by(word)",         "select * from CorpusWordChars where word='%s'"}, // 可能返回多个 - 多义
{"select-WC|full-by(char)",         "select * from CorpusWordChars where char='%s'"}, // 可能返回多个
{"select-WC-char",                  "select char from CorpusWordChars where word='%s'"},
{"select-WC-mean",                  "select mean from CorpusWordChars where word='%s'"},
{"select-WC-source",                "select source from CorpusWordChars where word='%s'"},
{"select-WC-remark",                "select remark from CorpusWordChars where word='%s'"},
};

DiskDic::DiskDic(string db)
    :m_db(db)
{
    /*1.open database*/
    int result = sqlite3_open(m_db.c_str(), &this->m_conn);
    if(result != SQLITE_OK){
        sqlite3_close(this->m_conn);
        cout << "[Error] open db failed" << endl;
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

        if(SQLITE_OK != sqlite3_prepare_v2(this->m_conn,
                                           CorpusTables[i],
                                           strlen(CorpusTables[i]),
                                           &stmt,
                                           NULL)){
            if(stmt){
                sqlite3_finalize(stmt);
            }
            cout << "[Error] Create Table failed : " << CorpusTables[i] << endl;
            ret = -1;
            continue;
        }

        if(SQLITE_DONE != sqlite3_step(stmt)){
            sqlite3_finalize(stmt);
            cout << "[Error] step failed " << endl;
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

    if(1 < this->m_st.utf_count(word)){
        sprintf(sql, this->m_sqlmap["part|insert-WS-words/spell"], word.c_str(), spell.c_str());
    }else{
        sprintf(sql, this->m_sqlmap["part|insert-WS-word/spell"], word.c_str(), spell.c_str());
    }

    if(sqlite3_prepare_v2(this->m_conn,
                          sql,
                          strlen(sql),
                          &stmt,
                          NULL) != SQLITE_OK){
        if(stmt) sqlite3_finalize(stmt);
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
    sqlite3_stmt *stmt  = NULL;
    string beginSQL     = "begin transaction";
    string commitSQL    = "commit";

    /*
     * begin transaction
     * */
    if(sqlite3_prepare_v2(this->m_conn,
                          beginSQL.c_str(),
                          beginSQL.size(),
                          &stmt,
                          NULL) != SQLITE_OK){
        if(stmt) sqlite3_finalize(stmt);
        return -1;
    }
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);


    /* 
     * insert data
     * */
    auto bulk_init = [&stmt, this](){
        stmt = NULL;
        if(sqlite3_prepare_v2(this->m_conn, 
                              this->m_sqlmap["part|insert-WS-words/spell|bulk"], 
                              strlen(this->m_sqlmap["part|insert-WS-words/spell|bulk"]),
                              &stmt,
                              NULL) != SQLITE_OK){
            if(stmt) sqlite3_finalize(stmt);
            return -1;
        }else
            return 0;
    };

    if(0 != bulk_init()) return -1;

    for(auto &ws : v_word_spell){
        int plural = 0; if(1 < this->m_st.utf_count(ws.first)) plural = 1;

        sqlite3_bind_text(stmt, 1, ws.first.c_str(),  ws.first.size(), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, ws.second.c_str(), ws.second.size(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt,  3, plural);

        if(sqlite3_step(stmt) != SQLITE_DONE){
            sqlite3_finalize(stmt);
            if(0 != bulk_init()) return -1;
            cout << "[Error] sqlite-step failed !" << endl;
            continue;
        }

        sqlite3_reset(stmt);
    }
    if(stmt) sqlite3_finalize(stmt);


    /*
     * commit
     * */
    stmt = NULL;
    if(sqlite3_prepare_v2(this->m_conn, 
                          commitSQL.c_str(),
                          commitSQL.size(),
                          &stmt,
                          NULL) != SQLITE_OK){
        if(stmt) sqlite3_finalize(stmt);
        return -1;
    }
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);

    return 0;
}

int  DiskDic::get_spell(vector<string> &spells, string word)
{
    sqlite3_stmt *stmt  = NULL;
    char sql[512]       = {0, };
    sprintf(sql, this->m_sqlmap["select-WS-spell"], word.c_str());

    if(sqlite3_prepare_v2(this->m_conn,
                          sql,
                          strlen(sql),
                          &stmt,
                          NULL) != SQLITE_OK){
        if(stmt) sqlite3_finalize(stmt);
        return -1;
    }

    do{
        int ret = sqlite3_step(stmt);
        if(SQLITE_ROW == ret){
            string spell = (const char *)sqlite3_column_text(stmt, 0);
            spells.push_back(spell);
        }else if(SQLITE_DONE == ret){
            break;
        }else{
            cout << "[Error] select failed" << endl;
            sqlite3_finalize(stmt);
            return -1;
        }
    }while(1);

    return 0;
}

int  DiskDic::get_word_spell(vector<pair<string, string> > &v_word_spell)
{
    sqlite3_stmt *stmt  = NULL;

    if(sqlite3_prepare_v2(this->m_conn,
                          this->m_sqlmap["select-WS|full-all"],
                          strlen(this->m_sqlmap["select-WS|full-all"]),
                          &stmt, NULL) != SQLITE_OK){
        if(stmt) sqlite3_finalize(stmt);
        return -1;
    }

    v_word_spell.clear();

    do{
        int ret = sqlite3_step(stmt);

        if(SQLITE_ROW == ret){
            //int id = sqlite3_column_int(stmt, 0); cout << "id = " << id << endl;
            string word((const char *)sqlite3_column_text(stmt, 1));
            string spell((const char *)sqlite3_column_text(stmt, 2));
            v_word_spell.push_back(make_pair(word, spell));
        }else if(SQLITE_DONE == ret){
            break;
        }else{
            cout << "[Error] select failed" << endl;
            sqlite3_finalize(stmt);
            return -1;
        }

    }while(1);

    if(stmt) sqlite3_finalize(stmt);

    return 0;
}

