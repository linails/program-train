/*
 * Progarm Name: key-bind-main.cpp
 * Created Time: 2017-01-13 17:05:35
 * Last modified: 2017-01-17 16:39:02
 * @author: minphone.linails linails@foxmail.com 
 */

#include "key-bind-main.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include "kb-common.hpp"
#include <cstdio>

using std::cout;
using std::endl;
using std::string;

KeyBind::KeyBind()
{
}

KeyBind::~KeyBind()
{
}

int  KeyBind::keybind_main(int argc, char **argv)
{
    int ret = 0;

    cout << "key-bind-main ... " << endl;

    ret = this->disk_init(); assert(-1 != ret);


    auto db_print = [this](void){
        /*
         * */
        vector<BindItem_t> vitems;

        this->m_disk->select_bind_items(vitems, 1);

        cout << "vitems.size() : " << vitems.size() << endl; {
            cout << "id     : " << vitems[0].id << endl;
            cout << "name   : " << vitems[0].name << endl;
            cout << "devid  : " << vitems[0].devid << endl;
            cout << "gw     : " << vitems[0].gateway << endl;
            cout << "status : " << vitems[0].status << endl;
        }
    };

    auto select_by_gw = [this](string gw){
        vector<BindItem_t> vitems;

        this->m_disk->select_bind_items(vitems, gw, 0);

        cout << "select_by_gw size : " << vitems.size() << endl;
    };

    db_print();

    ret = this->m_disk->update_bind_items(1, 1); assert(-1 != ret);

    db_print();

    ret = this->m_disk->update_bind_items(1, 0); assert(-1 != ret);

    int maxid = 0;
    ret = this->m_disk->select_bind_items(maxid);
    cout << "maxid : " << maxid << endl;

    select_by_gw("gateway ...");
    select_by_gw("gateway 1...");

    return ret;
}

int  KeyBind::disk_init(void)
{
    int ret = 0;

    this->m_disk = new Disk;
    if(NULL != this->m_disk){
        cout << "disk init successed !" << endl;

        /* 
         * insert bind-items For Test !
         * */
        //this->m_disk->insert_bind_items();
    }else{
        cout << "[Error] : disk init failed !" << endl;
    }

    return ret;
}

