/*
 * Progarm Name: msg.cpp
 * Created Time: 2017-01-17 10:22:47
 * Last modified: 2017-02-09 14:10:08
 * @author: minphone.linails linails@foxmail.com 
 */

#include "msg.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::make_tuple;
using std::make_pair;

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

    if(msg->root.HasMember("body") && msg->root["body"].IsObject()){ // if - 1
        string name;
        list<tuple<int, string> > binddev_list;

        Value &body = msg->root["body"];

        if(body.HasMember("name") && body["name"].IsString()){
            name = body["name"].GetString();
            this->m_bind_name = name;

            if(body.HasMember("devices") && body["devices"].IsArray()){
                Value &devices = body["devices"];
                for(auto &dev : devices.GetArray()){
                    if(dev.HasMember("id") && dev["id"].IsInt() &&
                       dev.HasMember("gateway") && dev["gateway"].IsString()){
                        binddev_list.push_back(make_tuple(dev["id"].GetInt(), 
                                                          dev["gateway"].GetString()));
                    }
                }
            }
        }else{
            ret = -1;
        }

        m_binddev_set[name] = binddev_list;
    } // end if - 1

    return ret;
}

int    MsgBindDevices::format_json_3063(void)
{
    int ret = 0;

    if(msg->root.HasMember("body") && msg->root["body"].IsObject()){ // if - 1

        Value &body = msg->root["body"];

        if(body.HasMember("id") && body["id"].IsInt()){
            this->m_bind_gid = body["id"].GetInt();
        }else{
            ret = -1;
        }

    } // end if - 1

    return ret;
}

int    MsgBindDevices::format_json_3064(void)
{
    int ret = 0;

    if(msg->root.HasMember("body") && msg->root["body"].IsObject()){ // if - 1
        string name;
        list<tuple<int, string> > binddev_list;

        Value &body = msg->root["body"];

        if(body.HasMember("id") && body["id"].IsInt()){
            this->m_bind_gid = body["id"].GetInt();
        }

        if(body.HasMember("name") && body["name"].IsString()){
            name = body["name"].GetString();
            this->m_bind_name = name;

            if(body.HasMember("devices") && body["devices"].IsArray()){
                Value &devices = body["devices"];
                for(auto &dev : devices.GetArray()){
                    if(dev.HasMember("id") && dev["id"].IsInt() &&
                       dev.HasMember("gateway") && dev["gateway"].IsString()){
                        binddev_list.push_back(make_tuple(dev["id"].GetInt(), 
                                                          dev["gateway"].GetString()));
                    }
                }
            }
        }

        m_binddev_set[name] = binddev_list;
    } // end if - 1

    return ret;
}

int    MsgBindDevices::format_json_3065(void)
{
    int ret = 0;

    if(msg->root.HasMember("body") && msg->root["body"].IsObject()){ // if - 1

        Value &body = msg->root["body"];

        if(body.HasMember("id") && body["id"].IsInt()){
            this->m_bind_gid = body["id"].GetInt();
        }else{
            ret = -1;
        }

        if(body.HasMember("status") && body["status"].IsInt()){
            this->m_ctrl_status = body["status"].GetInt();
        }else{
            ret = -1;
        }

    } // end if - 1

    return ret;
}

