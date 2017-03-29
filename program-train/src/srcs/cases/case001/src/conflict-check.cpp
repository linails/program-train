/*
 * Progarm Name: conflict-check.cpp
 * Created Time: 2017-03-27 15:08:09
 * Last modified: 2017-03-29 18:37:56
 * @author: minphone.linails linails@foxmail.com 
 */

#include "conflict-check.hpp"
#include <iostream>
#include <sstream>
#include "dev-child-sibling-tree.hpp"
#include "dev-avl-tree.hpp"
#include <algorithm>
#include <stack>

using std::cout;
using std::endl;
using std::stringstream;
using std::make_pair;
using std::stack;
using std::pair;

ConflictCheck::ConflictCheck(vector<device_t> *devices_set, vector<scene_t> *orig_scenes)
    :m_pdevices_set(devices_set)
    ,m_porig_scenes(orig_scenes)
{
    if(0 != this->sets_init()){
        cout << "[Error] conflict-check init failed !" << endl;
    }

    if(0 != this->tree_init()){
        cout << "[Error] conflict-check init scene-tree failed !" << endl;
    }
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
    device_tsl_t  tsl;  this->convert(tsl, dev); return 0;
}

int  ConflictCheck::device_add(vector<device_t> &devs)  // only concern dev.id | dev.gateway
{
    for(auto &dev : devs){
        device_tsl_t  tsl;
        this->convert(tsl, dev);
    }

    return 0;
}

int  ConflictCheck::device_del(device_t &dev)           // only concern dev.id | dev.gateway
{
    int ret     = 0;
    int tsl_pos = -1;

    this->convert(tsl_pos, dev);

    if(-1 != tsl_pos){
        auto fi = this->m_dev_mgr.tsl_set.find(tsl_pos);
        if(fi != this->m_dev_mgr.tsl_set.end()){
            this->m_dev_mgr.tsl_set.erase(fi);

            auto f_dt = this->m_dev_mgr.dev2tsl.find(dev);
            if(f_dt != this->m_dev_mgr.dev2tsl.end()){
                this->m_dev_mgr.dev2tsl.erase(f_dt);
            }

            auto f_td = this->m_dev_mgr.tsl2dev.find(tsl_pos);
            if(f_td != this->m_dev_mgr.tsl2dev.end()){
                this->m_dev_mgr.tsl2dev.erase(f_td);
            }

            this->m_dev_mgr.tsl_set_del.push_back(tsl_pos);

        }else
            ret = -1;
    }else
        ret = -1;

    return ret;
}

int  ConflictCheck::device_del(vector<device_t> &devs)  // only concern dev.id | dev.gateway
{
    for(auto &dev : devs){ this->device_del(dev); } return 0;
}

int  ConflictCheck::convert(device_tsl_t &tsl, device_t &dev)     // DevMgr_t
{
    auto fi = this->m_dev_mgr.dev2tsl.find(dev);
    if(fi == this->m_dev_mgr.dev2tsl.end()){

        int tsl_pos = this->get_tsl_pos();

        this->m_dev_mgr.dev2tsl.insert(make_pair(dev, tsl_pos));
        this->m_dev_mgr.tsl2dev.insert(make_pair(tsl_pos, dev));


        /*
         * insert into tsl_set;
         * */
        tsl.id      = tsl_pos;
        tsl.status  = dev.status;

        this->m_dev_mgr.tsl_set.insert(make_pair(tsl_pos, tsl));

    }else{
        /* 
         * find tsl_pos and update status
         * */
        int tsl_pos = this->m_dev_mgr.dev2tsl[dev];

        tsl.id      = tsl_pos;

        this->m_dev_mgr.tsl2dev[tsl_pos].status = dev.status;
        this->m_dev_mgr.tsl_set[tsl_pos].status = dev.status;

        tsl.status  = this->m_dev_mgr.tsl_set[tsl_pos].status;
    }

    return 0;
}

int  ConflictCheck::convert(int &tsl_pos, device_t &dev)          // DevMgr_t
{
    auto fi = this->m_dev_mgr.dev2tsl.find(dev);
    if(fi == this->m_dev_mgr.dev2tsl.end()){

        tsl_pos = this->get_tsl_pos();

        this->m_dev_mgr.dev2tsl.insert(make_pair(dev, tsl_pos));
        this->m_dev_mgr.tsl2dev.insert(make_pair(tsl_pos, dev));


        /*
         * insert into tsl_set;
         * */
        device_tsl_t  tsl;
        tsl.id      = tsl_pos;
        tsl.status  = dev.status;

        this->m_dev_mgr.tsl_set.insert(make_pair(tsl_pos, tsl));
    }else{
        /* 
         * find tsl_pos and update status
         * */
        tsl_pos = this->m_dev_mgr.dev2tsl[dev];

        this->m_dev_mgr.tsl2dev[tsl_pos].status = dev.status;
        this->m_dev_mgr.tsl_set[tsl_pos].status = dev.status;
    }

    return 0;
}

