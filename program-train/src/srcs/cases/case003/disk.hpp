/*
 * Progarm Name: disk.hpp
 * Created Time: 2017-01-16 11:13:02
 * Last modified: 2017-01-16 17:19:31
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _DISK_HPP_
#define _DISK_HPP_

#include <string>
#include "pqxx/pqxx"
#include "kb-common.hpp"
#include <vector>

using std::string;
using std::vector;

class Disk{
public:
    Disk();
    ~Disk();
    int  insert_bind_items(void);
    int  select_bind_items(vector<BindItem_t> &v_item, int id);
    int  select_bind_items(vector<BindItem_t> &v_item, string &name);
    int  delete_bind_items(int id);
    int  update_bind_items(int id, int status);
private:
    int  create_table(void);
private:
    pqxx::connection   *m_pqxx = NULL;
};

#endif //_DISK_HPP_

