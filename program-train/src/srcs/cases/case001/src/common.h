/*
 * Progarm Name: common.h
 * Created Time: 2016-07-27 13:11:34
 * Last modified: 2016-11-10 14:33:30
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

typedef struct{
    int     id;
    string  gateway;
    string  status;
}device_t;

typedef struct{
    string gateway;
    int    alarm;    /* alarm - status : On[1], off[0] */
}defense_t;

typedef struct {
    int     id;
    string  name;
    int     time;
    int     timetype; /* 1 timing;  2 delay */
    int     onoff;
    vector<device_t>    condition_devs;
    vector<int>         condition_scenes;
    vector<defense_t>   condition_defense;  //
    vector<device_t>    result_devs;
    vector<int>         result_scenes;
    vector<defense_t>   result_defense;     //
    vector<device_t>    recover_devs;
    vector<int>         recover_scenes;
    vector<defense_t>   recover_defense;    //
}scene_t;

#endif //_COMMON_H_

