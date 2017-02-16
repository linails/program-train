/*
 * Progarm Name: infinite_loops_v3.cpp
 * Created Time: 2016-11-09 15:06:00
 * Last modified: 2017-02-16 13:54:30
 * @author: minphone.linails linails@foxmail.com 
 */

#include "infinite_loops_v3.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::make_pair;
using std::stringstream;

/* 
 * readme !
 *
 * 1. v2 scene_t
 *       typedef struct {
 *           int     id;
 *           string  name;
 *           int     time;
 *           int     timetype; // 1 timing;  2 delay
 *           int     onoff;
 *           vector<device_t>    condition_devs;
 *           vector<int>         condition_scenes;
 *           vector<device_t>    result_devs;
 *           vector<int>         result_scenes;
 *           vector<device_t>    recover_devs;
 *           vector<int>         recover_scenes;
 *       }scene_t;
 *
 * 2. v3 scene_t 
 *       typedef struct {
 *           int     id;
 *           string  name;
 *           int     time;
 *           int     timetype; // 1 timing;  2 delay
 *           int     onoff;
 *           vector<device_t>    condition_devs;
 *           vector<int>         condition_scenes;
 *           vector<defense_t>   condition_defense;  // v3
 *           vector<device_t>    result_devs;
 *           vector<int>         result_scenes;
 *           vector<defense_t>   result_defense;     // v3
 *           vector<device_t>    recover_devs;
 *           vector<int>         recover_scenes;
 *           vector<defense_t>   recover_defense;    // v3
 *       }scene_t;
 * */

SceneSetv3::SceneSetv3(vector<device_t> &r_vdev, vector<scene_t> &r_vscene, int max_gid)
    :m_devices_set(r_vdev)
    ,m_orig_scenes(r_vscene)
    ,m_max_gid(max_gid)
{
    this->init(r_vdev, r_vscene);
}

SceneSetv3::~SceneSetv3()
{
    delete this->m_sst2;
}

int  SceneSetv3::reinit(vector<device_t> &r_vdev, vector<scene_t> &r_vscene, int max_gid)
{
    int ret = 0;

    /* step 1: clear all */
    delete this->m_sst2;
    this->m_sst2 = NULL;
    this->m_device2defense.clear();
    this->m_defense2device.clear();
    this->m_devices_set.clear();

    /* step 2: init SceneSetv3 */
    this->m_devices_set = r_vdev;
    this->m_max_gid     = max_gid;

    ret = this->init(r_vdev, r_vscene);

    return ret;
}

int  SceneSetv3::infinite_loops_check(scene_t &r_scene)    /* aim */
{
    int ret = 0;

    auto check_loopself = [](scene_t &scenev3){
        auto iter = find(scenev3.condition_scenes.begin(), 
                         scenev3.condition_scenes.end(), 
                         scenev3.id);
        if(iter == scenev3.condition_scenes.end()){
            cout << "check_loopself find nothing !" << endl;
            return -1;
        }else{
            cout << "*iter : " << *iter << endl;
            return 0;
        }
    };

    if(0 == check_loopself(r_scene)){
        cout << "[Warning] self-loop " << endl;
        return 0;
    }

    auto check = [this](scene_t &scenev3){
        scene_t scenev2;
        this->scenev3_to_scenev2(scenev2, scenev3);
        return this->m_sst2->infinite_loops_check(scenev2);
    };

    ret = check(r_scene);

    if(0 == ret){        /* exist infinite-loop */
        cout << "[Warning] exist infinite loops v3 " << endl;

        scene_t origin;

        auto isexist = [&origin, &r_scene](scene_t scene){
            if(r_scene.id == scene.id){
                /* exist */
                origin = scene;
                return 1;
            }else{
                return 0;
            }
        };

        /* Is exist before
         *
         *  Y : restore
         *  N : break
         * */
        auto iter = find_if(this->m_orig_scenes.begin(), 
                            this->m_orig_scenes.end(), 
                            isexist);

        if(iter == this->m_orig_scenes.end()){
            /* N */
            cout << "find nothing !" << endl;
        }else{
            /* Y */
            cout << "find it : sceie.id(" << iter->id << ")" << endl;
            if(0 == check(origin)){
                cout << "[Error] restore scene error" << endl;
            }else{
                cout << "restore success !" << endl;
            }
        }

    }else if(-1 == ret){ /* normal */
        /* Add this new scene to this->m_orig_scenes */
        this->m_orig_scenes.push_back(r_scene);
    }

    return ret;
}

