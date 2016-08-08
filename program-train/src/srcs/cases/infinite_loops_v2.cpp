/*
 * Progarm Name: infinite_loops_v2.cpp
 * Created Time: 2016-08-02 15:02:00
 * Last modified: 2016-08-08 17:45:11
 */

#include "infinite_loops_v2.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

class ActionUnitv2{
public:
    ActionUnitv2(SceneSetv2 *p_sst, device_t &r_dev);
    ActionUnitv2(SceneSetv2 *p_sst, int sceneid);
    ~ActionUnitv2();
    int  get_pos(void);
    int  get_realtype(void);
private:
    void add2set(void);
    int  is_exist(void);
private:
    union deviceInfo{
        int       sceneid;   /* false : virtual action; true : real action*/
        device_t *realdev;
    };
    typedef tuple<bool, deviceInfo> devInfo_t;

    int                 m_pos;    /* eg,pos = 3 :bitset: 000001000 */
    devInfo_t           m_device; /* device_t */
    SceneSetv2         *m_sst;
};

/* {action1 / action2 / ... } */
class SceneUnitv2{
public:
    SceneUnitv2(SceneSetv2 *p_sst, int sceneid);
    SceneUnitv2(SceneSetv2 *p_sst, scene_t &r_scene);
    ~SceneUnitv2();
    int  get_pos(void);
    int  ring_check(void);
private:
    SceneUnitv2& add_action(ActionUnitv2 &r_au);
    SceneUnitv2& add_action(device_t &r_dev);
    SceneUnitv2& add_action(int sceneid);
    SceneUnitv2& add_trig(ActionUnitv2 &r_au);
    SceneUnitv2& add_trig(device_t &r_dev);
    SceneUnitv2& add_trig(int sceneid);
    void add2set(void);
    int  is_exist(void);
    void add_action_trig_scene(void);
    void add_action_trig_scene(int vir_action);
    void add_action_vir(int sid, int action); /* add virtual action */
    void add_trig_vir(int sid, int action);   /* add virtual action */
    int  ring_check(int                                 timing,
                    tuple<int, int, vector<int> >       subscene, /* <action, sceneid_pos, action-set>*/
                    int                                 sid);     /* orig sceneid-pos */
private:
    int                 m_pos;    /* eg,pos = 3 :bitset: 000001000 */
    int                 m_sceneid;
    tuple<int, int>     m_time;   /* <type, time> : {type | 1 timing;  2 delay} */
    vector<int>         m_action_set;
    vector<int>         m_trig_action_set;
    SceneSetv2         *m_sst;
};

//------------------------------------------------------------

ActionUnitv2::ActionUnitv2(SceneSetv2 *p_sst, device_t &r_dev)
    :m_sst(p_sst)
{
    get<0>(this->m_device)  = true;

    get<1>(this->m_device).realdev = NULL;
    get<1>(this->m_device).realdev = new device_t;
    if(NULL == get<1>(this->m_device).realdev){
        cout << "new failed " << endl;
        return;
    }

    get<1>(this->m_device).realdev->id       = r_dev.id;
    get<1>(this->m_device).realdev->gateway  = r_dev.gateway;
    get<1>(this->m_device).realdev->status   = r_dev.status;

    if(0 != this->is_exist()){

        this->m_pos = get<0>(*this->m_sst->action_set);

        this->add2set();
    }
}

ActionUnitv2::ActionUnitv2(SceneSetv2 *p_sst, int sceneid)
    :m_sst(p_sst)
{
    get<0>(this->m_device)  = false;

    get<1>(this->m_device).sceneid   = sceneid;

    //if(0 != this->is_exist()){

        this->m_pos = get<0>(*this->m_sst->action_set);

        cout << "virtual action -> sceneid : " << this->m_pos << " - " << sceneid << endl;

        this->add2set();
    //}
}

int  ActionUnitv2::get_pos(void)
{
    return this->m_pos;
}

