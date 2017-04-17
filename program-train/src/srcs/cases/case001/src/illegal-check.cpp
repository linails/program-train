
#include "illegal-check.hpp"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

IllegalCheck::IllegalCheck()
{
}

IllegalCheck::~IllegalCheck()
{
}

/* 
 * ret = 0 -> illegal !!!
 * */
int  IllegalCheck::check(scene_t &r_scene)
{

    for(auto &dev : r_scene.condition_devs){
        auto isexist = [&dev](device_t unit){
            if((dev.id == unit.id) && (dev.gateway == unit.gateway)){
                /* exist */
                return 1;
            }else{
                return 0;
            }
        };

        auto fi = find_if(r_scene.result_devs.begin(),
                          r_scene.result_devs.end(), isexist);
        if(fi != r_scene.result_devs.end()){
            return 0;
        }
    }

    for(auto id : r_scene.condition_scenes){
        auto isexist = [&id](int sid){
            if(id == sid){
                /* exist */
                return 1;
            }else{
                return 0;
            }
        };

        auto fi = find_if(r_scene.result_scenes.begin(),
                          r_scene.result_scenes.end(), isexist);
        if(fi != r_scene.result_scenes.end()){
            return 0;
        }
    }

    for(auto &def : r_scene.condition_defense){
        auto isexist = [&def](defense_t unit){
            if(def.id == unit.id){
                /* exist */
                return 1;
            }else{
                return 0;
            }
        };

        auto fi = find_if(r_scene.result_defense.begin(),
                          r_scene.result_defense.end(), isexist);
        if(fi != r_scene.result_defense.end()){
            return 0;
        }
    }

    return -1;
}

