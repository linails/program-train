/*
 * Progarm Name: kb-common.hpp
 * Created Time: 2017-01-16 16:10:18
 * Last modified: 2017-02-09 14:15:53
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _KB_COMMON_HPP_
#define _KB_COMMON_HPP_

#include <string>

using std::string;

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

#endif //_KB_COMMON_HPP_

