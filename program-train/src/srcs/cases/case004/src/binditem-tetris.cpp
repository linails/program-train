/*
 * Progarm Name: binditem-tetris.cpp
 * Created Time: 2017-02-22 15:07:10
 * Last modified: 2017-02-24 10:43:24
 * @author: minphone.linails linails@foxmail.com 
 */

#include "binditem-tetris.hpp"
#include <iostream>

using std::cout;
using std::endl;

BindItemTetris::BindItemTetris(std::function<int (int, int)> ctrl_trigger)
{
    if(nullptr != ctrl_trigger){
        this->m_ctrl_trigger = ctrl_trigger;
    }else{
        cout << "ctrl_trigger is nullptr " << endl;
    }
}

BindItemTetris::~BindItemTetris()
{
    if(nullptr != this->m_tetris){
        delete this->m_tetris;
        this->m_tetris = nullptr;
    }
}

int  BindItemTetris::add_item_group(vector<BindItem_t> &items)
{
    auto addin_binditems = [this, &items](){

        for(auto &item : items){

            auto find_gid = this->m_binditems.find(item.id);
            if(find_gid != this->m_binditems.end()){
                cout << "Line : " << __LINE__ << " - find it gid = " << item.id << endl;

                auto isexist = [&item](BindItem_t bi){
                    if((bi.gateway == item.gateway) && (bi.devid == item.devid)){
                        /* exist */
                        return 1;
                    }else{
                        return 0;
                    }
                };

                auto iter = find_if(this->m_binditems[item.id].begin(),
                                    this->m_binditems[item.id].end(),
                                    isexist);
                if(iter == this->m_binditems[item.id].end()){
                    this->m_binditems[item.id].push_back(item);
                }

            }else{
                list<BindItem_t>    bi_list;
                bi_list.push_back(item);

                this->m_binditems[item.id] = bi_list;
            }
        }
    };

    /* 
     * For first init
     * */
    if(true == this->m_binditems.empty()){
        addin_binditems();

        /* generate all map-dev */
        this->map_dev();

        map<int, vector<int> > tetris_data;
        for(auto &u : this->m_binditems_map){

            vector<int> map_ids; for(auto id : u.second) map_ids.push_back(id);
            
            tetris_data.insert(make_pair(u.first, map_ids));
        }

        /* init Tetris<int> */
        if(nullptr == this->m_tetris){
            this->m_tetris = new Tetris<int>(tetris_data);
            if(nullptr == this->m_tetris){
                cout << "[Error] this->m_tetris new failed !" << endl;
            }else{
                if(nullptr != this->m_ctrl_trigger){
                    this->m_tetris->register_trigger_cb(this->m_ctrl_trigger);
                }
            }
        }else{

            vector<int> gids; for(auto &item : items) gids.push_back(item.id); 
            sort(gids.begin(), gids.end());
            auto iter = unique(gids.begin(), gids.end());
            gids.resize(std::distance(gids.begin(), iter));

            /* update Tetris<int> */
            for(auto gid : gids){
                vector<int> map_ids; for(auto id : this->m_binditems_map[gid]) map_ids.push_back(id);

                cout << "map_ids.size() : " << map_ids.size() << endl;

                pair<int, vector<int> > tetris_data(gid, map_ids);
                if(nullptr != this->m_tetris){
                    this->m_tetris->add_tid(tetris_data);
                }
            }
        }

    /* 
     * add oprt ...
     * */
    }else{
        addin_binditems();

        this->map_dev(items);

        vector<int> gids; for(auto &item : items) gids.push_back(item.id); 
        sort(gids.begin(), gids.end());
        auto iter = unique(gids.begin(), gids.end());
        gids.resize(std::distance(gids.begin(), iter));

        /* update Tetris<int> */
        for(auto gid : gids){
            vector<int> map_ids; for(auto id : this->m_binditems_map[gid]) map_ids.push_back(id);

            cout << "map_ids.size() : " << map_ids.size() << endl;

            pair<int, vector<int> > tetris_data(gid, map_ids);
            if(nullptr != this->m_tetris){
                this->m_tetris->add_tid(tetris_data);
            }
        }
    }

    return 0;
}

int  BindItemTetris::del_item_group(int gid)
{
    {
        auto iter = this->m_binditems.find(gid);
        if(iter != this->m_binditems.end()){
            this->m_binditems.erase(iter);
        }
    }
    {
        auto iter = this->m_binditems_map.find(gid);
        if(iter != this->m_binditems_map.end()){
            this->m_binditems_map.erase(iter);
        }
    }

    if(nullptr != this->m_tetris) this->m_tetris->del_tid(gid);

    return 0;
}