int  SceneSetv3::del_scene(int sceneid)
{
    return this->m_sst2->del_scene(sceneid);
}

/*
 *      server
 *        ↓↓ : filter(sceneid)
 *      client
 * */
int  SceneSetv3::filter(scene_t &r_exe_scene)
{
    scene_t scenev2;

    this->scenev3_to_scenev2(scenev2, r_exe_scene);

    return this->m_sst2->filter(scenev2);
}

void SceneSetv3::print_all_set(void)
{
    cout << "print_all_set ..." << endl;
    this->m_sst2->print_all_set();
}

int  SceneSetv3::init(vector<device_t> &r_vdev, vector<scene_t> &r_vscene)
{
    int ret = 0;

    /* 
     * 1. collecting gateway from devices | r_vdev
     * 2. defense_t -> devices
     * */
    this->collecting_gid2defense();



    /*
     * format datav3 to datav2
     * */
    vector<scene_t>  vec_scenev2;
    vector<device_t> vec_devv2(this->m_devices_set);

    /* step 1 : scenev3 to scenev2 , and update defense status to this->m_defense2device device */
    this->scenev3_to_scenev2(vec_scenev2, r_vscene);

    /* step 2 : push_back all this->m_defense2device device */
    for(auto &unit : this->m_defense2device){
        vec_devv2.push_back(unit.second);
    }



    if(vec_devv2.size() > 0 && vec_scenev2.size() > 0){
        this->m_sst2 = new SceneSetv2(vec_devv2, vec_scenev2);
        if(NULL == this->m_sst2) ret = -1;
    }else{
        ret = -1;
        cout << "[Error] : vec_devv2.size() = 0 || vec_scenev2.size() = 0" << endl;
    }

    return ret;
}

