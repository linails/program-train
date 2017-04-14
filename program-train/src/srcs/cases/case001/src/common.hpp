/*
 * Progarm Name: common.hpp
 * Created Time: 2017-02-16 14:38:53
 * Last modified: 2017-02-17 15:28:47
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include "common.h"

typedef struct {
    int    id;
    string name;
    int devid;
    string gateway;
    int status;
}BindItem_t;

typedef struct{
    string gwid;
    string gwname;
    string gwtype;
    int	   gid;
    string gname;
    int    id;
    string exid;
    string name;
    int    type;
    int    zonetype;
    int    added;
    int    stamp;
    string mac;
    string status;
    int    offline;
    string clusterid;
}device_item;

#endif //_COMMON_HPP_

