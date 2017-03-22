/*
 * @author: minphone.linails linails@foxmail.com 
 */

package check

func Check(){
    Log.Info(" - Check -")

    sst := NewSceneSet()

    Log.Info("sst : ", sst)

    var vdevs []Device_t
    var vscenes []Scene_t

    // init scenes 
    sst.Init_scene_set(vdevs, vscenes)

    var scene Scene_t

    // check
    sst.Infinite_loops_check(&scene)
}

