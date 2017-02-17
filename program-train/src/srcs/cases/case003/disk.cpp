/*
 * Progarm Name: disk.cpp
 * Created Time: 2017-01-16 11:12:58
 * Last modified: 2017-02-16 16:39:06
 * @author: minphone.linails linails@foxmail.com 
 */

#include "disk.hpp"
#include <iostream>
#include <sstream>
#include "kb-common.hpp"

using std::cout;
using std::endl;
using std::cerr;

Disk::Disk()
{
    try{
        string dbstr = "dbname=exampledb user=dbuser password=123456 hostaddr=127.0.0.1 port=5432";

        this->m_pqxx = new pqxx::connection(dbstr);
        if(NULL == this->m_pqxx){
            cout << "[Error] : new pqxx failed !" << endl;
        }else{
            cout << "connection successed !" << endl;

            /*
             * bind_devices
             * */
            this->m_pqxx->prepare("insert-bind-items", "insert into bind_devices(id,name,devid,gateway,status) values($1,$2,$3,$4,$5)");
            this->m_pqxx->prepare("select-bind-items-by-id", "select name,devid,gateway,status from bind_devices where id=$1");
            this->m_pqxx->prepare("select-bind-items-by-name", "select id,devid,gateway,status from bind_devices where name=$1");
            this->m_pqxx->prepare("select-bind-items-by-gw", "select name,id,devid,status from bind_devices where gateway=$1");
            this->m_pqxx->prepare("delete-bind-items-by-id", "delete from bind_devices where id=$1");
            this->m_pqxx->prepare("update-bind-items-by-id","update bind_devices set status=$1 where id=$2");
            this->m_pqxx->prepare("select-bind-items-maxid", "select id from bind_devices where id=(select max(id) from bind_devices)");


            /* 
             * 这么写仅供测试使用
             * */
            if(0 != this->create_table()){
                cout << "[Error] : disk.create-table failed !" << endl;
            }else{
                cout << "disk.create-table successed !" << endl;
            }

        }
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        exit(1);
    }
}

Disk::~Disk()
{
    if(NULL != this->m_pqxx){
        this->m_pqxx->disconnect();
    }
}

int  Disk::create_table(void)
{
    int ret = 0;

    string sql = "create table bind_devices("
                 "id int not null,"             // 绑定组 ID
                 "name text not null,"          // 绑定组名
                 "devid int not null,"          // 设备ID
                 "gateway text not null,"       // 网关ID
                 "status int not null"          // 开关状态
                 ")";

    try{
        pqxx::work w(*this->m_pqxx);

        w.exec(sql.c_str());

        w.commit();
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    return ret;
}

int  Disk::insert_bind_items(void)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);
    for(int i=0; i<10; i++){
        try{
            int    id   = 1;
            string name = "key-bind";
            int devid   = 0x0102;
            string gw   = "gateway 1...";
            int status  = 0;

            w.prepared("insert-bind-items")(id)(name)(devid)(gw)(status).exec();

        }catch (const std::exception &e){
            cerr << e.what() << endl;
            ret = -1;
        }
    }
    w.commit();

    return ret;
}

int  Disk::select_bind_items(vector<BindItem_t> &v_item, int id)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        pqxx::result r = w.prepared("select-bind-items-by-id")(id).exec();
        if(0 < r.size()){
            for(auto row = r.begin(); row != r.end(); row++){
                BindItem_t item;
                item.id     = id;
                item.name   = row[0].as<string>();
                item.devid  = row[1].as<int>();
                item.gateway= row[2].as<string>();
                item.status = row[3].as<int>();

                v_item.push_back(item);
            }
        }else{
            cout << "no bind-items where id = " << id << endl;
        }

    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

int  Disk::select_bind_items(vector<BindItem_t> &v_item, string &name)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        pqxx::result r = w.prepared("select-bind-items-by-name")(name).exec();
        if(0 < r.size()){
            for(auto row = r.begin(); row != r.end(); row++){
                BindItem_t item;
                item.name   = name;
                item.id     = row[0].as<int>();
                item.devid  = row[1].as<int>();
                item.gateway= row[2].as<string>();
                item.status = row[3].as<int>();

                v_item.push_back(item);
            }
        }else{
            cout << "no bind-items where name = " << name << endl;
        }

    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

int  Disk::select_bind_items(vector<BindItem_t> &v_item, string &gw, int)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        pqxx::result r = w.prepared("select-bind-items-by-gw")(gw).exec();
        if(0 < r.size()){
            for(auto row = r.begin(); row != r.end(); row++){
                BindItem_t item;
                item.name   = row[0].as<string>();
                item.id     = row[1].as<int>();
                item.devid  = row[2].as<int>();
                item.gateway= gw;
                item.status = row[3].as<int>();

                v_item.push_back(item);
            }
        }else{
            cout << "no bind-items where gw = " << gw << endl;
        }

    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

int  Disk::select_bind_items(int &maxid)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        pqxx::result r = w.prepared("select-bind-items-maxid").exec();
        if(0 < r.size()){
            maxid = r[0][0].as<int>();
        }else{
            cout << "[Error] : no items where max(id)" << endl;
        }

    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

int  Disk::delete_bind_items(int id)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        w.prepared("delete-bind-items-by-id")(id).exec();
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

int  Disk::update_bind_items(int id, int status)
{
    int ret = 0;

    pqxx::work w(*this->m_pqxx);

    try{
        pqxx::result r = w.prepared("select-bind-items-by-id")(id).exec();
        if(0 < r.size()){
            w.prepared("update-bind-items-by-id")(status)(id).exec();
        }else{
            cout << "[Error] : bind-items id = " << id << " is null" << endl;
            ret = -1;
        }
    }catch (const std::exception &e){
        cerr << e.what() << endl;
        ret = -1;
    }

    w.commit();

    return ret;
}