string MsgBindDevices::to_json_3060(vector<BodyUnit_t> &objs_body)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
        /* body */
        writer.String("body");{
        writer.StartObject();{
            writer.String("binds");
            writer.StartArray();{   // StartArray ---- 1
                for(auto &body_unit : objs_body){
                    writer.StartObject();{
                        for(auto &unit : body_unit){
                            writer.String(unit.first);
                            switch(std::get<0>(unit.second)){
                            case 1: writer.Int(std::get<1>(unit.second));              break;
                            case 2: writer.String(std::get<2>(unit.second).c_str());   break;
                            case 3:
                                writer.StartArray();{   // StartArray ---- 2
                                for(auto &dev : *std::get<3>(unit.second)){
                                writer.StartObject();{
                                    for(auto &u : dev){
                                        writer.String(u.first);
                                        switch(std::get<0>(u.second)){
                                        case 1: writer.Int(std::get<1>(u.second));            break;
                                        case 2: writer.String(std::get<2>(u.second).c_str()); break;
                                        }
                                    }
                                } writer.EndObject();
                                }
                                } writer.EndArray();    // EndArray ---- 2
                                break;
                            }
                        }
                    } writer.EndObject();
                }
            } writer.EndArray(); // EndArray ---- 1
        } writer.EndObject();
        }
        
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string MsgBindDevices::to_json_3061(vector<devUnit_t> &objs_body)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
        /* body */
        writer.String("body");{
        writer.StartObject();{
            writer.String("devices");
            writer.StartArray();{   // StartArray ---- 1
                for(auto &body_unit : objs_body){
                    writer.StartObject();{
                        for(auto &u : body_unit){
                            writer.String(u.first);
                            switch(std::get<0>(u.second)){
                            case 1: writer.Int(std::get<1>(u.second));            break;
                            case 2: writer.String(std::get<2>(u.second).c_str()); break;
                            }
                        }
                    } writer.EndObject();
                }
            } writer.EndArray(); // EndArray ---- 1
        } writer.EndObject();
        }
        
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string MsgBindDevices::to_json_3062(vector<devUnit_t> &objs_body, bool tf)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
        if(false == tf){
            /* body */
            writer.String("body");{
            writer.StartObject();{
                writer.String("name");
                writer.String(this->m_bind_name.c_str());
                writer.String("devices");
                writer.StartArray();{   // StartArray ---- 1
                    for(auto &body_unit : objs_body){
                        writer.StartObject();{
                            for(auto &u : body_unit){
                                writer.String(u.first);
                                switch(std::get<0>(u.second)){
                                case 1: writer.Int(std::get<1>(u.second));            break;
                                case 2: writer.String(std::get<2>(u.second).c_str()); break;
                                }
                            }
                        } writer.EndObject();
                    }
                } writer.EndArray(); // EndArray ---- 1
            } writer.EndObject();
            }
        }
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string MsgBindDevices::to_json_3063(void)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string MsgBindDevices::to_json_3064(vector<devUnit_t> &objs_body, bool tf)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }

        if(false == tf){
            /* body */
            writer.String("body");{
            writer.StartObject();{
                writer.String("id");
                writer.Int(this->m_bind_gid);
                writer.String("name");
                writer.String(this->m_bind_name.c_str());
                writer.String("devices");
                writer.StartArray();{   // StartArray ---- 1
                    for(auto &body_unit : objs_body){
                        writer.StartObject();{
                            for(auto &u : body_unit){
                                writer.String(u.first);
                                switch(std::get<0>(u.second)){
                                case 1: writer.Int(std::get<1>(u.second));            break;
                                case 2: writer.String(std::get<2>(u.second).c_str()); break;
                                }
                            }
                        } writer.EndObject();
                    }
                } writer.EndArray(); // EndArray ---- 1
            } writer.EndObject();
            }
        }
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string MsgBindDevices::to_json_3065(void)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string  MsgBindDevices::to_json_3066(void)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
        /* body */
        writer.String("body");{
        writer.StartObject();{
            writer.String("id");
            writer.Int(this->m_bind_gid);
            writer.String("status");
            writer.Int(this->m_ctrl_status);
        } writer.EndObject();
        }
        
    }writer.EndObject();

    ret = buffer.GetString();

    return ret;
}

string  MsgBindDevices::to_json_3003(devUnit_t &objs_body)
{
    string ret;

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    writer.StartObject();{
        /* head */
        writer.String("head");{
            writer.StartObject();{
                for(auto &objs_head : this->m_objs_head){
                    writer.String(objs_head.first);
                    writer.String(objs_head.second.c_str());
                }
                writer.String("status");
                writer.Int(msg->m_status);
            } writer.EndObject();
        }
        /* body */
        writer.String("body");{
        writer.StartObject();{
            writer.String("device");
            writer.StartObject();{
                for(auto &u : objs_body){
                    writer.String(u.first);
                    switch(std::get<0>(u.second)){
                    case 1: writer.Int(std::get<1>(u.second));            break;
                    case 2:
                        if(string(u.first) != "command"){
                            writer.String(std::get<2>(u.second).c_str()); 
                        }else{
                            writer.StartObject();{
                                writer.String("onoff");
                                if(std::get<2>(u.second) == "on")
                                    writer.Int(1);
                                else
                                    writer.Int(0);
                            } writer.EndObject();
                        }
                        break;
                    }
                }
            } writer.EndObject();
        } writer.EndObject();
        }
        
    }writer.EndObject();

    ret = buffer.GetString();

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
    vector<MsgBindDevices::BodyUnit_t> objs_body;
    {
    }

    /* 
     * Out msg
     * */
    string ret_msg = msg_bind_devices->to_json_3060(objs_body);

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


