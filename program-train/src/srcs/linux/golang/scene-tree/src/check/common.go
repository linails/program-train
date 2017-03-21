/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type Device_t struct{
    id      int
    gateway string
    status  string
}

type Defense_t struct{
    id      int
    alarm   int
}

type Scene_t struct{
    id                  int
    name                string
    time                int
    timetype            int
    onoff               int     // scene onoff
    condition_devs      []Device_t
    condition_scenes    []int
    condition_defense   []Defense_t
    result_devs         []Device_t
    result_scenes       []int
    result_defense      []Defense_t
    recover_devs        []Device_t
    recover_scenes      []int
    recover_defense     []Defense_t
}
