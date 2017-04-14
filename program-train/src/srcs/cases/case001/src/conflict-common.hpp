/*
 * Progarm Name: conflict-common.hpp
 * Created Time: 2017-03-23 14:11:52
 * Last modified: 2017-03-23 17:17:32
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _CONFLICT_COMMON_HPP_
#define _CONFLICT_COMMON_HPP_

#include <string>

using std::string;

/* 
 * devict_t -> device_tsl_t
 * defense_t -> device_tsl_t
 * */
typedef struct DeviceTsl{
    int     id;
    string  status;
}device_tsl_t;

typedef int key_t;

struct btNode{
    btNode():m_left(NULL), m_right(NULL){};
    btNode(key_t key, int time, string &status, btNode *l = NULL, btNode *r = NULL)
        :m_left(l) ,m_right(r) ,m_key(key) ,m_time(time) ,m_status(status){};
public:
    btNode    *m_left   = nullptr;
    btNode    *m_right  = nullptr;
    key_t      m_key    = -1;
    int        m_time   = -1;
    string     m_status;
};

#endif //_CONFLICT_COMMON_HPP_