int  ConflictCheck::convert(scene_tsl_t &tsl, scene_t &scene)     // SceneMgr_t
{
    tsl.id       = scene.id;
    tsl.time     = scene.time;
    tsl.timetype = scene.timetype;


    /* 
     * conditions
     * */
    {
        for(auto &dev : scene.condition_devs){
            device_tsl_t tsl_dev;
            this->convert(tsl_dev, dev);     // DevMgr_t

            tsl.conditions.push_back(tsl_dev);
        }

        for(auto &sid : scene.condition_scenes){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.scene2tsl[sid];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            tsl.conditions.push_back(tsl_dev);
        }

        for(auto &def : scene.condition_defense){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.def2tsl[def.id];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            stringstream  stream;
            stream << def.alarm;
            stream >> tsl_dev.status;

            tsl.conditions.push_back(tsl_dev);
        }
    }

    /* 
     * results
     * */
    {
        for(auto &dev : scene.result_devs){
            device_tsl_t tsl_dev;
            this->convert(tsl_dev, dev);     // DevMgr_t

            tsl.results.push_back(tsl_dev);
        }

        for(auto &sid : scene.result_scenes){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.scene2tsl[sid];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            tsl.results.push_back(tsl_dev);
        }

        for(auto &def : scene.result_defense){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.def2tsl[def.id];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            stringstream  stream;
            stream << def.alarm;
            stream >> tsl_dev.status;

            tsl.results.push_back(tsl_dev);
        }
    }

    /* 
     * recovers
     * */
    {
        for(auto &dev : scene.recover_devs){
            device_tsl_t tsl_dev;
            this->convert(tsl_dev, dev);     // DevMgr_t

            tsl.recovers.push_back(tsl_dev);
        }

        for(auto &sid : scene.recover_scenes){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.scene2tsl[sid];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            tsl.recovers.push_back(tsl_dev);
        }

        for(auto &def : scene.recover_defense){
            device_tsl_t tsl_dev;
            int tsl_pos = this->m_dev_mgr.def2tsl[def.id];
            tsl_dev     = this->m_dev_mgr.tsl_set[tsl_pos];

            stringstream  stream;
            stream << def.alarm;
            stream >> tsl_dev.status;

            tsl.recovers.push_back(tsl_dev);
        }
    }

    return 0;
}

int  ConflictCheck::create_scene_cs_tree(DevChildSiblingTree *cstree, scene_tsl_t &tsl)
{
    int ret = 0;

    /*
     * timetype : 1 timing;  2 delay
     * */
    if(2 != tsl.timetype){

        stack<pair<device_tsl_t *, int> > backspace;

        backspace.push(make_pair(nullptr, -1));


        /* 
         * unit oprt func
         * */
        auto unit = [&cstree, &backspace, this](device_tsl_t &tsl_dev, int time){

            int sibling = -1;

            /* 
             * tsl_dev is scene when tsl_dev.status = null
             * */
            if(true == tsl_dev.status.empty()){

                int scene_id = this->m_dev_mgr.tsl2scene[tsl_dev.id];
                scene_tsl_t &tsl = this->m_scene_mgr.scene_tsl[scene_id];

                int exe_time = tsl.time;
                if(2 == tsl.timetype) exe_time += time;

                int index = 0;
                for(auto &tsl_d : tsl.results){
                    if(0 == index){
                        cstree->insert_child(tsl_dev.id, tsl_d, exe_time);
                        index = 1;
                    }else{
                        cstree->insert_sibling(sibling, tsl_d, exe_time);
                    }
                    sibling = tsl_d.id;

                    backspace.push(make_pair(&tsl_d, exe_time));
                }
            }else{

                auto fi = this->m_scene_mgr.trig_set.find(tsl_dev.id);
                int sibling = -1;

                /* 
                 * tsl_dev -> tsl_scene
                 * */
                if(fi != this->m_scene_mgr.trig_set.end()){

                    int index = 0;
                    for(auto &sid : this->m_scene_mgr.trig_set[tsl_dev.id]){

                        int tsl_scene = this->m_dev_mgr.scene2tsl[sid];
                        device_tsl_t &tsl_d = this->m_dev_mgr.tsl_set[tsl_scene];

                        if(0 == index){
                            cstree->insert_child(tsl_dev.id, tsl_d, time);
                            index = 1;
                        }else{
                            cstree->insert_sibling(sibling, tsl_d, time);
                        }
                        sibling = tsl_d.id;

                        backspace.push(make_pair(&tsl_d, time));
                    }
                }
            }
        };


        int tsl_pos = this->m_dev_mgr.scene2tsl[tsl.id];
        device_tsl_t tsl_dev = this->m_dev_mgr.tsl_set[tsl_pos];

        pair<device_tsl_t *, int> tsl_time(make_pair(&tsl_dev, tsl.time));

        do{
            unit(*tsl_time.first, tsl_time.second);

            tsl_time = backspace.top();
            backspace.pop();

        }while(nullptr != tsl_time.first);

    }else
        ret = -1;

    return ret;
}

