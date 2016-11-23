/*
 * Progarm Name: normal.cpp
 * Created Time: 2016-11-23 21:53:09
 * Last modified: 2016-11-23 22:23:47
 * @author: minphone.linails linails@foxmail.com 
 */

#include "normal.hpp"
#include <iostream>
#include "sqlite3.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

NormalDB::NormalDB()
{
}

NormalDB::~NormalDB()
{
}

int NormalDB::generic_insert(void)
{
    sqlite3 * conn = NULL;

    /*1.open database*/
    int result = sqlite3_open("./disk/first.db",&conn);
    if(result != SQLITE_OK){
        sqlite3_close(conn);
        return -1;
    }

    const char *createTableSQL = 
        "create table testtable(int_col int,float_col real,string_col text)";
    sqlite3_stmt *stmt = NULL;
    int len = strlen(createTableSQL);


    /*2.准备创建数据表，如果创建失败，需要用sqlite3_finalize释放sqlite3_stmt对象，以防止内存泄漏*/
    if(sqlite3_prepare_v2(conn,createTableSQL,len,&stmt,NULL) != SQLITE_OK){
        if(stmt){
            sqlite3_finalize(stmt);
        }
        sqlite3_close(conn);
        return -1;
    }


    /*3.通过sqlite3_step命令执行创建表的语句，对于DDL和DML语句而言，sqlite3_step执行正确的返回值
     * 只有SQLITE_DNOE，对于SELECT查询而言，如果有数据返回SQLITE_ROW，当到达结果集末尾时则返回
     * SQLITE_DONE*/
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        sqlite3_close(conn);
        return -1;
    }


    /*4.释放创建表语句对象的资源*/
    sqlite3_finalize(stmt);
    cout<<"succeed to create test table now..."<<endl;


    /*5.构建插入数据的sqlite3_stmt对象*/
    int insertCount = 10;
    const char *insertSQL = "insert into testtable values(%d,%f,'%s')";
    const char *testString = "this is a test.";
    char sql[1024];
    sqlite3_stmt *stmt2 = NULL;
    for(int i=0;i<insertCount;++i){
        sprintf(sql,insertSQL,i,i * 1.0,testString);
        if(sqlite3_prepare_v2(conn,sql,strlen(sql),&stmt2,NULL) != SQLITE_OK){
            if(stmt2)
                sqlite3_finalize(stmt2);
            sqlite3_close(conn);
            return -1;
        }
        if(sqlite3_step(stmt2) != SQLITE_DONE){
            sqlite3_finalize(stmt2);
            sqlite3_close(conn);
            return -1;
        }
        cout<<"Insert success"<<endl;
    }
    sqlite3_finalize(stmt2);


    /*6.为了方便下一次测试运行，这里需要删除该函数创建的数据表，否则在下次
     * 运行时将无法创建该表，因为它已经存在*/
    const char *dropSQL = "drop table testtable";
    sqlite3_stmt *stmt3 = NULL;
    if(sqlite3_prepare_v2(conn,dropSQL,strlen(dropSQL),&stmt3,NULL) != SQLITE_OK){
        if(stmt3)
            sqlite3_finalize(stmt3);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt3) == SQLITE_DONE){
        cout<<"The test table has been dropped."<<endl;
    }
    sqlite3_finalize(stmt3);
    sqlite3_close(conn);
    return 0;
}

