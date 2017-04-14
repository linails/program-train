/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type Filter_t struct{
    m_sid_pos_top       int
    m_sst               *SceneSet_t
    m_sas               map[int] bool /* <action_pos, used> | used -> true */
    m_pending_sid_pos   []int /* <sid_pos> | current pending (sid_pos) */
}

func (this *Filter_t)Init_filter(sst *SceneSet_t, sid_pos int){

}

func (this *Filter_t)Filtering(scene *Scene_t, sid_pos int) int {
    return 0
}

func (this *Filter_t)Is_pending() int{
    return 0
}

func (this *Filter_t)filtering(sid_pos int) int{
    return 0
}

func (this *Filter_t)generate_scenes_actionset() int{
    return 0
}

func (this *Filter_t)add_scenes_action(sid_pos int, action_set []int) int{
    return 0
}

func (this *Filter_t)step(sid_pos int) int{
    return 0
}

func (this *Filter_t)get_pending_from_esid(
                            actions map[int]bool,
                            pending_sid []int,
                            sid_pos int) int{
    return 0
}

func (this *Filter_t)pruning(scene *Scene_t) int{
    return 0
}

func (this *Filter_t)pruning_actions(result_devs []Device_t)int{
    return 0
}

func (this *Filter_t)pruning_scenes(result_scenes []int)int{
    return 0
}

func (this *Filter_t)set_used_flag(actions map[int]bool) int{
    return 0
}

