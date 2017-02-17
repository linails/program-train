/*
 * Progarm Name: binditem-tetris.hpp
 * Created Time: 2017-02-17 14:14:15
 * Last modified: 2017-02-17 16:14:59
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
    BindItemTetris();
    ~BindItemTetris();
    int  add_item_group(vector<BindItem_t> &items);
    int  del_item_group(int gid);
    int  add_item(BindItem_t &item);
    int  del_item(int gid, string gw, int devid);
    int  report_status(string gw, int devid, int status);
    int  ctrl_status(int gid, int status);
    int  register_ctrl_cb(int (*ctrl)(void));
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
private:
    typedef int (*CtrlCB_t)(void);
    typedef unordered_map<device_t, size_t, DeviceHash, DeviceEqual> DevsMap_t;
    Tetris<int>                    *m_tetris;
    map<int, list<BindItem_t> >     m_binditems;
    DevsMap_t                       m_devsmap; /* <gw, devid> -> pos-id */
    map<int, list<int> >            m_binditems_map;
    CtrlCB_t                        m_ctrl_fun;
};

#endif //_BINDITEM_TETRIS_HPP_