int NormalDB::bulk_insert(void)
{
    sqlite3 * conn = NULL;

    /*1.open database*/
    int result = sqlite3_open("./disk/first.db",&conn);
    if(result != SQLITE_OK){
        sqlite3_close(conn);
        return -1;
    }

    const char *createTableSQL = 
        "create table testtable(int_col int,float_col real,string_col text)";
    sqlite3_stmt *stmt = NULL;
    int len = strlen(createTableSQL);


    /*2.准备创建数据表，如果创建失败，需要用sqlite3_finalize释放sqlite3_stmt对象，以防止内存泄漏*/
    if(sqlite3_prepare_v2(conn,createTableSQL,len,&stmt,NULL) != SQLITE_OK){
        if(stmt){
            sqlite3_finalize(stmt);
        }
        sqlite3_close(conn);
        return -1;
    }


    /*3.通过sqlite3_step命令执行创建表的语句，对于DDL和DML语句而言，sqlite3_step执行正确的返回值
     * 只有SQLITE_DNOE，对于SELECT查询而言，如果有数据返回SQLITE_ROW，当到达结果集末尾时则返回
     * SQLITE_DONE*/
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        sqlite3_close(conn);
        return -1;
    }


    /*4.释放创建表语句对象的资源*/
    sqlite3_finalize(stmt);
    cout<<"succeed to create test table now..."<<endl;


    /*5.显式的开启一个事务*/
    sqlite3_stmt *stmt2 = NULL;
    const char *beginSQL = "begin transaction";
    if(sqlite3_prepare_v2(conn,beginSQL,strlen(beginSQL),&stmt2,NULL) != SQLITE_OK){
        if(stmt2)
            sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt2) != SQLITE_DONE){
        sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return -1;
    }
    sqlite3_finalize(stmt2);


    /*6.构建基于绑定变量的插入数据*/
    cout<<"6. ..."<<endl;
    const char *insertSQL = "insert into testtable values(?,?,?)";
    sqlite3_stmt *stmt3 = NULL;
    if(sqlite3_prepare_v2(conn,insertSQL,strlen(insertSQL),&stmt3,NULL) != SQLITE_OK){
        if(stmt3)
            sqlite3_finalize(stmt3);
        sqlite3_close(conn);
        return -1;
    }
    int insertCount = 10;
    const char *strData = "This is a test.";


    /*7.基于已有的SQL语句，迭代的绑定不同的变量数据*/
    cout<<"7. ..."<<endl;
    for(int i=0;i<insertCount;i++){
        /*在绑定时，最左面的变量索引值是1*/
        sqlite3_bind_int(stmt3,1,i);
        sqlite3_bind_double(stmt3,2,i * 1.0);
        sqlite3_bind_text(stmt3,3,strData,strlen(strData),SQLITE_TRANSIENT);
        if(sqlite3_step(stmt3) != SQLITE_DONE){
            sqlite3_finalize(stmt3);
            sqlite3_close(conn);
            cout<<"sqlite3_close"<<endl;
            return -1;
        }
        /*重新初始化该sqlite3_stmt对象绑定的变量*/
        sqlite3_reset(stmt3);
        cout<<"Insert succeed"<<endl;
    }
    sqlite3_finalize(stmt3);


    /*8.提交之前的事物*/
    cout<<"8. ..."<<endl;
    const char *commitSQL = "commit";
    sqlite3_stmt *stmt4 = NULL;
    if(sqlite3_prepare_v2(conn,commitSQL,strlen(commitSQL),&stmt4,NULL) != SQLITE_OK){
        if(stmt4)
            sqlite3_finalize(stmt4);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt4) != SQLITE_DONE){
        sqlite3_finalize(stmt4);
        sqlite3_close(conn);
        return -1;
    }
    sqlite3_finalize(stmt4);


    /*9.为了方便下一次测试运行，这里需要删除该函数创建的数据表，否则在下次
     * 运行时将无法创建该表，因为它已经存在*/
    cout<<"9. ..."<<endl;
    const char *dropSQL = "drop table testtable";
    sqlite3_stmt *stmt5 = NULL;
    if(sqlite3_prepare_v2(conn,dropSQL,strlen(dropSQL),&stmt5,NULL) != SQLITE_OK){
        if(stmt5)
            sqlite3_finalize(stmt5);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt5) == SQLITE_DONE){
        cout<<"The test table has been dropped."<<endl;
    }
    sqlite3_finalize(stmt5);
    sqlite3_close(conn);
    return 0;
}

