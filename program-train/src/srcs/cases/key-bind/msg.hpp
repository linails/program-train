/*
 * Progarm Name: msg.hpp
 * Created Time: 2017-01-17 10:22:52
 * Last modified: 2017-02-09 13:56:09
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSG_HPP_
#define _MSG_HPP_

#include <string>
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include "kb-common.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using std::string;
using std::vector;
using std::map;
using std::list;
using std::tuple;
using namespace rapidjson;

struct JsonMsg{
    virtual int     format_json(char *buf, int len);
    virtual string  to_json(void);
public:
    string  m_method;
    string  m_ts;
    string  m_ukey;
    string  m_platform;
    string  m_proto_version;
    string  m_session;
    int     m_status;
    char   *payload;
    int     payloadlen;
    Document    document;
    Value  &root = document;
};

/* 
 * bind-devices : 3060 - 3065
 * */
struct MsgBindDevices{
    /*                        tuple< 0    1     2   > > */
    typedef map<const char *, tuple<int, int, string> > devUnit_t;
    /*                        tuple< 0    1     2         3      > > */
    typedef map<const char *, tuple<int, int, string, vector<devUnit_t> *> > BodyUnit_t;
    typedef map<string, list<tuple<int, string> > > BindDeviceSet_t;
    MsgBindDevices(JsonMsg* msg) :msg(msg){
        m_objs_head.insert(map<const char *, string &>::value_type("method",        msg->m_method));
        m_objs_head.insert(map<const char *, string &>::value_type("ts",            msg->m_ts));
        m_objs_head.insert(map<const char *, string &>::value_type("ukey",          msg->m_ukey));
        m_objs_head.insert(map<const char *, string &>::value_type("platform",      msg->m_platform));
        m_objs_head.insert(map<const char *, string &>::value_type("proto_version", msg->m_proto_version));
        m_objs_head.insert(map<const char *, string &>::value_type("session",       msg->m_session));
        m_bind_gid = 0;
    }
    ~MsgBindDevices(){}
    int    format_json_3060(void);
    int    format_json_3061(void);
    int    format_json_3062(void);
    int    format_json_3063(void);
    int    format_json_3064(void);
    int    format_json_3065(void);
    string  to_json_3060(vector<BodyUnit_t> &objs_body);
    string  to_json_3061(vector<devUnit_t> &objs_body);
    string  to_json_3062(vector<devUnit_t> &objs_body, bool tf = true);
    string  to_json_3063(void);
    string  to_json_3064(vector<devUnit_t> &objs_body, bool tf = true);
    string  to_json_3065(void);
    string  to_json_3066(void);
    string  to_json_3003(devUnit_t &objs_body);
public:
    vector<BindItem_t>          m_vitems;
    list<device_item>           m_dev_items;
    BindDeviceSet_t             m_binddev_set;
    int                         m_bind_gid;
    string                      m_bind_name;
    int                         m_ctrl_status;
    JsonMsg*                    msg = NULL;
    map<const char *, string &> m_objs_head;
};

class Msg{
public:
    Msg();
    ~Msg();
    int  process_3060_msg_v2(JsonMsg *msg); // - bind-devices
    int  process_3061_msg_v2(JsonMsg *msg); // - bind-devices
    int  process_3062_msg_v2(JsonMsg *msg); // - bind-devices
    int  process_3063_msg_v2(JsonMsg *msg); // - bind-devices
    int  process_3064_msg_v2(JsonMsg *msg); // - bind-devices
    int  process_3065_msg_v2(JsonMsg *msg); // - bind-devices
private:
};

#endif //_MSG_HPP_

