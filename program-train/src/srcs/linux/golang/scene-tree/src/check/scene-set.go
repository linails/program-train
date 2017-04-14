/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

func NewSceneSet() *SceneSet_t{
    return &SceneSet_t{}
}

type SceneSet_t struct{
    p_action_set            *actionSet_t
    p_scene_unit_set        *sceneUnitSet_t
    p_action_trig_scene_set *action_trig_SceneSet_t
    m_del_set                delSetPos_t
    m_filter_set             [] *Filter_t
}

func (this *SceneSet_t)Init_scene_set(vdevs []Device_t, vscenes []Scene_t) int{
    Log.Info()
    return 0
}

func (this *SceneSet_t)Infinite_loops_check(scene *Scene_t) int{
    Log.Info()
    InfiniteLoops()
    return 0
}

func (this *SceneSet_t)Del_scene(sceneid int) int{
    Log.Info()
    return 0
}

func (this *SceneSet_t)Reset_all_set(){

}

func (this *SceneSet_t)Print_all_set(){

}

func (this *SceneSet_t)add_actionunit(vdev []Device_t){

}

func (this *SceneSet_t)add_sceneunit(vscene []Scene_t){

}

func (this *SceneSet_t)del_sceneunit(sceneid int){

}

func (this *SceneSet_t)del_action_trig_scene(pos, sceneid_pos int){

}

func (this *SceneSet_t)del_vir_action(pos int){

}

func (this *SceneSet_t)del_pos(pos_type, pos int) int{
    return 0
}

// same as tuple<bool, int, string, string>
type devidSceneidInfo_t struct{
    realtype        bool
    devid_sceneid   int
    gateway         string
    status          string
}

// same as tuple<int, unordered_map<int, devidSceneidInfo_t>>
type actionSet_t struct{
    cnt             int
    ds_pos          map[int] devidSceneidInfo_t
}

// same as tuple<int, vector<int>, vector<int>, tuple<int, int>>
type sceneUnit_t struct{
    m_sceneid         int
    m_action_set      []int
    m_trig_action_set []int
    m_time            [2]int
}

// same as tuple<int, unordered_map<int, sceneUnit_t>>
type sceneUnitSet_t struct{
    cnt             int
    scene_pos       map[int] sceneUnit_t
}

// same as tuple<int, unordered_map<int, vector<int>>>
type action_trig_SceneSet_t struct{
    cnt             int
    action_trigs    map[int] []int
}

// same as tuple<list<{action_pos | action_set}>, list<sid_pos, scene_unit_set>>
type delSetPos_t struct{
    action_pos      []int
    sid_pos         []int
}
