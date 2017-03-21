/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type devInfo_t struct{
    realtype        bool
    sceneid         int
    realdev        *Device_t
}

type ActionUnit_t struct{
    m_pos           int
    m_device        devInfo_t
    m_sst          *SceneSet_t
}

func (this *ActionUnit_t)Init_action_unit_dev(sst *SceneSet_t, dev *Device_t){

}

func (this *ActionUnit_t)Init_action_unit_sceneid(sst *SceneSet_t, sceneid int){

}

func (this *ActionUnit_t)Get_pos() int{
    return 0
}

func (this *ActionUnit_t)Get_realtype() int{
    return 0
}

func (this *ActionUnit_t)add2set(){

}

func (this *ActionUnit_t)is_exist() int{
    return 0
}

func (this *ActionUnit_t)generate_pos() int{
    return 0
}