/* 0: real; -1: virtual */
int  ActionUnitv2::get_realtype(void)
{
    if(true == get<0>(this->m_device)){
        return 0;
    }else{
        return -1;
    }
}

void ActionUnitv2::add2set(void)
{
    if(true == get<0>(this->m_device)){
        if(true == 
            /* 
             * <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> 
             * tuple<int, unordered_map<int, tuple<bool, int, string> > >
             * */
            get<1>(*this->m_sst->action_set).insert(unordered_map<int, tuple<bool, int, string> >::
                value_type(this->m_pos, 
                    make_tuple(
                        get<0>(this->m_device),
                        get<1>(this->m_device).realdev->id,
                        get<1>(this->m_device).realdev->gateway))).second){
            get<0>(*this->m_sst->action_set)++;
        }
    }else{
        if(true == 
            get<1>(*this->m_sst->action_set).insert(unordered_map<int, tuple<bool, int, string> >::
                value_type(this->m_pos, 
                    make_tuple(
                        get<0>(this->m_device),
                        get<1>(this->m_device).sceneid,
                        ""))).second){
            get<0>(*this->m_sst->action_set)++;
        }
    }
}

/* return 0 : exist */
int  ActionUnitv2::is_exist(void)
{
    if(true == get<0>(this->m_device)){
        /* 
         * <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> 
         * tuple<int, unordered_map<int, tuple<bool, int, string> > >
         * */
        for(auto iter = get<1>(*this->m_sst->action_set).begin();
                 iter!= get<1>(*this->m_sst->action_set).end(); iter++){
            if((get<1>(iter->second) == get<1>(this->m_device).realdev->id)&&
               (get<2>(iter->second) == get<1>(this->m_device).realdev->gateway)){

                this->m_pos = iter->first;
                return 0;
            }
        }
        return -1;
    }else{
        for(auto iter = get<1>(*this->m_sst->action_set).begin();
                 iter!= get<1>(*this->m_sst->action_set).end(); iter++){
            if((get<0>(iter->second) == false)&&
               (get<1>(iter->second) == get<1>(this->m_device).sceneid)){

                this->m_pos = iter->first;
                return 0;
            }
        }
        return -1;
    }
}

ActionUnitv2::~ActionUnitv2()
{
    if(true == get<0>(this->m_device)){
        delete get<1>(this->m_device).realdev;
    }
}

//------------------------------------------------------------

SceneUnitv2::SceneUnitv2(SceneSetv2 *p_sst, int sceneid)
    :m_sceneid(sceneid)
    ,m_sst(p_sst)
{
    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto iter = get<1>(*this->m_sst->scene_unit_set).begin();
             iter!= get<1>(*this->m_sst->scene_unit_set).end(); iter++){
        if(get<0>(iter->second) == sceneid){
            this->m_pos             = iter->first;

            get<0>(this->m_time)    = get<0>(get<3>(iter->second));
            get<1>(this->m_time)    = get<1>(get<3>(iter->second));

            this->m_action_set      = get<1>(iter->second);
            this->m_trig_action_set = get<1>(iter->second);

            return;
        }
    }

    if(0 != this->is_exist()){

        this->m_pos = get<0>(*this->m_sst->scene_unit_set);

        this->add2set();

        this->add_action_trig_scene();
    }
}

