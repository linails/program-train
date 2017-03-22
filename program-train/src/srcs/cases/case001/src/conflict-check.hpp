/*
 * Progarm Name: conflict-check.hpp
 * Created Time: 2017-03-22 10:15:01
 * Last modified: 2017-03-22 11:04:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CONFLICT_CHECK_HPP_
#define _CONFLICT_CHECK_HPP_

#include <vector>
#include "common.hpp"
#include <tuple>
#include <unordered_map>
#include <string>
#include <list>
#include <map>

using std::vector;
using std::tuple;
using std::unordered_map;
using std::string;
using std::list;
using std::hash;
using std::map;

/* 
 * devict_t -> device_tsl_t
 * defense_t -> device_tsl_t
 * */
typedef struct{
    int     id;
    string  status;
}device_tsl_t;

/* 
 * scene_t -> scene_tsl_t
 * */
typedef struct{
    int                     id;
    int                     time;
    int                     timetype; /* 1 timing;  2 delay */
    list<device_tsl_t>      conditions;
    list<device_tsl_t>      results;
    list<device_tsl_t>      recovers;
}scene_tsl_t;

//----------------------------------------------------------

class ConflictCheck{
public:
    ConflictCheck();
    ~ConflictCheck();
private:
private:
    list<device_tsl_t>      m_dev_set;  // all dev_tsl set
};

#endif //_CONFLICT_CHECK_HPP_