int  BindItemTetris::add_item(BindItem_t &item)
{
    auto find_gid = this->m_binditems.find(item.id);
    if(find_gid != this->m_binditems.end()){
        cout << "Line : " << __LINE__ << " - find it gid = " << item.id << endl;

        auto isexist = [&item](BindItem_t bi){
            if((item.devid == bi.devid) && (item.gateway == bi.gateway)){
                /* exist */
                return 1;
            }else{
                return 0;
            }
        };

        auto iter = find_if(this->m_binditems[item.id].begin(),
                            this->m_binditems[item.id].end(),
                            isexist);
        if(iter == this->m_binditems[item.id].end()){
            this->m_binditems[item.id].push_back(item);

            /* updating */
            int map_id;
            this->map_dev(map_id, item.gateway, item.devid, item.id); // addin binditems_map

            if(nullptr != this->m_tetris){
                vector<int> map_ids; for(auto id : this->m_binditems_map[item.id]) map_ids.push_back(id);
                pair<int, vector<int> > tetris_data(item.id, map_ids);
                this->m_tetris->update_tid(tetris_data);
            }
        }

    }else{
        list<BindItem_t>    bi_list;
        bi_list.push_back(item);

        this->m_binditems[item.id] = bi_list;

        /* new tid For Tetris */
        int map_id;
        this->map_dev(map_id, item.gateway, item.devid, -1);

        list<int> map_ids;
        map_ids.push_back(map_id);
        this->m_binditems_map[item.id] = map_ids;

        /* update Tetris<int> */
        if(nullptr != this->m_tetris){
            vector<int> map_ids; for(auto id : this->m_binditems_map[item.id]) map_ids.push_back(id);
            pair<int, vector<int> > tetris_data(item.id, map_ids);
            this->m_tetris->add_tid(tetris_data);
        }
    }

    return 0;
}

int  BindItemTetris::del_item(int gid, string gw, int devid)
{
    int map_id;
    this->map_dev(map_id, gw, devid, -1); /* get map_id */

    auto iter = find(this->m_binditems_map[gid].begin(),
                     this->m_binditems_map[gid].end(),
                     map_id);
    if(iter != this->m_binditems_map[gid].end()){
        this->m_binditems_map[gid].erase(iter);
    }

    /* updating */
    if(nullptr != this->m_tetris){
        vector<int> map_ids; for(auto id : this->m_binditems_map[gid]) map_ids.push_back(id);
        pair<int, vector<int> > tetris_data(gid, map_ids);
        this->m_tetris->update_tid(tetris_data);
    }

    return 0;
}

int  BindItemTetris::push_report_status(string gw, int devid, int status)
{
    if(nullptr != this->m_tetris){
        int map_id;
        this->map_dev(map_id, gw, devid, -1);
        this->m_tetris->push_left(map_id, status);
    }
    return 0;
}

int  BindItemTetris::push_ctrl_status(int gid, int status)
{
    if(nullptr != this->m_tetris){
        this->m_tetris->push_right(gid, status);
    }
    return 0;
}

int  BindItemTetris::register_ctrl_trigger(std::function<int (int, int)> ctrl_trigger) /* (gid, ctrl-status) */
{
    this->m_ctrl_trigger = ctrl_trigger;
    if(nullptr != this->m_tetris){
        this->m_tetris->register_trigger_cb(this->m_ctrl_trigger);
    }
    return 0;
}

/*
 * generate all map-dev and addin this->m_binditems_map
 * */
int  BindItemTetris::map_dev(void)
{
    for(auto &u : this->m_binditems){
        list<int> map_ids;

        for(auto &item : u.second){
            int map_id;
            this->map_dev(map_id, item.gateway, item.devid, -1); /* generate map_id only */
            map_ids.push_back(map_id);
        }

        this->m_binditems_map[u.first] = map_ids;
    }
    return 0;
}

/* 
 * generate items -> vector<map-dev> 
 * */
int  BindItemTetris::map_dev(vector<BindItem_t> &items)
{
    for(auto &item : items){
        int map_id;
        this->map_dev(map_id, item.gateway, item.devid, -1);

        auto iter = this->m_binditems_map.find(item.id);
        if(iter != this->m_binditems_map.end()){
            auto isexist = find(this->m_binditems_map[item.id].begin(),
                                this->m_binditems_map[item.id].end(),
                                map_id);
            if(isexist == this->m_binditems_map[item.id].end()){
                this->m_binditems_map[item.id].push_back(map_id);
            }
        }else{
            list<int> map_ids;
            map_ids.push_back(map_id);
            this->m_binditems_map[item.id] = map_ids;
        }
    }
    return 0;
}

/*
 * generate map-id or get map-id
 * */
int  BindItemTetris::map_dev(int &map_id, string gw, int devid, int gid)
{
    device_t device;
    device.gateway  = gw;
    device.id       = devid;

    auto iter = this->m_devsmap.find(device);
    if(iter != this->m_devsmap.end()){
        map_id = this->m_devsmap[device];
    }else{
        map_id = this->m_devsmap.size() + 1;
        this->m_devsmap[device] = map_id;

        /* 
         * generate map_id and addin binditems_map | or get map_id
         * */
        if(-1 != gid){
            this->m_binditems_map[gid].push_back(map_id);

        }else{
            /* 
             * generate only | or get map_id
             * */
        }
    }
    return 0;
}

void BindItemTetris::print_info(int gid, unsigned line)
{
    if(nullptr != this->m_tetris){
        this->m_tetris->print_info(gid, line);
    }
}