SceneUnitv2::SceneUnitv2(SceneSetv2 *p_sst, scene_t &r_scene)
    :m_sst(p_sst)
{
    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto iter = get<1>(*this->m_sst->scene_unit_set).begin();
             iter!= get<1>(*this->m_sst->scene_unit_set).end(); iter++){

        /* exist sceneid ; return */
        if(get<0>(iter->second) == r_scene.id){
            this->m_pos             = iter->first;

            get<0>(this->m_time)    = get<0>(get<3>(iter->second));
            get<1>(this->m_time)    = get<1>(get<3>(iter->second));

            this->m_action_set      = get<1>(iter->second);
            this->m_trig_action_set = get<2>(iter->second);

            return;
        }
    }

    this->m_sceneid = r_scene.id;

    get<0>(this->m_time) = r_scene.timetype;
    get<1>(this->m_time) = r_scene.time;

    /* add action */
    {
        /* 1. add real action -> this->m_trig_action_set */
        for(auto &dev : r_scene.condition_devs) this->add_trig(dev);

        /* 2. add virtual action[:scene] -> this->m_trig_action_set */
        for(auto &scene : r_scene.condition_scenes) this->add_trig(scene);

        /* 3. add real action -> this->m_action_set */
        for(auto &dev : r_scene.result_devs) this->add_action(dev);

        /* 4. add virtual action[:scene] -> this->m_action_set */
        for(auto &scene : r_scene.result_scenes) this->add_action(scene);
    }

    if(0 != this->is_exist()){

        this->m_pos = get<0>(*this->m_sst->scene_unit_set);

        this->add2set();

        this->add_action_trig_scene();
    }
}

int  SceneUnitv2::get_pos(void)
{
    return this->m_pos;
}

/* return 0 : existed */
int  SceneUnitv2::ring_check(void)
{
    /* <type, time> : {type | 1 timing;  2 delay} 
     * tuple<int, int> 
     * */
    int timing = get<0>(this->m_time) == 1 ? get<1>(this->m_time) : 0;

    return this->ring_check(timing,
                            make_tuple(0xffff, this->m_pos, this->m_action_set),
                            this->m_pos);
}

/* return 0 : existed */
int  SceneUnitv2::ring_check(
        int                                 timing,
        tuple<int, int, vector<int> >       subscene, /* <action, sceneid_pos, action-set>*/
        int                                 sid)      /* orig sceneid-pos */
{
    cout << "action|sceneid_pos : " << get<0>(subscene) << " | " << get<1>(subscene);
    cout << " - timing : " << timing << endl;
    int ret = -1;

    if(0xffff == get<0>(subscene)){
        cout << "first called" << endl;
        /* <action, sceneid, action-set> */
        for(auto action : get<2>(subscene)){

            /* <cnt, <m_pos, vector<m_sceneid>> > */
            auto got = get<1>(*this->m_sst->action_trig_scene_set).find(action);

            if(get<1>(*this->m_sst->action_trig_scene_set).end() == got)   ret = -1;
            else{
                cout << "xxxx" << endl;
                cout << "got->first : " << got->first ;
                cout << " got->second.size() : " << got->second.size() << endl;
                for(auto sid2 : got->second){
                    cout << "sid2 : " << sid2 << " - sid : " << sid << endl;

                    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
                     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int>>>>
                     * */
                    auto got2 = get<1>(*this->m_sst->scene_unit_set).find(sid2);
                    if(get<1>(*this->m_sst->scene_unit_set).end() == got2) cout << "ring_check : error !" << endl;
                    else{

                        {
                            /* timing check 
                             * <type, time> : {type | 1 timing;  2 delay}
                             * */
                            if(1 == get<0>(get<3>(got2->second))){

                                int max_timing = get<1>(get<3>(got2->second));

                                printf("timing : %.8d  - max_timing : %.8d \n", timing, max_timing);

                                if(timing > max_timing){
                                    cout << "timing error << " << endl;
                                    return 1;
                                }else{
                                    timing = max_timing;
                                }
                            }
                        }

                        if(sid2 == sid) return 0;   /* termination condition */

                        ret = this->ring_check(timing,
                                         make_tuple(got->first, sid2, get<1>(got2->second)),
                                         sid);
                        if(0 == ret) return 0;
                    }
                }
            }

        }
    }else{
        /* <action, sceneid, action-set> */
        for(auto action : get<2>(subscene)){

            auto got = get<1>(*this->m_sst->action_trig_scene_set).find(action);

            if(get<1>(*this->m_sst->action_trig_scene_set).end() == got)   ret = -1;
            else{
                cout << ". . got->first : " << got->first ;
                cout << " got->second.size() : " << got->second.size() << endl;
                for(auto sid2 : got->second){
                    cout << ". . sid2 : " << sid2 << " - sid : " << sid << endl;

                    auto got2 = get<1>(*this->m_sst->scene_unit_set).find(sid2);
                    if(get<1>(*this->m_sst->scene_unit_set).end() == got2) cout << "ring_check : error !" << endl;
                    else{

                        {
                            /* timing check 
                             * <type, time> : {type | 1 timing;  2 delay}
                             * */
                            if(1 == get<0>(get<3>(got2->second))){

                                int max_timing = get<1>(get<3>(got2->second));

                                printf("timing : %.8d  - max_timing : %.8d \n", timing, max_timing);

                                if(timing > max_timing){
                                    cout << "timing error << " << endl;
                                    return 1;
                                }else{
                                    timing = max_timing;
                                }
                            }
                        }

                        if(sid2 == sid) return 0;   /* termination condition */

                        ret = this->ring_check(timing,
                                         make_tuple(got->first, sid2, get<1>(got2->second)),
                                         sid);
                        if(0 == ret) return 0;
                    }
                }
            }

        }
    }

    return ret;
}

