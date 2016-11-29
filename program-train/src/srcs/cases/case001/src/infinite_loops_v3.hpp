/*
 * Progarm Name: infinite_loops_v3.hpp
 * Created Time: 2016-11-09 15:05:54
 * Last modified: 2016-11-29 14:09:06
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _INFINITE_LOOPS_V3_HPP_
#define _INFINITE_LOOPS_V3_HPP_

#include <vector>
#include "common.h"
#include <tuple>
#include <unordered_map>
#include <string>
#include <list>
#include "infinite_loops_v2.h"

using std::vector;
using std::tuple;
using std::unordered_map;
using std::string;
using std::list;
using std::hash;

/* scene1 / scene2 / ... 
 *
 * example :
 * {
 *   vector<device_t> vdev;
 *   vector<scene_t> vscene;
 *
 *   SceneSetv3  ss(vdev, vscene);
 *
 *   //[-1, 0, 1]
 *   // -1 : normal
 *   //  0 : infinite loop
 *   //  1 : timing error
 *
 *   int ret = ss.infinite_loops_check(scene);    // aim 
 *
 *   if(0 == ret){
 *       cout << "infinite loop ? : YES" << endl;
 *   }else if(1 == ret){
 *       cout << "timing error !" << endl;
 *   }else{
 *       cout << "infinite loop ? : NO" << endl;
 *   }
 * }
 * */
class SceneSetv3{
public:
    SceneSetv3(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);
    ~SceneSetv3();
    int  reinit(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);

    int  infinite_loops_check(scene_t &r_scene);    /* aim */

    int  del_scene(int sceneid);

    /*
     *      server
     *        ↓↓ : filter(sceneid)
     *      client
     * */
    int  filter(scene_t &r_exe_scene);

public:
    void print_all_set(void);
private:
    SceneSetv3(const SceneSetv3&) = delete;
    SceneSetv3 &operator=(const SceneSetv3&) = delete;
    int  init(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);
    int  collecting_gateway2defense(void);
    int  scenev3_to_scenev2(scene_t &scenev2, scene_t &scenev3);
    int  scenev2_to_scenev3(scene_t &scenev3, scene_t &scenev2);
    int  scenev3_to_scenev2(vector<scene_t> &vscenev2, vector<scene_t> &vscenev3);
    int  scenev2_to_scenev3(vector<scene_t> &vscenev3, vector<scene_t> &vscenev2);
private:
    struct DeviceHash{
        size_t operator()(const device_t &device) const
        {
            size_t ret = hash<int>()(device.id) ^ hash<string>()(device.gateway) ^ hash<string>()(device.status);
            return ret;
        }
    };
    struct DeviceEqual{
        bool operator()(const device_t &ld, const device_t &rd) const
        {
            return ld.gateway == rd.gateway && ld.id == rd.id;
        }
    };
    struct DefenseHash{
        size_t operator()(const defense_t &defense) const
        {
            size_t ret = hash<string>()(defense.gateway) ^ hash<int>()(defense.alarm);
            return ret;
        }
    };
    struct DefenseEqual{
        bool operator()(const defense_t &ld, const defense_t &rd) const
        {
            return ld.gateway == rd.gateway && ld.alarm == rd.alarm;
        }
    };
    /* <m_pos, defense_t> = <0xffff++, defense_t> */
    typedef unordered_map<device_t, defense_t, DeviceHash, DeviceEqual> Device2Defense_t;
    typedef unordered_map<defense_t, device_t, DefenseHash, DefenseEqual> Defense2Device_t;
    /* <gateway, gw-index =>[0,+00) > */
    typedef unordered_map<string, int> GatewaySet_t;
    SceneSetv2           *m_sst2;        /* pointer to SceneSetv2 instance */
    Device2Defense_t      m_device2defense;
    Defense2Device_t      m_defense2device;
    vector<device_t>      m_devices_set;
    GatewaySet_t          m_gateways;
    vector<scene_t>       m_orig_scenes;
};

#endif //_INFINITE_LOOPS_V3_HPP_

