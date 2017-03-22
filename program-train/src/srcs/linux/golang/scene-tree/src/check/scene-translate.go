/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type SceneTranslate_t struct{
    m_dev_set_first             map[Device_t] DeviceTsl_t
    m_dev_set_second            map[DeviceTsl_t] Device_t 
    m_dev_set_def_first         map[Device_t] Defense_t
    m_dev_set_def_second        map[Defense_t] Device_t 
    m_secenes_set_first         map[SceneTsl_t] Scene_t
    m_secenes_set_second        map[Scene_t] SceneTsl_t
}
