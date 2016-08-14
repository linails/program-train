/*
 * Progarm Name: infinite_loops_v2.cpp
 * Created Time: 2016-08-02 15:02:00
 * Last modified: 2016-08-12 19:18:14
 */

#include "infinite_loops_v2.h"
#include <iostream>
#include <cstdio>
#include <stack>
#include <unordered_set>

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
    int  generate_pos(void);
    ActionUnitv2(const ActionUnitv2&) = delete;
    ActionUnitv2 &operator=(const ActionUnitv2&) = delete;
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
    SceneUnitv2(const SceneUnitv2 &) = delete;
    SceneUnitv2& operator=(const SceneUnitv2&) = delete;
    SceneUnitv2& add_action(ActionUnitv2 &r_au);
    SceneUnitv2& add_action(device_t &r_dev);
    SceneUnitv2& add_action(int sceneid);
    SceneUnitv2& add_trig(ActionUnitv2 &r_au);
    SceneUnitv2& add_trig(device_t &r_dev);
    SceneUnitv2& add_trig(int sceneid);
    void add2set(void);
    int  is_exist(void);
    int  generate_pos(void);
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

class Filter{
public:
    Filter(SceneSetv2 *p_sst, int sid_pos);
    ~Filter();
    int  filtering(scene_t &scene, int sid_pos);
    int  is_pending(void);
private:
    int  filtering(int sid_pos);
    int  generate_scenes_actionset(void);
    int  add_scenes_action(int sid_pos, const vector<int> &action_set);
    int  step(int sid_pos);
    int  get_pending_from_esid(
            unordered_map<int, bool> &actions, 
            list<int> &pending_sid, 
            int sid_pos); /* from exec sid_pos */
    int  pruning(scene_t &scene);
    int  pruning_actions(vector<device_t> &r_result_devs);
    int  pruning_scenes(vector<int> &r_result_scenes);
    int  set_used_flag(unordered_map<int, bool> &actions);
private:
    /* <action_pos, used> | used -> true */
    typedef unordered_map<int, bool> ScenesActionSet_t;
    /* <sid_pos> | current pending (sid_pos) */
    typedef list<int> PendingSidPos_t;
    int                 m_sid_pos_top;
    SceneSetv2         *m_sst;
    ScenesActionSet_t   m_sas;
    PendingSidPos_t     m_pending_sid_pos; /* current pending sid_pos */
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

        this->m_pos = this->generate_pos();

        this->add2set();
    }
}