int NormalDB::get_schema(void)
{
    sqlite3 * conn = NULL;

    /*1.open database*/
    int result = sqlite3_open("./disk/first.db",&conn);
    if(result != SQLITE_OK){
        sqlite3_close(conn);
        return -1;
    }

    const char *createTableSQL = 
        "create table testtable(int_col int,float_col real,string_col text)";
    sqlite3_stmt *stmt = NULL;
    int len = strlen(createTableSQL);


    /*2.准备创建数据表，如果创建失败，需要用sqlite3_finalize释放sqlite3_stmt对象，以防止内存泄漏*/
    if(sqlite3_prepare_v2(conn,createTableSQL,len,&stmt,NULL) != SQLITE_OK){
        if(stmt){
            sqlite3_finalize(stmt);
        }
        sqlite3_close(conn);
        return -1;
    }


    /*3.通过sqlite3_step命令执行创建表的语句，对于DDL和DML语句而言，sqlite3_step执行正确的返回值
     * 只有SQLITE_DNOE，对于SELECT查询而言，如果有数据返回SQLITE_ROW，当到达结果集末尾时则返回
     * SQLITE_DONE*/
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        sqlite3_close(conn);
        return -1;
    }


    /*4.释放创建表语句对象的资源*/
    sqlite3_finalize(stmt);
    cout<<"succeed to create test table now..."<<endl;


    /*5.构造查询表数据的sqlite3_stmt对象*/
    const char *selectSQL = "select * from testtable where 1 = 0";
    sqlite3_stmt *stmt2 = NULL;
    if(sqlite3_prepare_v2(conn,selectSQL,strlen(selectSQL),&stmt2,NULL) != SQLITE_OK){
        if(stmt2){
            sqlite3_finalize(stmt2);
        }
        sqlite3_close(conn);
        return -1;
    }


    /*6.根据select语句的对象，获取结果集中的字段数量*/
    int fieldCount = sqlite3_column_count(stmt2);
    printf("The column count is %d.\n",fieldCount);


    /*7.遍历结果集中每一个字段meta信息，并获取其声明时的类型*/
    for(int i=0;i<fieldCount;++i){
        /*由于此时table中并不存在数据，再有就是SQLite中的数据类型本身是动态的，所以在
         * 没有数据时无法通过sqlie3_column_type函数获取，此时sqlite3_column_type只会
         * 返回SQLITE_NULL，直到有数据时才能返回具体的类型，因此这里使用了sqlite3_col
         * umn_decltype函数类获取表声明时给出的声明类型*/
        string stype = sqlite3_column_decltype(stmt2,i);
        stype = this->strlwr((char*)stype.c_str());
        /*下面的解析规则见该系列的“数据类型-->1.决定字段亲缘性的规则部分”*/
        if(stype.find("int") != string::npos){
            printf("The type of %dth column is INTERGER.\n",i);
        }else if(stype.find("char") != string::npos
                || stype.find("text") != string::npos){
            printf("The type of %dth column is TEXT.\n",i);
        }else if(stype.find("real") != string::npos
                || stype.find("floa") != string::npos
                || stype.find("doub") != string::npos){
            printf("The type of %dth column is DOUBLE.\n",i);
        }
    }

    sqlite3_finalize(stmt2);


    /*8.为了方便下一次测试运行，这里需要删除该函数创建的数据表，否则在下次
     * 运行时将无法创建该表，因为它已经存在*/
    const char *dropSQL = "drop table testtable";
    sqlite3_stmt *stmt3 = NULL;
    if(sqlite3_prepare_v2(conn,dropSQL,strlen(dropSQL),&stmt3,NULL) != SQLITE_OK){
        if(stmt3)
            sqlite3_finalize(stmt3);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt3) == SQLITE_DONE){
        cout<<"The test table has been dropped."<<endl;
    }
    sqlite3_finalize(stmt3);
    sqlite3_close(conn);
    return 0;
}

int NormalDB::query(void)
{
    sqlite3 * conn = NULL;

    /*1.open database*/
    int result = sqlite3_open("./disk/first.db",&conn);
    if(result != SQLITE_OK){
        sqlite3_close(conn);
        return -1;
    }

    const char *createTableSQL = 
        "create table testtable(int_col int,float_col real,string_col text)";
    sqlite3_stmt *stmt = NULL;
    int len = strlen(createTableSQL);


    /*2.准备创建数据表，如果创建失败，需要用sqlite3_finalize释放sqlite3_stmt对象，以防止内存泄漏*/
    if(sqlite3_prepare_v2(conn,createTableSQL,len,&stmt,NULL) != SQLITE_OK){
        if(stmt){
            sqlite3_finalize(stmt);
        }
        sqlite3_close(conn);
        return -1;
    }


    /*3.通过sqlite3_step命令执行创建表的语句，对于DDL和DML语句而言，sqlite3_step执行正确的返回值
     * 只有SQLITE_DNOE，对于SELECT查询而言，如果有数据返回SQLITE_ROW，当到达结果集末尾时则返回
     * SQLITE_DONE*/
    if(sqlite3_step(stmt) != SQLITE_DONE){
        sqlite3_finalize(stmt);
        sqlite3_close(conn);
        return -1;
    }


    /*4.释放创建表语句对象的资源*/
    cout<<"4. .."<<endl;
    sqlite3_finalize(stmt);
    cout<<"succeed to create test table now..."<<endl;


    /*5.为后面的查询操作插入测试数据*/
    cout<<"5. .."<<endl;
    sqlite3_stmt *stmt2 = NULL;
    const char *insertSQL = "insert into testtable values(20,21.0,'this is a test.')";
    if(sqlite3_prepare_v2(conn,insertSQL,strlen(insertSQL),&stmt2,NULL) != SQLITE_OK){
        if(stmt2)
            sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return -1;
    }
    if(sqlite3_step(stmt2) != SQLITE_DONE){
        sqlite3_finalize(stmt2);
        sqlite3_close(conn);
        return -1;
    }
    cout<<"success to insert test data."<<endl;
    sqlite3_finalize(stmt2);


    /*6.执行select语句查询数据*/
    cout<<"6. .."<<endl;
    //const char *selectSQL = "select * from testtable";
    //sqlite3_stmt *stmt3 = NULL;
    return 0;
}

/*strlwr --> for linux*/
char *NormalDB::strlwr(char *str)
{
    char *p = str;
    if(str == NULL) return NULL;

    while(*p != '\0'){
        if(*p >= 'A' && *p <= 'Z'){
            *p = *p + 0x20;
        }
        p++;
    }
    return str;
}