int  SceneSetv3::collecting_gid2defense(void)
{
    int ret = 0;

#if 0
    for(auto &device : this->m_devices_set){
        auto got = this->m_gateways.find(device.gateway);
        if(got == this->m_gateways.end()){
            size_t idx = this->m_gateways.size() + 1;
            this->m_gateways.insert(unordered_map<string, int>::value_type(device.gateway, idx));
            cout << "gateway : " << device.gateway << " - " << idx << endl;
        }
    }


    /* generate defense devices */
    for(auto &gw : this->m_gateways){
        device_t    device;
        defense_t   defense;
        stringstream stream;

        /* status = 0 */
        defense.alarm   = 0;
        defense.gateway = gw.first;

        stream << defense.alarm;
        stream >> device.status;
        
        device.id       = gw.second + 0xffff;
        device.gateway  = gw.first;

        this->m_device2defense.insert(Device2Defense_t::value_type(device, defense));
        this->m_defense2device.insert(Defense2Device_t::value_type(defense, device));

        /* status = 1 */
        stream.clear();

        defense.alarm   = 1;
        stream << defense.alarm;
        stream >> device.status;

        this->m_device2defense.insert(Device2Defense_t::value_type(device, defense));
        this->m_defense2device.insert(Defense2Device_t::value_type(defense, device));
    }
#else
    for(int i=0; i<this->m_max_gid; i++){
        device_t     device;
        defense_t    defense;
        stringstream stream;

        /* status = 0 */
        defense.alarm   = 0;
        defense.id      = i + 1;

        stream << defense.alarm;
        stream >> device.status;
        
        device.id       = defense.id;
        device.gateway  = "Defense virtual gateway 0000";

        this->m_device2defense.insert(Device2Defense_t::value_type(device, defense));
        this->m_defense2device.insert(Defense2Device_t::value_type(defense, device));

        /* status = 1 */
        stream.clear();

        defense.alarm   = 1;
        stream << defense.alarm;
        stream >> device.status;

        this->m_device2defense.insert(Device2Defense_t::value_type(device, defense));
        this->m_defense2device.insert(Defense2Device_t::value_type(defense, device));
    }
#endif


    /* For debug print */
    {
#if 1
        cout << "----------------------------- collecting_gid2defense -----------------------------" << endl;
        int i = 0;
        for(auto &unit : this->m_device2defense){
            printf( "[%d]\n", i);
            cout << "|defense : " << endl;
            cout << "|   alarm : " << unit.second.alarm << endl;
            cout << "|   gid : " << unit.second.id << endl;
            cout << "|device :" << endl;
            cout << "|   id : " << unit.first.id << endl;
            cout << "|   status : " << unit.first.status << endl;
            printf( "|__________________________________[%d]\n", i++);
        }
        cout << "----------------------------------------------------------" << endl;
        i = 0;
        for(auto &unit : this->m_defense2device){
            printf( "[%d]\n", i);
            cout << "|defense : " << endl;
            cout << "|   alarm : " << unit.first.alarm << endl;
            cout << "|   gid : " << unit.first.id << endl;
            cout << "|device :" << endl;
            cout << "|   id : " << unit.second.id << endl;
            cout << "|   status : " << unit.second.status << endl;
            printf( "|__________________________________[%d]\n", i++);
        }
        cout << "----------------------------- collecting_gid2defense -----------------------------" << endl;
#endif
    }

    return ret;
}

/* 
 * have to update
 * */
int  SceneSetv3::scenev3_to_scenev2(scene_t &scenev2, scene_t &scenev3)
{
    scenev2.id      = scenev3.id;
    scenev2.name    = scenev3.name;
    scenev2.time    = scenev3.time;
    scenev2.timetype= scenev3.timetype; /* 1 timing;  2 delay */
    scenev2.onoff   = scenev3.onoff;

    scenev2.condition_devs  = scenev3.condition_devs;
    scenev2.condition_scenes= scenev3.condition_scenes;
    scenev2.result_devs     = scenev3.result_devs;
    scenev2.result_scenes   = scenev3.result_scenes;
    scenev2.recover_devs    = scenev3.recover_devs;
    scenev2.recover_scenes  = scenev3.recover_scenes;

    for(auto &defense : scenev3.condition_defense)
        scenev2.condition_devs.push_back(this->m_defense2device[defense]);

    for(auto &defense : scenev3.result_defense)
        scenev2.result_devs.push_back(this->m_defense2device[defense]);

    for(auto &defense : scenev3.recover_defense)
        scenev2.recover_devs.push_back(this->m_defense2device[defense]);

    return 0;
}

int  SceneSetv3::scenev2_to_scenev3(scene_t &scenev3, scene_t &scenev2)
{
    cout << "scenev2_to_scenev3 ..." << endl;
    return 0;
}

int  SceneSetv3::scenev3_to_scenev2(vector<scene_t> &vscenev2, vector<scene_t> &vscenev3)
{
    int ret = 0;

    for(auto &scenev3 : vscenev3){
        scene_t scenev2;
        this->scenev3_to_scenev2(scenev2, scenev3);
        vscenev2.push_back(scenev2);
    }

    return ret;
}

int  SceneSetv3::scenev2_to_scenev3(vector<scene_t> &vscenev3, vector<scene_t> &vscenev2)
{
    cout << "scenev2_to_scenev3 ..." << endl;
    return 0;
}