ActionUnitv2::ActionUnitv2(SceneSetv2 *p_sst, int sceneid)
    :m_sst(p_sst)
{
    get<0>(this->m_device)  = false;

    get<1>(this->m_device).sceneid   = sceneid;

    //if(0 != this->is_exist()){

        this->m_pos = this->generate_pos();

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
             * <cnt, <m_pos, <realtype, devid/sceneid, gateway, status>>> 
             * tuple<int, unordered_map<int, tuple<bool, int, string, string> > >
             * */
            get<1>(*this->m_sst->action_set).insert(unordered_map<int, tuple<bool, int, string, string> >::
                value_type(this->m_pos, 
                    make_tuple(
                        get<0>(this->m_device),
                        get<1>(this->m_device).realdev->id,
                        get<1>(this->m_device).realdev->gateway,
                        get<1>(this->m_device).realdev->status))).second){
            if(this->m_pos == get<0>(*this->m_sst->action_set)){
                get<0>(*this->m_sst->action_set)++;
            }
        }
    }else{
        if(true == 
            get<1>(*this->m_sst->action_set).insert(unordered_map<int, tuple<bool, int, string, string> >::
                value_type(this->m_pos, 
                    make_tuple(
                        get<0>(this->m_device),
                        get<1>(this->m_device).sceneid,
                        "",
                        ""))).second){
            if(this->m_pos == get<0>(*this->m_sst->action_set)){
                get<0>(*this->m_sst->action_set)++;
            }
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
               (get<2>(iter->second) == get<1>(this->m_device).realdev->gateway &&
               (get<3>(iter->second) == get<1>(this->m_device).realdev->status))){

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

int  ActionUnitv2::generate_pos(void)
{
    if(false == get<0>(this->m_sst->m_del_set).empty()){
        int front = get<0>(this->m_sst->m_del_set).front();
        get<0>(this->m_sst->m_del_set).pop_front();
        return front;
    }else
        return get<0>(*this->m_sst->action_set);
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

        this->m_pos = this->generate_pos();

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

        this->m_pos = this->generate_pos();

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
        if(this->m_pos == get<0>(*this->m_sst->scene_unit_set)){
            get<0>(*this->m_sst->scene_unit_set)++;
        }
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

int  SceneUnitv2::generate_pos(void)
{
    if(false == get<1>(this->m_sst->m_del_set).empty()){
        int front = get<1>(this->m_sst->m_del_set).front();
        get<1>(this->m_sst->m_del_set).pop_front();
        return front;
    }else
        return get<0>(*this->m_sst->scene_unit_set);
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
    this->action_set            = new ActionSet_t ;
    this->scene_unit_set        = new SceneUnitSet_t ;
    this->action_trig_scene_set = new Action_Trig_SceneSet_t ;

    this->reset_all_set();

    this->add_actionunit(r_vdev);
    this->add_sceneunit(r_vscene);
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

void SceneSetv2::del_sceneunit(int sceneid)
{
    int pos = 0xffff;

    /* 
     * <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*scene_unit_set)){
        if(get<0>(unit.second) == sceneid){
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

                this->del_pos(0, pos);
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

                this->del_pos(0, pos);
            }
        }

        this->del_pos(1, pos);

    }
}

/* return 0 : exist */
int  SceneSetv2::infinite_loops_check(scene_t &r_scene)
{
    /* for update : step 1 : delete sceneid ; step 2 : new sceneid */
    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto &unit : get<1>(*this->scene_unit_set)){
        if(r_scene.id == get<0>(unit.second)){
            cout << "update scene : step 1 ..." << endl;
            this->del_scene(r_scene.id);
            break;
        }
    }

    /* new */
    SceneUnitv2 su(this, r_scene);


    /* if exist del scene */

    int ret = su.ring_check();
    if(0 == ret){
        this->del_sceneunit(r_scene.id);
    }else if(1 == ret){
        this->del_sceneunit(r_scene.id);
    }
    cout << "quit infinite_loops_check !" << endl;
    return ret;
}

int  SceneSetv2::del_scene(int sceneid)
{
    this->del_sceneunit(sceneid);
    return 0;
}

/* pos_type : 0->action_pos ; 1->sid_pos */
int  SceneSetv2::del_pos(int pos_type, int pos)
{
    if(0 == pos_type){ /* action_pos */
        if(pos+1 == get<0>(*action_set)){
            cout << "pos = get<0>(*action_set)" << endl;
            get<0>(*action_set)--;
        }else{
            cout << "pos + 1 != *action_set.size() ";
            cout << ": " << pos << " - " << get<0>(*action_set) << endl;
            get<0>(this->m_del_set).push_back(pos);
            get<0>(this->m_del_set).sort();
        }
        get<1>(*action_set).erase(pos);

    }else if(1 == pos_type){ /* sid_pos */
        if(pos+1 == get<0>(*scene_unit_set)){
            cout << "pos = get<0>(*scene_unit_set)" << endl;
            get<0>(*scene_unit_set)--;
        }else{
            cout << "pos + 1 != *scene_unit_set.size() " << endl;
            cout << ": " << pos << " - " << get<0>(*scene_unit_set) << endl;
            get<1>(this->m_del_set).push_back(pos);
            get<1>(this->m_del_set).sort();
        }
        get<1>(*scene_unit_set).erase(pos);
    }
    return 0;
}

/*
 *     server
 *       ↓↓ : filter(sceneid)
 *     client
 * */
int  SceneSetv2::filter(scene_t &r_exe_scene)
{
    int sid_pos = 0xffff;

    /* step 1 : search sid_pos  */
    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >*/
    for(auto &unit : get<1>(*this->scene_unit_set)){
        if(r_exe_scene.id == get<0>(unit.second)){
            sid_pos = unit.first;
            break;
        }
    }

    if(0xffff == sid_pos){
        cout << "filter error !" << endl;
        return -1;
    }



    cout << "this->m_filter_set.size() : " << this->m_filter_set.size() << endl;
    /* step 2 : filter actions */
    auto iter = this->m_filter_set.begin();
    for( ; iter!= this->m_filter_set.end(); iter++){

        cout << "sid_pos : " << sid_pos << endl;
        /* filtering... */
        if(0 == (*iter)->filtering(r_exe_scene, sid_pos)) break;
    }

    if(iter != this->m_filter_set.end()){
        /* have no several scenes is pending , delete Filter*/
        if(0 != (*iter)->is_pending()){
            delete *iter;
            this->m_filter_set.erase(iter);
            cout << "this->m_filter_set.erase(iter);" << endl;
        }
    }else{

        cout << "new Filter(this, sid_pos);" << endl;
        /* step 3 : if isn't a pending scene , new Filter */
        Filter *pfilter = new Filter(this, sid_pos);

        if(0 != pfilter->is_pending()){
            cout << "delete pfilter " << endl;
            delete pfilter;
        }
        else{
            this->m_filter_set.push_back(pfilter);
        }
    }

    return 0;
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
         * <cnt, <m_pos, <realtype, devid/sceneid, gateway, status>>> 
         * tuple<int, unordered_map<int, tuple<bool, int, string, string> > >
         * */
        cout << "------------------------ action_set ------------------------" << endl;
        cout << get<0>(*action_set);
        cout << " : { del-set : ";
        for(auto unit : get<0>(this->m_del_set)) printf("%.4d ", unit);
        cout << " } " << endl;
        cout << "<cnt, <m_pos, <realtype, devid/sceneid, gateway>>> " << endl;
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
        cout << get<0>(*scene_unit_set);
        cout << " : { del-set : ";
        for(auto unit : get<1>(this->m_del_set)) printf("%.4d ", unit);
        cout << " } " << endl;
        cout << "<cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> " << endl;

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
    for(auto iter = this->m_filter_set.begin();
             iter!= this->m_filter_set.end(); iter++){
        delete *iter;
    }
}

//------------------------------------------------------------

Filter::Filter(SceneSetv2 *p_sst, int sid_pos)
    :m_sid_pos_top(sid_pos)
    ,m_sst(p_sst)
{
    this->generate_scenes_actionset();

    if(0 != this->is_pending()){
        cout << "this->m_pending_sid_pos is empty" << endl;
    }else{
        cout << "pending sid : ";
        for(auto sid : this->m_pending_sid_pos){
            cout << sid << " ";
        }
        cout << endl;
    }

    this->filtering(this->m_sid_pos_top);
}

int  Filter::filtering(int sid_pos)
{
    list<int> pending_sid;
    unordered_map<int, bool> actions;

    /* step 1.1 : get next pending sid from current sid_pos */
    this->get_pending_from_esid(actions, pending_sid, sid_pos);

    /* step 1.2 : del current <sid_pos> */
    /* <sid_pos> | current pending (sid_pos) */
    for(auto iter = this->m_pending_sid_pos.begin();
             iter!= this->m_pending_sid_pos.end(); iter++){
        if(*iter == sid_pos){
            this->m_pending_sid_pos.erase(iter);
            break;
        }
    }

    /* step 1.3 : set this->m_sas used flag = true { sid_pos->action_set | this->m_sas } */
    this->set_used_flag(actions);

    {
        // for debug
        cout << "pending sid : ";
        for(auto sid : this->m_pending_sid_pos){
            cout << sid << " ";
        }
        cout << endl;

        cout << "m_sas : " << endl;
        int i = 0;
        for(auto &unit : this->m_sas){
            printf("%.4d : %s | ", unit.first, (unit.second ? "x" : "o"));
            if(++i % 10 == 0) cout << endl;
        }
        cout << endl;
    }
    return 0;
}

/* success return 0 ; fail return -1*/
int  Filter::filtering(scene_t &scene, int sid_pos)
{
    /* step 1 : is <sid_pos> existed */
    if(0 == this->step(sid_pos)){

        list<int> pending_sid;
        unordered_map<int, bool> actions;

        /* step 1.1 : get next pending sid from current sid_pos */
        this->get_pending_from_esid(actions, pending_sid, sid_pos);

        /* step 1.1.1 : add in pending sid list */
        if(false == pending_sid.empty()){
            this->m_pending_sid_pos.merge(pending_sid);
            this->m_pending_sid_pos.sort();
        }

        /* step 1.2 : del current <sid_pos> */
        /* <sid_pos> | current pending (sid_pos) */
        for(auto iter = this->m_pending_sid_pos.begin();
                 iter!= this->m_pending_sid_pos.end(); iter++){
            if(*iter == sid_pos){
                this->m_pending_sid_pos.erase(iter);
                break;
            }
        }

        /* step 1.3 : update scene(pruning) , and return 0 */
        if(-1 == this->pruning(scene)) return -1;

        /* step 1.4 : set this->m_sas used flag = true { sid_pos->action_set | this->m_sas } */
        this->set_used_flag(actions);

        {
            // for debug
            cout << "pending sid : ";
            for(auto sid : this->m_pending_sid_pos){
                cout << sid << " ";
            }
            cout << endl;

            cout << "m_sas : " << endl;
            int i = 0;
            for(auto &unit : this->m_sas){
                printf("%.4d : %s | ", unit.first, (unit.second ? "x" : "o"));
                if(++i % 10 == 0) cout << endl;
            }
            cout << endl;
        }
        return 0;
    }else{
        /* step 2 : else return -1 */
        return -1;
    }
}

/* is pending return 0 */
int  Filter::is_pending(void)
{
    if(false == this->m_pending_sid_pos.empty()){
        return 0;
    }else{
        return -1;
    }
}

int  Filter::generate_scenes_actionset(void)
{
    int ret = 0;

    /* step 1 : get top sid_pos -> action_set */
    auto got2 = get<1>(*this->m_sst->scene_unit_set).find(this->m_sid_pos_top);
    if(get<1>(*this->m_sst->scene_unit_set).end() == got2){
        cout << "filter add_scenes_action : error !" << endl;
        ret = -1;
    }
    else{
        /* step 2 : traversing */
        ret = this->add_scenes_action(this->m_sid_pos_top, get<1>(got2->second));
    }

    list<int> pending_sid;
    unordered_map<int, bool> actions; 

    /* step 1.1 : get next pending sid from current sid_pos */
    this->get_pending_from_esid(actions, pending_sid, this->m_sid_pos_top);

    /* step 1.1.1 : add in pending sid list */
    if(false == pending_sid.empty()){
        this->m_pending_sid_pos.merge(pending_sid);
        this->m_pending_sid_pos.sort();
    }

    return ret;
}

int  Filter::add_scenes_action(int sid_pos, const vector<int> &action_set)
{
    /* step 1 : traversing */

    int ret = 0;

    /* 
     *
     * tuple<int, int, vector<int> >  subscene, ||  <action, sceneid_pos, action-set>
     *
     * */

    /* <action, sceneid, action-set> */
    for(auto action : action_set){

        /* <action_pos, used> | used -> true
         * unordered_map<int, bool>
         * */
        this->m_sas.insert(unordered_map<int, bool>::value_type(action, false)); // ignore insert fault

        auto got = get<1>(*this->m_sst->action_trig_scene_set).find(action);

        if(get<1>(*this->m_sst->action_trig_scene_set).end() == got)   ret = 0;
        else{
            cout << ". . got->first : " << got->first ;
            cout << " got->second.size() : " << got->second.size() << endl;
            for(auto sid2 : got->second){

                auto got2 = get<1>(*this->m_sst->scene_unit_set).find(sid2);
                if(get<1>(*this->m_sst->scene_unit_set).end() == got2){
                    cout << "filter add_scenes_action : error !" << endl;
                    ret = -1;
                }
                else{
                    ret = this->add_scenes_action(sid2, get<1>(got2->second));
                }
            }
        }
    }

    return ret;
}

/* success return sid_pos ; fail return -1*/
int  Filter::step(int sid_pos)
{
    for(auto unit : this->m_pending_sid_pos){
        if(sid_pos == unit){
            cout << "step : sid_pos = unit" << endl;
            return 0;
        }
    }

    cout << "step : sid_pos != unit" << endl;
    return -1;
}

int  Filter::get_pending_from_esid(unordered_map<int, bool> &actions, list<int> &pending_sid, int sid_pos) /* from exec sid_pos */
{
    /* <sid_pos> | current pending (sid_pos)
     * list<int>
     * m_pending_sid_pos
     * */

    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> 
     * tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > >
     * */
    for(auto unit : get<1>(get<1>(*this->m_sst->scene_unit_set)[sid_pos]))
        actions.insert(unordered_map<int, bool>::value_type(unit, false));

    /* step 1 : filter this->m_sas */
    {
        /* <action_pos, used> | used -> true 
         * unordered_map<int, bool>
         * */
        size_t size =  this->m_sas.size();  //-------------
        for(auto &act : actions){           //            |
            act.second = this->m_sas[act.first]; //       |
        }                                   //            |
                                            //            |
        if(size != this->m_sas.size()) // if add new act <-
            cout << "this->m_sas ( scenes all actions set ) error !" << endl;
    }

    /* step 2 : search sid through action_pos */
    for(auto &unit : actions){
        if(false == unit.second){
            /* <cnt, <m_pos, vector<m_sceneid>> > 
             * tuple<int, unordered_map<int, vector<int>> > 
             * */
            auto got = get<1>(*this->m_sst->action_trig_scene_set).find(unit.first);
            if(got != get<1>(*this->m_sst->action_trig_scene_set).end()){
                for(auto sid : got->second){
                    pending_sid.push_back(sid);
                }
            }
        }
    }
    pending_sid.sort();
    pending_sid.unique();

    return 0;
}

int  Filter::pruning(scene_t &scene)
{
    if(-1 == this->pruning_actions(scene.result_devs)) return -1;

    if(-1 == this->pruning_scenes(scene.result_scenes)) return -1;

    return 0;
}

int  Filter::pruning_actions(vector<device_t> &r_result_devs)
{
    vector<int> del_devids; // vector<device_t.id>

    for(auto iter = r_result_devs.begin();
             iter!= r_result_devs.end(); iter++){

        int action = 0xffff;
        /* <cnt, <m_pos, <realtype, devid/sceneid, gateway, status>>> 
         * tuple<int, unordered_map<int, tuple<bool, int, string, string> > >
         * */
        for(auto &unit : get<1>(*this->m_sst->action_set)){
            if(true == get<0>(unit.second)){
                if(iter->id == get<1>(unit.second) &&
                   iter->gateway == get<2>(unit.second)){
                    action = unit.first;
                }
            }
        }

        if(0xffff != action){
            if(true == this->m_sas[action]){
                del_devids.push_back(iter->id);
            }
        }
    }

    for(auto id : del_devids){

        auto iter = r_result_devs.begin();

        for( ; iter != r_result_devs.end(); iter++) if(iter->id == id) break;

        if(iter != r_result_devs.end()) r_result_devs.erase(iter);
    }

    return 0;
}

int  Filter::pruning_scenes(vector<int> &r_result_scenes)
{
    return 0;
}

int  Filter::set_used_flag(unordered_map<int, bool> &actions)
{
    /* <action_pos, used> | used -> true 
     * unordered_map<int, bool>
     * */
    for(auto &unit : actions) this->m_sas[unit.first] = true;

    return 0;
}

Filter::~Filter()
{
}



