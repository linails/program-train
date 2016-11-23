/*
 * Progarm Name: normal.hpp
 * Created Time: 2016-11-23 21:53:14
 * Last modified: 2016-11-23 22:20:50
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _NORMAL_HPP_
#define _NORMAL_HPP_

class NormalDB {
public:
    NormalDB();
    ~NormalDB();
    int generic_insert(void);
    int bulk_insert(void);
    int get_schema(void);
    int query(void);
private:
    char *strlwr(char *str);
};

#endif //_NORMAL_HPP_

