/*
 * Progarm Name: conflict-check.cpp
 * Created Time: 2017-03-27 15:08:09
 * Last modified: 2017-03-27 18:54:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "conflict-check.hpp"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;
using std::make_pair;

ConflictCheck::ConflictCheck(vector<device_t> *devices_set, vector<scene_t> *orig_scenes)
    :m_pdevices_set(devices_set)
    ,m_porig_scenes(orig_scenes)
{
}

ConflictCheck::~ConflictCheck()
{
    if(false == this->m_avl_mgr.scene_cs_tree.empty()){
        for(auto &u : this->m_avl_mgr.scene_cs_tree){
            if(nullptr != u.second) delete u.second;
        }
    }

    if(false == this->m_avl_mgr.scene_avl_tree.empty()){
        for(auto &u : this->m_avl_mgr.scene_avl_tree){
            if(nullptr != u.second) delete u.second;
        }
    }
}

/* 
 * ConflictCheck.check
 * ret
 *  success : sid(>0) | conflict
 *  failed  :     -1 
 * */
int  ConflictCheck::check(scene_t &scene)
{
    return 0;
}

int  ConflictCheck::reset_gid(int max_gid)
{
    if(max_gid > (int)this->m_dev_mgr.def2tsl.size()){
        int remain = max_gid - this->m_dev_mgr.def2tsl.size();
        for(int i=0; i<remain; i++){
            int defid   = this->m_dev_mgr.def2tsl.size() + 1;
            int tsl_pos = this->get_tsl_pos();

            this->m_dev_mgr.def2tsl.insert(make_pair(defid, tsl_pos));
            this->m_dev_mgr.tsl2def.insert(make_pair(tsl_pos, defid));

            /*
             * insert into tsl_set;
             * */
            device_tsl_t  tsl;
            stringstream  stream;

            tsl.id = tsl_pos;
            stream << 0;
            stream >> tsl.status;

            this->m_dev_mgr.tsl_set.insert(make_pair(tsl_pos, tsl));
        }
    }

    return 0;
}

int  ConflictCheck::device_add(device_t &dev)           // only concern dev.id | dev.gateway
{
    return 0;
}

int  ConflictCheck::device_add(vector<device_t> &devs)  // only concern dev.id | dev.gateway
{
    return 0;
}

int  ConflictCheck::device_del(device_t &dev)           // only concern dev.id | dev.gateway
{
    return 0;
}

int  ConflictCheck::device_del(vector<device_t> &devs)  // only concern dev.id | dev.gateway
{
    return 0;
}

int  ConflictCheck::convert(device_tsl_t &tsl, device_t &dev)     // DevMgr_t
{
    return 0;
}

int  ConflictCheck::convert(int &tsl_pos, device_t &dev)          // DevMgr_t
{
    return 0;
}

int  ConflictCheck::convert(scene_tsl_t &tsl, scene_t &scene)     // SceneMgr_t
{
    return 0;
}

int  ConflictCheck::create_scene_cs_tree(DevChildSiblingTree *cstree, scene_tsl_t &tsl)
{
    return 0;
}

int  ConflictCheck::convert_cs2avl_tree(DevAVLTree *avltree, DevChildSiblingTree *cstree)
{
    return 0;
}

int  ConflictCheck::get_tsl_pos(void)
{
    int tsl_pos = -1;
    if(false == this->m_dev_mgr.tsl_set_del.empty()){
        auto iter = this->m_dev_mgr.tsl_set_del.begin();
        tsl_pos   = *iter;

        this->m_dev_mgr.tsl_set_del.erase(iter);
    }else{
        tsl_pos   = ++this->m_dev_mgr.maxpos;
    }

    return tsl_pos;
}

int  ConflictCheck::sets_init(void)
{
    return 0;
}

