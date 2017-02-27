/*
 * Progarm Name: disk-dic.hpp
 * Created Time: 2017-02-27 15:35:40
 * Last modified: 2017-02-27 15:39:12
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DISK_DIC_HPP_
#define _DISK_DIC_HPP_

#include <string>
#include <vector>

using std::string;
using std::vector;

class DiskDic{
public:
    DiskDic(string path);
    ~DiskDic();
private:
    string      m_path;
};

#endif //_DISK_DIC_HPP_

