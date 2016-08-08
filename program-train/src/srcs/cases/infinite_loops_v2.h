/*
 * Progarm Name: infinite_loops_v2.h
 * Created Time: 2016-08-02 15:02:12
 * Last modified: 2016-08-08 16:52:04
 */

#ifndef _INFINITE_LOOPS_V2_H_
#define _INFINITE_LOOPS_V2_H_

#include <vector>
#include "common.h"
#include <tuple>
#include <unordered_map>
#include <string>

using std::vector;
using std::tuple;
using std::unordered_map;
using std::string;

class ActionUnitv2;
class SceneUnitv2;
class SceneSetv2;

/* scene1 / scene2 / ... 
 *
 * example :
 * {
 *   vector<device_t> vdev;
 *   vector<scene_t> vscene;
 *
 *   SceneSetv2  ss(vdev, vscene);
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
class SceneSetv2{
public:
    SceneSetv2(vector<device_t> &r_vdev, vector<scene_t> &r_vscene);
    ~SceneSetv2();
    int  infinite_loops_check(scene_t &r_scene);    /* aim */
    void reset_all_set(void);
    void print_all_set(void);
private:
    int  get_action_pos(device_t &r_dev);
    int  get_scene_unit_pos(scene_t &r_scene);
    void add_actionunit(vector<device_t> &r_vdev);
    void add_sceneunit(vector<scene_t> &r_vscene);
    void del_sceneunit(scene_t &r_scene);
    void del_action_trig_scene(int pos, int sceneid_pos);
    void del_vir_action(int pos); /* pos : vir_action */
private:
    friend class ActionUnitv2;
    friend class SceneUnitv2;

    /* <cnt, <m_pos, <realtype, devid/sceneid, gateway>>> */
    typedef tuple<int, unordered_map<int, tuple<bool, int, string> > > ActionSet_t;
    ActionSet_t  *action_set;

    /* <cnt, <m_pos, <m_sceneid, m_action_set, m_trig_action_set, m_time>>> */
    typedef tuple<int, unordered_map<int, tuple<int, vector<int>, vector<int>, tuple<int, int> > > > SceneUnitSet_t;
    SceneUnitSet_t *scene_unit_set;

    /* <cnt, <m_pos, vector<m_sceneid>> > */
    typedef tuple<int, unordered_map<int, vector<int>> > Action_Trig_SceneSet_t;
    Action_Trig_SceneSet_t *action_trig_scene_set;
};

#endif //_INFINITE_LOOPS_V2_H_

