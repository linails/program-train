/*
 * Progarm Name: infinite-loops-drived.hpp
 * Created Time: 2016-11-10 17:54:34
 * Last modified: 2016-11-10 18:03:16
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _INFINITE_LOOPS_DRIVED_HPP_
#define _INFINITE_LOOPS_DRIVED_HPP_

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

class SceneSetDrived : public infinite_loops_v2
{
public:
    SceneSetDrived(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);
    ~SceneSetDrived();

    int  reinit(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);

    int  infinite_loops_check(scene_t &r_scene);    /* aim */

    int  del_scene(int sceneid);

    /*
     *      server
     *        ↓↓ : filter(sceneid)
     *      client
     * */
    int  filter(scene_t &r_exe_scene);

private:
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
    Device2Defense_t      m_device2defense;
    Defense2Device_t      m_defense2device;
    vector<device_t>      m_devices_set;
    GatewaySet_t          m_gateways;
}

#endif //_INFINITE_LOOPS_DRIVED_HPP_

