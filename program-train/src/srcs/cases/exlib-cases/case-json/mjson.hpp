/*
 * Progarm Name: mjson.hpp
 * Created Time: 2016-12-22 09:01:01
 * Last modified: 2017-01-19 20:26:02
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MJSON_HPP_
#define _MJSON_HPP_

class mJson{
public:
    mJson();
    ~mJson();
    int  mjson_main(int argc, char **argv);
private:
    int  json_rapidjson(void);
    int  json_cppjson(void);
    int  rapidjson_read(void);
    int  rapidjson_write(void);
    int  rapidjson_advanced(void);
};

#endif //_MJSON_HPP_