SceneUnitv2& SceneUnitv2::add_action(ActionUnitv2 &r_au)
{
    bool flag = false;

    for(auto pos : this->m_action_set) if(pos == r_au.get_pos()) flag = true;
    
    if(false == flag) this->m_action_set.push_back(r_au.get_pos());

    return *this;
}

SceneUnitv2& SceneUnitv2::add_action(device_t &r_dev)
{
    ActionUnitv2 au(this->m_sst, r_dev);
    return this->add_action(au);
}

SceneUnitv2& SceneUnitv2::add_action(int sceneid)
{
    ActionUnitv2 au(this->m_sst, sceneid);

    this->add_trig_vir(sceneid, au.get_pos());

    this->add_action_trig_scene(au.get_pos());

    return this->add_action(au);
}

SceneUnitv2& SceneUnitv2::add_trig(ActionUnitv2 &r_au)
{
    bool flag = false;

    for(auto pos : this->m_trig_action_set){
        if(pos == r_au.get_pos()) flag = true;
        cout << "pos : " << pos << " flag : " << (flag ? "true" : "false") << endl;
    }
    
    if(false == flag) this->m_trig_action_set.push_back(r_au.get_pos());

    return *this;
}

SceneUnitv2& SceneUnitv2::add_trig(device_t &r_dev)
{
    ActionUnitv2 au(this->m_sst, r_dev);
    return this->add_trig(au);
}

SceneUnitv2& SceneUnitv2::add_trig(int sceneid)
{
    ActionUnitv2 au(this->m_sst, sceneid);

    this->add_action_vir(sceneid, au.get_pos());

    return this->add_trig(au);
}

void SceneUnitv2::add_action_vir(int sid, int action) /* add virtual action */
{
    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*this->m_sst->scene_unit_set)){
        if(sid == get<0>(unit.second)){
            for(auto action_unit : get<1>(unit.second)) if(action_unit == action) return;

            get<1>(unit.second).push_back(action);
            break;
        }
    }
}

void SceneUnitv2::add_trig_vir(int sid, int action)   /* add virtual action */
{
    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*this->m_sst->scene_unit_set)){
        if(sid == get<0>(unit.second)){
            for(auto action_unit : get<2>(unit.second)) if(action_unit == action) return;

            get<2>(unit.second).push_back(action);
            break;
        }
    }
}

void SceneUnitv2::add2set(void)
{
    if(true == 
        /* 
         * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
         * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
         * */
        get<1>(*this->m_sst->scene_unit_set).insert(unordered_map<int, 
            tuple<int, vector<int>, vector<int>, tuple<int, int> > >::
            value_type(this->m_pos,
                make_tuple(
                    this->m_sceneid,
                    this->m_action_set,
                    this->m_trig_action_set,
                    make_tuple(get<0>(this->m_time), get<1>(this->m_time))))).second){
        get<0>(*this->m_sst->scene_unit_set)++;
    }
}

