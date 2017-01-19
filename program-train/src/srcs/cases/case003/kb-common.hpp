/*
 * Progarm Name: kb-common.hpp
 * Created Time: 2017-01-16 16:10:18
 * Last modified: 2017-01-16 16:30:32
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

#endif //_KB_COMMON_HPP_