int  ConflictCheck::convert_cs2avl_tree(DevAVLTree *avltree, DevChildSiblingTree *cstree)
{
    auto set_val = [](device_tsl_t &tsl, int &time, int key, string status, int time_val){
        tsl.id      = key;
        tsl.status  = status;
        time        = time_val;
    };

    auto visit = [&avltree, &set_val](btNode *pos) -> int{

        int time = -1;
        device_tsl_t tsl;

        set_val(tsl, time, pos->m_key, pos->m_status, pos->m_time);

        avltree->insert(tsl, time);

        return 0;
    };

    cstree->pre_order(visit);

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
    /* 
     * init device_t -> dev2tsl
     * */
    if(nullptr != this->m_pdevices_set){
        for(auto &dev : *this->m_pdevices_set){
            device_tsl_t  tsl;  this->convert(tsl, dev);
        }
    }


    /* 
     * collecting gid
     * */
    {
        int max_gid = -1;

        if(nullptr != this->m_porig_scenes){
            for(auto &sce : *this->m_porig_scenes){

                for(auto &def : sce.condition_defense){
                    if(def.id > max_gid) max_gid = def.id;
                }

                for(auto &def : sce.result_defense){
                    if(def.id > max_gid) max_gid = def.id;
                }

                for(auto &def : sce.recover_defense){
                    if(def.id > max_gid) max_gid = def.id;
                }
            }
        }

        this->reset_gid(max_gid);
    }


    /* 
     * init scene_t -> scene2tsl
     * */
    if(nullptr != this->m_porig_scenes){
        for(auto &sce : *this->m_porig_scenes){

            auto fi = this->m_dev_mgr.scene2tsl.find(sce.id);
            if(fi == this->m_dev_mgr.scene2tsl.end()){


                /*
                 * init into m_dev_mgr
                 * */
                {
                    int tsl_pos = this->get_tsl_pos();

                    this->m_dev_mgr.scene2tsl.insert(make_pair(sce.id, tsl_pos));
                    this->m_dev_mgr.tsl2scene.insert(make_pair(tsl_pos, sce.id));


                    /*
                     * insert into tsl_set;
                     *
                     * Note : tsl.status is null
                     *
                     * */
                    device_tsl_t  tsl;
                    tsl.id      = tsl_pos;

                    this->m_dev_mgr.tsl_set.insert(make_pair(tsl_pos, tsl));
                }


                /* 
                 * init into m_scene_mgr
                 * */
                {
                    scene_tsl_t tsl;
                    this->convert(tsl, sce);     // SceneMgr_t

                    this->m_scene_mgr.scene_ori.insert(make_pair(sce.id, sce));
                    this->m_scene_mgr.scene_tsl.insert(make_pair(sce.id, tsl));

                    this->add_trig(tsl.conditions, tsl.id);
                }
            }
        }
    }

    return 0;
}

int  ConflictCheck::add_trig(int trig, int scene_id)
{
    vector<int> trigs;

    trigs.push_back(trig);

    this->add_trig(trigs, scene_id);

    return 0;
}

int  ConflictCheck::add_trig(vector<int> &trigs, int scene_id)
{
    for(auto &trig : trigs){
        auto f_trig = this->m_scene_mgr.trig_set.find(trig);
        if(f_trig != this->m_scene_mgr.trig_set.end()){

            auto f_sid = find(this->m_scene_mgr.trig_set[trig].begin(),
                              this->m_scene_mgr.trig_set[trig].end(),  scene_id);
            if(f_sid == this->m_scene_mgr.trig_set[trig].end()){
                this->m_scene_mgr.trig_set[trig].push_back(scene_id);
            }

        }else{

            list<int> sce_ids;
            sce_ids.push_back(scene_id);

            this->m_scene_mgr.trig_set.insert(make_pair(trig, sce_ids));
        }
    }

    return 0;
}