/* return 0 : exist */
int  SceneUnitv2::is_exist(void)
{
    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*this->m_sst->scene_unit_set)){
        if(get<0>(unit.second) == this->m_sceneid){
            this->m_pos = unit.first;
            return 0;
        }
    }
    return -1;
}

void SceneUnitv2::add_action_trig_scene(void)
{
    for(auto action : this->m_trig_action_set){
        cout << "action : " << action << endl;
        auto got = get<1>(*this->m_sst->action_trig_scene_set).find(action);

        /* <cnt, <m_pos, vector<m_sceneid>> > */
        if(get<1>(*this->m_sst->action_trig_scene_set).end() == got){
            vector<int> vi;
            vi.push_back(this->m_pos);
            cout << "vi.size() : " << vi.size() << endl;
            if(true == 
                    get<1>(*this->m_sst->action_trig_scene_set).insert(unordered_map<int, vector<int> >::
                        value_type(action, vi)).second){
                get<0>(*this->m_sst->action_trig_scene_set)++;
            }
            cout << " size : " << get<1>(*this->m_sst->action_trig_scene_set)[action].size() << endl;
        }else{
            for(auto pos : got->second){
                if(pos == this->m_pos) return;
            }

            got->second.push_back(this->m_pos);
        }
    }
}

void SceneUnitv2::add_action_trig_scene(int vir_action)
{
    cout << "vir_action : " << vir_action << endl;
    auto got = get<1>(*this->m_sst->action_trig_scene_set).find(vir_action);

    /* <cnt, <m_pos, vector<m_sceneid>> > */
    if(get<1>(*this->m_sst->action_trig_scene_set).end() == got){
        for(auto &unit : get<1>(*this->m_sst->scene_unit_set)){
            if(get<1>(get<1>(*this->m_sst->action_set)[vir_action]) == 
                    get<0>(unit.second)){
                vector<int> vi;
                vi.push_back(unit.first);

                cout << "vi.size() : " << vi.size() << endl;
                if(true == 
                        get<1>(*this->m_sst->action_trig_scene_set).insert(unordered_map<int, vector<int> >::
                            value_type(vir_action, vi)).second){
                    get<0>(*this->m_sst->action_trig_scene_set)++;
                }
                cout << " size : " << get<1>(*this->m_sst->action_trig_scene_set)[vir_action].size() << endl;
            }
        }
    }else{

        for(auto &unit : get<1>(*this->m_sst->scene_unit_set)){
            if(get<1>(get<1>(*this->m_sst->action_set)[vir_action]) == 
                    get<0>(unit.second)){

                for(auto pos : got->second){
                    if(pos == unit.first) return;
                }

                got->second.push_back(unit.first);

            }
        }

    }
}

SceneUnitv2::~SceneUnitv2()
{
}

//------------------------------------------------------------

SceneSetv2::SceneSetv2(vector<device_t> &r_vdev, vector<scene_t> &r_vscene)
{
    this->action_set            = new(ActionSet_t);
    this->scene_unit_set        = new(SceneUnitSet_t);
    this->action_trig_scene_set = new(Action_Trig_SceneSet_t);

    this->reset_all_set();

    this->add_actionunit(r_vdev);
    this->add_sceneunit(r_vscene);
}

int  SceneSetv2::get_action_pos(device_t &r_dev)
{
    ActionUnitv2 au(this, r_dev);
    return au.get_pos();
}

int  SceneSetv2::get_scene_unit_pos(scene_t &r_scene)
{
    SceneUnitv2 su(this, r_scene);
    return su.get_pos();
}

