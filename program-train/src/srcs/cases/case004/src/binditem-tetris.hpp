/*
 * Progarm Name: binditem-tetris.hpp
 * Created Time: 2017-02-17 14:14:15
 * Last modified: 2017-02-22 16:59:56
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _BINDITEM_TETRIS_HPP_
#define _BINDITEM_TETRIS_HPP_

#include "common.hpp"
#include "queue-tetris-def.hpp"
#include <unordered_map>

using std::unordered_map;
using std::hash;

class BindItemTetris{
public:
    BindItemTetris(std::function<int (int, int)> ctrl_trigger = nullptr);
    ~BindItemTetris();
    int  add_item_group(vector<BindItem_t> &items);
    int  del_item_group(int gid);
    int  add_item(BindItem_t &item);
    int  del_item(int gid, string gw, int devid);
    int  push_report_status(string gw, int devid, int status);
    int  push_ctrl_status(int gid, int status);
    int  register_ctrl_trigger(std::function<int (int, int)> ctrl_trigger); /* (gid, ctrl-status) */
private:
    struct DeviceHash{
        size_t operator()(const device_t &device) const {
            size_t ret = hash<int>()(device.id) ^ hash<string>()(device.gateway) ^ hash<string>()(device.status);
            return ret;
        }
    };
    struct DeviceEqual{
        bool operator()(const device_t &ld, const device_t &rd) const {
            return ld.gateway == rd.gateway && ld.id == rd.id;
        }
    };
    int  map_dev(void);                                 /* generate all map-dev */
    int  map_dev(vector<BindItem_t> &items);            /* generate items -> vector<map-dev> */
    int  map_dev(size_t &map_id, string gw, int devid); /* generate map-id or get map-id */
private:
    typedef unordered_map<device_t, size_t, DeviceHash, DeviceEqual> DevsMap_t;
    Tetris<int>                    *m_tetris = nullptr;
    map<int, list<BindItem_t> >     m_binditems;        /* gid - list<BindItem_t> */
    DevsMap_t                       m_devsmap;          /* <gw, devid> -> pos-id */
    map<int, list<int> >            m_binditems_map;    /* gid - list<pos-id> */
    std::function<int (int, int)>   m_ctrl_trigger = nullptr;
};

#endif //_BINDITEM_TETRIS_HPP_

