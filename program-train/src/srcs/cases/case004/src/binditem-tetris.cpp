/*
 * Progarm Name: binditem-tetris.cpp
 * Created Time: 2017-02-22 15:07:10
 * Last modified: 2017-02-22 17:48:52
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
                    if((item.devid == bi.devid) && (item.gateway == bi.gateway)){
                        /* exist */
                        return 1;
                    }else{
                        return 0;
                    }
                };

                auto iter = find_if(this->m_binditems[item.id].begin(),
                                    this->m_binditems[item.id].begin(),
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

        if(nullptr == this->m_tetris){
            this->m_tetris = new Tetris<int>(tetris_data);
            if(nullptr == this->m_tetris){
                cout << "[Error] this->m_tetris new failed !" << endl;
            }
        }

    /* 
     * add ...
     * */
    }else{
        addin_binditems();

        this->map_dev(items);

        vector<int> gids; for(auto &item : items) gids.push_back(item.id);
        sort(gids.begin(), gids.end());
        auto iter = unique(gids.begin(), gids.end());
        gids.resize(std::distance(gids.begin(), iter));

        for(auto gid : gids){
            vector<int> map_ids; for(auto id : this->m_binditems_map[gid]) map_ids.push_back(id);
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
    return 0;
}

int  BindItemTetris::add_item(BindItem_t &item)
{
    return 0;
}

int  BindItemTetris::del_item(int gid, string gw, int devid)
{
    return 0;
}

int  BindItemTetris::push_report_status(string gw, int devid, int status)
{
    return 0;
}

int  BindItemTetris::push_ctrl_status(int gid, int status)
{
    return 0;
}

int  BindItemTetris::register_ctrl_trigger(std::function<int (int, int)> ctrl_trigger) /* (gid, ctrl-status) */
{
    return 0;
}

/*
 * generate all map-dev 
 * */
int  BindItemTetris::map_dev(void)
{
    return 0;
}

/* 
 * generate items -> vector<map-dev> 
 * */
int  BindItemTetris::map_dev(vector<BindItem_t> &items)
{
    return 0;
}

/*
 * generate map-id or get map-id 
 * */
int  BindItemTetris::map_dev(size_t &map_id, string gw, int devid)
{
    return 0;
}



