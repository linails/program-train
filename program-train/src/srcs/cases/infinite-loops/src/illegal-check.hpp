
#ifndef _ILLEGAL_CHECK_HPP_
#define _ILLEGAL_CHECK_HPP_

#include "common.hpp"
#include <vector>
#include <tuple>
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

class IllegalCheck{
public:
    IllegalCheck();
    ~IllegalCheck();

    /* 
     * ret = 0 -> illegal !!!
     * */
    int  check(scene_t &r_scene);
private:
};

#endif //_ILLEGAL_CHECK_HPP_

