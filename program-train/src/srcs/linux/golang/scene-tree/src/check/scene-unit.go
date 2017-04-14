/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type SceneUnit_t struct{
    m_pos               int /* eg.pos = 3 :bitset: 000001000 */
    m_sceneid           int
    m_time              [2]int  /* <type, time> : {type | 1 timeing : 2 delay} */
    m_action_set        []int
    m_trig_action_set   []int
    m_sst               *SceneSet_t
}

func (this *SceneUnit_t)Init_sceneunit_sceneid(sst *SceneSet_t, sceneid int){

}

func (this *SceneUnit_t)Init_sceneunit_scene(sst *SceneSet_t, scene *Scene_t){

}

func (this *SceneUnit_t)Get_pos() int{
    return 0
}

func (this *SceneUnit_t)Ring_check() int{
    return 0
}

func (this *SceneUnit_t)add_action_au(au *ActionUnit_t) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add_action_dev(dev *Device_t) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add_action_sid(sceneid int) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add_trig_au(au *ActionUnit_t) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add_trig_dev(dev *Device_t) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add_trig_sid(sceneid int) *SceneUnit_t{
    return this
}

func (this *SceneUnit_t)add2set(){

}

func (this *SceneUnit_t)is_exist() int{
    return 0
}

func (this *SceneUnit_t)generate_pos() int{
    return 0
}

func (this *SceneUnit_t)add_action_trig_scene(){

}

func (this *SceneUnit_t)add_action_trig_scene_vir_action(vir_action int){

}

func (this *SceneUnit_t)add_action_vir(sid, action int){

}

func (this *SceneUnit_t)add_trig_vir(sid, action int){

}

type subscene_t struct{
    action      int
    sid_pos     int
    action_set  []int
}

func (this *SceneUnit_t)ring_check(timing int, subscene subscene_t, sid int) int{
    return 0
}

