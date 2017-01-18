/*
 * Progarm Name: msg.hpp
 * Created Time: 2017-01-17 10:22:52
 * Last modified: 2017-01-18 10:30:21
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MSG_HPP_
#define _MSG_HPP_

#include <string>
#include <vector>
#include <map>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using std::string;
using std::vector;
using std::map;
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
    MsgBindDevices(JsonMsg* msg) :msg(msg){
        m_objs_head.insert(map<const char *, string &>::value_type("method",        msg->m_method));
        m_objs_head.insert(map<const char *, string &>::value_type("ts",            msg->m_ts));
        m_objs_head.insert(map<const char *, string &>::value_type("ukey",          msg->m_ukey));
        m_objs_head.insert(map<const char *, string &>::value_type("platform",      msg->m_platform));
        m_objs_head.insert(map<const char *, string &>::value_type("proto_version", msg->m_proto_version));
        m_objs_head.insert(map<const char *, string &>::value_type("session",       msg->m_session));
    }
    ~MsgBindDevices(){}
    int    format_json_3060(void);
    int    format_json_3061(void);
    int    format_json_3062(void);
    int    format_json_3063(void);
    int    format_json_3064(void);
    int    format_json_3065(void);
    string to_json_3060(void);
    string to_json_3061(void);
    string to_json_3062(void);
    string to_json_3063(void);
    string to_json_3064(void);
    string to_json_3065(void);
public:
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