int  ConflictCheck::add_trig(list<device_tsl_t> trigs, int scene_id)
{
    for(auto &tsl : trigs){
        auto f_trig = this->m_scene_mgr.trig_set.find(tsl.id);
        if(f_trig != this->m_scene_mgr.trig_set.end()){

            auto f_sid = find(this->m_scene_mgr.trig_set[tsl.id].begin(),
                              this->m_scene_mgr.trig_set[tsl.id].end(),  scene_id);
            if(f_sid == this->m_scene_mgr.trig_set[tsl.id].end()){
                this->m_scene_mgr.trig_set[tsl.id].push_back(scene_id);
            }

        }else{

            list<int> sce_ids;
            sce_ids.push_back(scene_id);

            this->m_scene_mgr.trig_set.insert(make_pair(tsl.id, sce_ids));
        }
    }

    return 0;
}

int  ConflictCheck::del_trig(int trig, int scene_id)
{
    int ret = 0;

    auto fi = this->m_scene_mgr.trig_set.find(trig);
    if(fi != this->m_scene_mgr.trig_set.end()){
        auto f_sid = find(this->m_scene_mgr.trig_set[trig].begin(), 
                          this->m_scene_mgr.trig_set[trig].end(), scene_id);
        if(f_sid != this->m_scene_mgr.trig_set[trig].end()){
            this->m_scene_mgr.trig_set[trig].erase(f_sid);

            if(true == this->m_scene_mgr.trig_set[trig].empty()){
                this->m_scene_mgr.trig_set.erase(fi);
            }
        }else{
            ret = -1;
        }
    }else{
        ret = -1;
    }

    return ret;
}

int  ConflictCheck::del_trig(vector<int> trigs, int scene_id)
{
    for(auto &trig : trigs){ this->del_trig(trig, scene_id); } return 0;
}

int  ConflictCheck::del_scene(int scene_id)
{
    this->m_scene_mgr.scene_del.push_back(scene_id);

    auto fi_tsl = this->m_scene_mgr.scene_tsl.find(scene_id);
    if(fi_tsl != this->m_scene_mgr.scene_tsl.end()){

        for(auto &tsl_dev : fi_tsl->second.conditions){
            this->del_trig(tsl_dev.id, scene_id);
        }

        this->m_scene_mgr.scene_tsl.erase(fi_tsl);
    }

    auto fi_ori = this->m_scene_mgr.scene_ori.find(scene_id);
    if(fi_ori != this->m_scene_mgr.scene_ori.end()){
        this->m_scene_mgr.scene_ori.erase(fi_ori);
    }

    /* 
     * delete avl-tree
     * */
    {
        auto fi_cs = this->m_avl_mgr.scene_cs_tree.find(scene_id);
        if(fi_cs != this->m_avl_mgr.scene_cs_tree.end()){
            this->m_avl_mgr.scene_cs_tree.erase(fi_cs);
        }

        auto fi_avl = this->m_avl_mgr.scene_avl_tree.find(scene_id);
        if(fi_avl != this->m_avl_mgr.scene_avl_tree.end()){
            this->m_avl_mgr.scene_avl_tree.erase(fi_avl);
        }
    }

    return 0;
}

int  ConflictCheck::tree_init(void)
{
    int ret = 0;

    for(auto &u : this->m_scene_mgr.scene_tsl){
        scene_tsl_t &tsl_scene = u.second;
        if(1 == tsl_scene.timetype){

            /* 
             * init DevChildSiblingTree
             * */
            DevChildSiblingTree *cstree = new DevChildSiblingTree();
            if(nullptr != cstree){
                this->create_scene_cs_tree(cstree, tsl_scene);

                this->m_avl_mgr.scene_cs_tree.insert(make_pair(tsl_scene.id, cstree));

                /* 
                 * init avl
                 * */
                DevAVLTree *avltree = new DevAVLTree();
                if(nullptr != avltree){
                    this->convert_cs2avl_tree(avltree, cstree);

                    this->m_avl_mgr.scene_avl_tree.insert(make_pair(tsl_scene.id, avltree));
                }else{
                    cout << "[Error] new DevAVLTree() failed !" << endl;
                    ret = -1;
                }
            }else{
                cout << "[Error] new DevChildSiblingTree() failed !" << endl;
                ret = -1;
            }
        }
    }

    return ret;
}

