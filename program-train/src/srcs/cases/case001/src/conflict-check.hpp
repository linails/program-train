/*
 * Progarm Name: conflict-check.hpp
 * Created Time: 2017-03-22 10:15:01
 * Last modified: 2017-03-27 18:54:00
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CONFLICT_CHECK_HPP_
#define _CONFLICT_CHECK_HPP_

#include <vector>
#include "common.hpp"
#include <tuple>
#include <unordered_map>
#include <string>
#include <list>
#include <map>
#include "dev-avl-tree.hpp"
#include "dev-child-sibling-tree.hpp"
#include "conflict-common.hpp"

using std::vector;
using std::tuple;
using std::unordered_map;
using std::string;
using std::list;
using std::hash;
using std::map;

class DevChildSiblingTree;
class DevAVLTree;

/* 
 * scene_t -> scene_tsl_t
 * */
typedef struct{
    int                     id;
    int                     time;
    int                     timetype; /* 1 timing;  2 delay */
    list<device_tsl_t>      conditions;
    list<device_tsl_t>      results;
    list<device_tsl_t>      recovers;
}scene_tsl_t;

//----------------------------------------------------------

class ConflictCheck{
public:
    ConflictCheck(vector<device_t> *devices_set = nullptr, vector<scene_t> *orig_scenes = nullptr);
    ~ConflictCheck();
    /* 
     * ConflictCheck.check
     * ret
     *  success : sid(>0) | conflict
     *  failed  :     -1 
     * */
    int  check(scene_t &scene);
    int  reset_gid(int max_gid = -1);
    int  device_add(device_t &dev);         // only concern dev.id | dev.gateway
    int  device_add(vector<device_t> &devs);// only concern dev.id | dev.gateway
    int  device_del(device_t &dev);         // only concern dev.id | dev.gateway
    int  device_del(vector<device_t> &devs);// only concern dev.id | dev.gateway
private:
    int  sets_init(void);
    int  get_tsl_pos(void);
private:
    int  convert(device_tsl_t &tsl, device_t &dev);     // DevMgr_t
    int  convert(int &tsl_pos, device_t &dev);          // DevMgr_t
    int  convert(scene_tsl_t &tsl, scene_t &scene);     // SceneMgr_t
    int  create_scene_cs_tree(DevChildSiblingTree *cstree, scene_tsl_t &tsl);
    int  convert_cs2avl_tree(DevAVLTree *avltree, DevChildSiblingTree *cstree);
private:
    typedef struct {
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
        int                     maxpos = 0;
        map<int, device_tsl_t>  tsl_set;
        list<int>               tsl_set_del;    // save deleted device_tsl_t | pos(int)
        map<int, int>           def2tsl;        // map< defense_t.id, tsl_pos >
        map<int, int>           tsl2def;        // map< tsl_pos, defense_t.id >
        map<int, int>           scene2tsl;      // map< scene_t.id, tsl_pos >
        map<int, int>           tsl2scene;      // map< tsl_pos, scene_t.id >
        map<int, device_t>                                      tsl2dev;
        unordered_map<device_t, int, DeviceHash, DeviceEqual>   dev2tsl;
    }DevMgr_t;
    typedef struct {
        map<int, int>           trig_set;       // map< tsl_pos(dev), scene_t.id >
        map<int, scene_t>       scene_ori;
        map<int, scene_tsl_t>   scene_tsl;
        list<int>               scene_del;      // save deleted scene_t.id | scene_t.id(int)
    }SceneMgr_t;
    typedef struct {
        map<int, DevChildSiblingTree*>  scene_cs_tree;      // map< root, child-sibling-tree > | root = scene_t.id
        map<int, DevAVLTree*>           scene_avl_tree;     // map< root, dev-avl-tree > | root = scene_t.id
    }avlTreeMgr_t;
private:
    vector<device_t>       *m_pdevices_set = nullptr;
    vector<scene_t>        *m_porig_scenes = nullptr;
    DevMgr_t                m_dev_mgr;
    SceneMgr_t              m_scene_mgr;
    avlTreeMgr_t            m_avl_mgr;
};

#endif //_CONFLICT_CHECK_HPP_

