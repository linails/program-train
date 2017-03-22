/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

type DeviceTsl_t struct{
    id      int         // = dev_pos
    status  string
}

type SceneTsl_t struct{
    id                  int
    time                int
    timetype            int
    condition           []DeviceTsl_t
    result              []DeviceTsl_t
    recover             []DeviceTsl_t
}