void SceneSetv2::add_actionunit(vector<device_t> &r_vdev)
{
    for(auto &unit : r_vdev) ActionUnitv2 au(this, unit);
}

void SceneSetv2::add_sceneunit(vector<scene_t> &r_vscene)
{
    for(auto &unit : r_vscene) SceneUnitv2 su(this, unit);
}

void SceneSetv2::del_vir_action(int pos) /* pos : vir_action */
{
    /*
     * <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> 
     * tuple<int, unordered_map<int, tuple<bool, int, string> > >
     * */
    if(false == get<0>(get<1>(*action_set)[pos])){

        /* 
         * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
         * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
         * */
        for(auto &unit : get<1>(*scene_unit_set)){
            if(get<0>(unit.second) == get<1>(get<1>(*action_set)[pos])){

                /* for m_action_set */
                auto iter = get<1>(unit.second).begin();
                for(; iter != get<1>(unit.second).end(); iter++){
                    if(*iter == pos) break;
                }
                if(iter != get<1>(unit.second).end()){
                    get<1>(unit.second).erase(iter);
                }

                /* for m_trig_action_set */
                auto iter1 = get<2>(unit.second).begin();
                for(; iter1 != get<2>(unit.second).end(); iter1++){
                    if(*iter1 == pos) break;
                }
                if(iter1 != get<2>(unit.second).end()){
                    get<2>(unit.second).erase(iter1);
                }
                break;
            }
        }
        cout << "delete vir action ..." << endl;
    }
}

void SceneSetv2::del_action_trig_scene(int pos, int sceneid_pos)
{

    this->del_vir_action(pos); /* pos : vir_action */

    /* <cnt, <m_pos, vector<m_sceneid>> > */
    for(auto iter : get<1>(*action_trig_scene_set)){
        if(pos == iter.first){
            cout << "del_action_trig_scene : pos = " << pos ;
            cout << " -> iter.second.size() : " << iter.second.size() << endl;
            if(1 == iter.second.size()){
                get<1>(*action_trig_scene_set).erase(pos);
                get<0>(*action_trig_scene_set)--;
            }else{
                auto iter2 = iter.second.begin();
                for(; iter2 != iter.second.end(); iter2++){
                    if(sceneid_pos == *iter2) break;
                }
                if(iter2 != iter.second.end()){
                    iter.second.erase(iter2);
                }
            }

            break;
        }
    }
}

void SceneSetv2::del_sceneunit(scene_t &r_scene)
{
    int pos = 0xffff;

    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*scene_unit_set)){
        if(get<0>(unit.second) == r_scene.id){
            pos = unit.first;
            break;
        }
    }

    if(0xffff != pos){ /* pos : sid_pos*/

        /* get<2>(get<1>(*scene_unit_set)[pos] : m_trig_action_set */
        for(auto action : get<2>(get<1>(*scene_unit_set)[pos])) this->del_action_trig_scene(action, pos);

        /* get<1>(get<1>(*scene_unit_set)[pos] : m_action_set */
        for(auto action : get<1>(get<1>(*scene_unit_set)[pos])){

            /* vir action */
            /* <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> */
            if(false == get<0>(get<1>(*action_set)[action])){
                this->del_action_trig_scene(action, pos);
            }
        }

        {

            stack<int> vir_action;

            /* get<2>(get<1>(*scene_unit_set)[sid_pos] : m_trig_action_set */
            for(auto action : get<2>(get<1>(*scene_unit_set)[pos])){
                /* vir action */
                /* <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> */
                if(false == get<0>(get<1>(*action_set)[action])){
                    vir_action.push(action);
                }
            }

            while(false == vir_action.empty()){
                int pos = vir_action.top();

                vir_action.pop();

                get<1>(*action_set).erase(pos);
                get<0>(*action_set)--;
            }
        }
        {

            stack<int> vir_action;

            /* get<1>(get<1>(*scene_unit_set)[sid_pos] : m_action_set */
            for(auto action : get<1>(get<1>(*scene_unit_set)[pos])){
                /* vir action */
                /* <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> */
                if(false == get<0>(get<1>(*action_set)[action])){
                    vir_action.push(action);
                }
            }

            while(false == vir_action.empty()){
                int pos = vir_action.top();

                vir_action.pop();

                get<1>(*action_set).erase(pos);
                get<0>(*action_set)--;
            }
        }

        get<1>(*scene_unit_set).erase(pos);
        get<0>(*scene_unit_set)--;

    }
}

