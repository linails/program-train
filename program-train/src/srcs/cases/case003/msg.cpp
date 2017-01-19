/*
 * Progarm Name: msg.cpp
 * Created Time: 2017-01-17 10:22:47
 * Last modified: 2017-01-18 10:37:07
 * @author: minphone.linails linails@foxmail.com 
 */

#include "msg.hpp"
#include <iostream>

using std::cout;
using std::endl;

int     JsonMsg::format_json(char *buf, int len)
{
    int ret = 0;

    if(NULL == buf || 0 >= len){
        cout << "[Error] : buf is null" << endl;
        ret = -1;
    }else{
        this->payload   = buf;
        this->payloadlen= len;
        document.Parse((char*)buf);

        if(document.HasParseError()){
            cout << "[Error] : wrong json string : " << buf << endl;
            ret = -1;
            return ret;
        }

        if(root.HasMember("head") && root["head"].IsObject()){
            Value& head = root["head"];

            const char *objs[] = {
                "method",       // 0
                "ts",           // 1
                "ukey",         // 2
                "session",      // 3
                "proto_version" // 4
            };

            if(head.HasMember(objs[0]) && head[objs[0]].IsString()) this->m_method       = head[objs[0]].GetString();
            if(head.HasMember(objs[1]) && head[objs[1]].IsString()) this->m_ts           = head[objs[1]].GetString();
            if(head.HasMember(objs[2]) && head[objs[2]].IsString()) this->m_ukey         = head[objs[2]].GetString();
            if(head.HasMember(objs[3]) && head[objs[3]].IsString()) this->m_session      = head[objs[3]].GetString();
            if(head.HasMember(objs[4]) && head[objs[4]].IsString()) this->m_proto_version= head[objs[4]].GetString();
        }
    }

    return ret;
}

string  JsonMsg::to_json(void)
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        writer.String("head");
        writer.StartObject(); {
            const char *objs[] = {
                "ts",           // 0
                "ukey",         // 1
                "status",       // 2
                "method",       // 3
                "session",      // 4
                "proto_version" // 5
            };

            writer.String(objs[0]); writer.String(this->m_ts.c_str());
            writer.String(objs[1]); writer.String(this->m_ukey.c_str());
            writer.String(objs[2]); writer.Int(this->m_status);
            writer.String(objs[3]); writer.String(this->m_method.c_str());

            if((0 != this->m_method.compare("1012")) || (0 == this->m_method.compare("")) ){
            writer.String(objs[4]); writer.String(this->m_session.c_str()); }

            writer.String(objs[5]); writer.String(this->m_proto_version.c_str());
        } writer.EndObject();
    } writer.EndObject();

    string msg(buffer.GetString());

    return msg;
}

int    MsgBindDevices::format_json_3060(void)
{
    return 0;
}

int    MsgBindDevices::format_json_3061(void)
{
    int ret = 0;
    return ret;
}

int    MsgBindDevices::format_json_3062(void)
{
    int ret = 0;
    return ret;
}

int    MsgBindDevices::format_json_3063(void)
{
    int ret = 0;
    return ret;
}

int    MsgBindDevices::format_json_3064(void)
{
    int ret = 0;
    return ret;
}

int    MsgBindDevices::format_json_3065(void)
{
    int ret = 0;
    return ret;
}

string MsgBindDevices::to_json_3060(void)
{
    string ret;
    return ret;
}

string MsgBindDevices::to_json_3061(void)
{
    string ret;
    return ret;
}

string MsgBindDevices::to_json_3062(void)
{
    string ret;
    return ret;
}

string MsgBindDevices::to_json_3063(void)
{
    string ret;
    return ret;
}

string MsgBindDevices::to_json_3064(void)
{
    string ret;
    return ret;
}

string MsgBindDevices::to_json_3065(void)
{
    string ret;
    return ret;
}

Msg::Msg()
{
}

Msg::~Msg()
{
}

int  Msg::process_3060_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;

    /* 
     * In msg
     * */
    MsgBindDevices *msg_bind_devices = new MsgBindDevices(msg);

    if (0 != (ret_code = msg_bind_devices->format_json_3060())){
        msg_bind_devices->msg->m_status = ret_code;
        return ret_code;
    }

    /* 
     * Get bind-devices-items
     * */
    string session = msg_bind_devices->msg->m_session;
    {
    }

    /* 
     * Out msg
     * */
    string ret_msg = msg_bind_devices->to_json_3060();

    cout << "3060 bind-devices : " << session << ":" << ret_msg << endl;

    return ret_code;
}

int  Msg::process_3061_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;
    return ret_code;
}

int  Msg::process_3062_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;
    return ret_code;
}

int  Msg::process_3063_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;
    return ret_code;
}

int  Msg::process_3064_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;
    return ret_code;
}

int  Msg::process_3065_msg_v2(JsonMsg *msg) // - bind-devices
{
    int ret_code = 0;
    return ret_code;
}