/* return 0 : exist */
int  SceneSetv2::infinite_loops_check(scene_t &r_scene)
{
    SceneUnitv2 su(this, r_scene);

    /* if exist del scene */

    int ret = su.ring_check();
    if(0 == ret){
        this->del_sceneunit(r_scene);
    }else if(1 == ret){
        this->del_sceneunit(r_scene);
    }
    return ret;
}

void SceneSetv2::reset_all_set(void)
{
    get<0>(*action_set) = 0;

    if(true == get<1>(*action_set).empty()){
        get<1>(*action_set).clear();
    }

    get<0>(*scene_unit_set) = 0;

    if(true == get<1>(*scene_unit_set).empty()){
        get<1>(*scene_unit_set).clear();
    }

    get<0>(*action_trig_scene_set) = 0;
    if(true == get<1>(*action_trig_scene_set).empty()){
        get<1>(*action_trig_scene_set).clear();
    }
}

void SceneSetv2::print_all_set(void)
{
    {
        /*
         * ActionSet_t :
         *
         * <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> 
         * tuple<int, unordered_map<int, tuple<bool, int, string> > >
         * */
        cout << "------------------------ action_set ------------------------" << endl;
        cout << "<cnt, <m_pos, <realtype, devid/sceneid, gateway>>> " << endl;
        cout << get<0>(*action_set) << endl;
#if 1
        for(auto &unit : get<1>(*action_set)){
            if(unit.first >= 1000){
                cout << get<0>(*action_set) << "   ";
                cout << unit.first << "   ";
                cout << (get<0>(unit.second) ? "true " : "false") << "   ";
                cout << get<1>(unit.second) << "  ";
                cout << get<2>(unit.second) << endl;
            }
        }
#endif
    }

    {
        /* 
         * SceneUnitSet_t :
         *
         * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
         * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
         * */
        cout << "------------------------ scene_unit_set ------------------------" << endl;
        cout << "<cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> " << endl;
        cout << get<0>(*scene_unit_set) << endl;

        for(auto &unit : get<1>(*scene_unit_set)){
            printf("%.4d  ", get<0>(*scene_unit_set));
            printf(" %.4d    ", unit.first);
            printf(" %.4d  ", get<0>(unit.second));
            {
                printf("actions : ");
                for(auto pos : get<1>(unit.second)) printf("%.4d|", pos);
                printf("\n                      ");
                printf("trigs   : ");
                for(auto pos : get<2>(unit.second)) printf("%.4d|", pos);
            }
            cout << endl;
        }
    }

    {
        /* 
         * Action_Trig_SceneSet_t :
         *
         * <cnt, <m_pos, vector<m_sceneid>> > 
         * tuple<int, unordered_map<int, vector<int>> >
         * */
        cout << "------------------------ action_trig_scene_set ------------------------" << endl;
        cout << " <cnt, <m_pos, vector<m_sceneid>> > " << endl;
        cout << get<0>(*action_trig_scene_set) << endl;

        for(auto &unit : get<1>(*action_trig_scene_set)){
            printf("%.4d  ", get<0>(*action_trig_scene_set));
            printf(" %.4d ", unit.first);
            printf(" scene_pos : ");
            for(auto pos : unit.second) printf("%.4d|",pos);
            cout << endl;
        }
    }
}

SceneSetv2::~SceneSetv2()
{
    delete this->action_set;
    delete this->scene_unit_set;
    delete this->action_trig_scene_set;
}

