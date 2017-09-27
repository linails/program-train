/*
 * Progarm Name: mjson.cpp
 * Created Time: 2016-12-22 09:00:56
 * Last modified: 2017-09-27 10:31:21
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mjson.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include <map>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <list>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::pair;
using std::tuple;
using std::make_pair;
using std::make_tuple;
using std::vector;
using std::unordered_map;
using std::list;

using namespace rapidjson;

mJson::mJson()
{
}

mJson::~mJson()
{
}

int  mJson::mjson_main(int argc, char **argv)
{
    int ret = 0;

    ret = this->json_rapidjson();

    ret = this->json_cppjson();

    return ret;
}

/* 
 * rapidjson.org/zh-ch/md_doc_tutorial_8zh-cn.html
 * */
int  mJson::json_rapidjson(void)
{
    int ret = 0;

    cout << "---------------------------" << endl;
    {
        const char *json = "{\"project\":\"rapidjosn\",\"stars\":10}";
        Document d;

        d.Parse(json);

        Value& s = d["stars"];
        s.SetInt(s.GetInt() + 1);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        d.Accept(writer);

        cout << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        printf("Lu//a\"\n");
        Document document;

        Document::AllocatorType& allocator = document.GetAllocator();
        Value contact(kArrayType);
        Value contact2(kArrayType);
        Value root(kArrayType);
        contact.PushBack("Lu//a\"",allocator).PushBack("Mio",allocator).PushBack("",allocator);
        contact2.PushBack("Lu// a\"",allocator).PushBack("Mio",allocator).PushBack("",allocator);
        root.PushBack(contact,allocator);
        root.PushBack(contact2,allocator);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        root.Accept(writer);
        string reststring = buffer.GetString();
        cout << reststring << endl;
    }
    cout << "---------------------------" << endl;
    {
        Document document;
        Document::AllocatorType& allocator = document.GetAllocator();
        Value root(kObjectType);

        Value storage_phone_count(kStringType);
        string storage_phone_count_str("49");
        storage_phone_count.SetString(storage_phone_count_str.c_str(),
                storage_phone_count_str.size(),allocator);

        Value storage_music_count(kStringType);
        string storage_music_count_str("48");
        storage_music_count.SetString(storage_music_count_str.c_str(),
                storage_music_count_str.size(),allocator);

        root.AddMember("storage.photo.count",storage_phone_count,allocator);
        root.AddMember("storage.music.count",storage_music_count,allocator);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        root.Accept(writer);
        string result = buffer.GetString();
        cout << "result : " << result << "--------:" << result.size() << endl;

        cout << "------------ parse json ------------" << endl;
        if(document.Parse<0>(result.c_str()).HasParseError()){
            cout << "error" << endl;
        }

        assert(document.HasMember("storage.music.count"));
        cout << document["storage.music.count"].GetString() << endl;

        cout << "------------ enum object ------------" << endl;
        Document::MemberIterator iter = document.MemberBegin();
        for(; iter!= document.MemberEnd(); ++iter){
            const char *name = iter->name.GetString();
            const char *value = iter->value.GetString();
            cout << name << ":" << value << endl;
        }
    }
    cout << "---------------------------" << endl;
    {
        string info = "{\"id\":\"1111111\",\"cards\":[0,1,2,3,4,5,6,7,8,9],\"jiaoDiZhu\":\"\"}";

        Document doc;
        doc.Parse<0>(info.c_str());

        Value &dataArray = doc["cards"];

        if(dataArray.IsArray()){
            for(SizeType i = 0; i< dataArray.Size(); i++){
                const Value &object = dataArray[i];
                printf("%d\n",object.GetInt());
            }
        }
    }
    cout << "---------------------------" << endl;
    {
        //read json
        string updateInfo = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}";

        Document doc;
        doc.Parse<0>(updateInfo.c_str());

        Value &dataArray = doc["UpdateInfo"];

        if(dataArray.IsArray()){
            for(unsigned i = 0; i < dataArray.Size(); i++){
                const Value &object = dataArray[i];

                string url = object["url"].GetString();
                string platform = object["platform"].GetString();
                cout << "url : " << url << endl;
                cout << "platform : " << platform << endl;
            }
        }

        cout << " write json ..." << endl;

        Document document;
        
        document.SetObject();

        Document::AllocatorType &allocator = document.GetAllocator();

        Value array(kArrayType);

        for(int i = 0; i < 10; i++){
            Value object(kObjectType);
            object.AddMember("id",1,allocator);
            object.AddMember("name","test",allocator);
            object.AddMember("version",1.01,allocator);
            object.AddMember("vip",true,allocator);

            object.SetInt(i);
            array.PushBack(object,allocator);
        }

        document.AddMember("title","PLAYER INFO",allocator);
        document.AddMember("players",array,allocator);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);

        auto out = buffer.GetString();

        cout << "buffer : " << out << endl;
    }
    cout << "---------------------------" << endl;
    {
        char json[] = "{\"carriorName\":\"japan comucation\",\"deviceName\":\"iPhane5,2\",\"osName\":\"android\",\"osVersion\":\"8.1\",\"appId\":\"com.mmcshadow.doudizhu\",\"versionName\":\"1.0\",\"versionCode\":\"1.0\",\"deviceId\":\"11111111\"}";

        Document d;
        d.Parse<0>(json);
        printf("%s\n",d["carriorName"].GetString());
        printf("%s\n",json);
    }
    cout << "---------------------------" << endl;
    {
        Document document;
        Document::AllocatorType &allocator = document.GetAllocator();

        Value root(kObjectType);
        root.AddMember("name","minphone",allocator);
        root.AddMember("gold",1234,allocator);

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        root.Accept(writer);

        string s = buffer.GetString();

        cout << s << endl;
    }

    ret = this->rapidjson_read(); assert(-1 != ret);

    ret = this->rapidjson_write(); assert(-1 != ret);

    ret = this->rapidjson_advanced(); assert(-1 != ret);

    return ret;
}

int  mJson::json_cppjson(void)
{
    int ret = 0;

    return ret;
}

int  mJson::rapidjson_read(void)
{
    int ret = 0;

    cout << "---------------------------" << endl;
    {
        const char *json = "{\"hello\":\"world\","
                           "\"t\": true,"
                           "\"f\": false,"
                           "\"n\": null,"
                           "\"i\": 123,"
                           "\"pi\": 3.1455,"
                           "\"a\":[1,2,3,4]}";

        Document doc;
        doc.Parse(json);

        cout << "json : " << json << endl << endl;

        if(true == doc.IsObject()) cout << "doc.isObject() : true" << endl;
        else                       cout << "doc.isObject() : false" << endl;

        if(true == doc.HasMember("hello")) cout << "doc.HasMember() : true" << endl;
        else                               cout << "doc.HasMember() : false" << endl;

        if(true == doc["hello"].IsString()){
            cout << "doc[hello].IsString() : true" << endl;
            cout << "doc[hello].GetString() : " << doc["hello"].GetString() << endl;
        }else                                cout << "doc[hello].IsString() : false" << endl;

        cout << "----------" << endl;

        if(true == doc["t"].IsBool()){
            cout << "doc[t].IsBool() : true" << endl;
            cout << "doc[t] = " << doc["t"].GetBool() << endl;
        }else
            cout << "doc[t].IsBool() : false" << endl;

        cout << "----------" << endl;

        if(true == doc["n"].IsNull())   cout << "doc[n].IsNull() : true" << endl;
        else                            cout << "doc[n].IsNull() : false" << endl;

        cout << "----------" << endl;

        if(true == doc["i"].IsNumber()){
            cout << "doc[i].IsNumber() : true" << endl;
            cout << "doc[i].GetInt() : " << doc["i"].GetInt() << endl;
        }else
            cout << "doc[i].IsNumber() : false" << endl;

        cout << "----------" << endl;

        if(true == doc["pi"].IsDouble()){
            cout << "doc[pi].IsDouble() : true" << endl;
            cout << "doc[pi].GetDouble() : " << doc["pi"].GetDouble() << endl;
        }else
            cout << "doc[pi].IsDouble() : false" << endl;

        cout << "----------" << endl;

        /*
         * rapidjson 的 Array 是与 vector 类似，可以使用索引，也可以使用迭代器
         * */
        const Value &a = doc["a"];
        if(true == doc["a"].IsArray()){
            cout << "doc[a].IsArray() : true" << endl;

            /* 
             * SizeType 在缺省情况下是 unsigned
             * */
            for(SizeType i=0; i<a.Size(); i++){
                printf("a[%d] = %d\n", i, a[i].GetInt());
            }

            for(auto &v : a.GetArray()){
                printf("a[] = %d\n", v.GetInt());
            }

            /*
             * using iterator
             * */
            for(auto itr = a.Begin();
                     itr!= a.End(); itr++){
                cout << "itr = " << itr->GetInt() << endl;
            }
        }else
            cout << "doc[a].IsArray() : false" << endl;

        cout << "----------" << endl;

        /*
         * 和 Array 相似，可以使用迭代器进行访问所有的 Object 成员
         * */
        const char *kTypeNames[] = {"Null", "False", "True", "Object", "Array", "String", "Number"};

        cout << "kTypeNames[] : "; for(auto str : kTypeNames) cout << str << " "; cout << endl;

        for(auto itr = doc.MemberBegin();
                 itr!= doc.MemberEnd(); itr++){
            cout << itr->name.GetString() << " - " << kTypeNames[itr->value.GetType()];
            cout << " - itr->value.GetType() : " << itr->value.GetType() << endl;
        }

        cout << "----------" << endl;

        /*
         * 1. 在不确定一个成员是否存在时，则需要在调用 operator[](const cahr *) 前先调用 HasMember()
         * 2. 在更优的情况下，是调用 FindMember() ，这样不需要进行两次查找
         * */
        auto itr = doc.FindMember("hello");
        if(itr != doc.MemberEnd()) cout << "itr->value.GetString() : " << itr->value.GetString() << endl;

    }

    return ret;
}

int  mJson::rapidjson_write(void)
{
    int ret = 0;

    /* 
     * 有多种方法去创建值，当一个 DOM 树被创建或修改后，可以使用 Writer 再次存储为 JSON
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * 当使用默认的构造函数创建一个 Value / Document，它的类型便会是 Null，要修改的时候，可以直接赋值，或使用
     *  Setxxx() 进行操作
     *
     *  Document doc;   // NULL
     *  doc.SetObject(); 
     *
     *  Value v; // NULL
     *  v.SetInt(10); / v = 10;
     *
     * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
     *
     * 几个类型都有重载构造函数 : 
     *  Value b(true);  // Value(bool)
     *  Value i(-123);  // Value(int)
     *  Value u(123u);  // Value(unsigned)
     *  Value d(1.2);   // Value(double)
     *
     * 要创建空的 Object/Array ,可以在默认构造函数后面直接使用 Value(Type) : 
     *  Value o(kObjectType);
     *  Value a(kArrayType);
     * */
    cout << "---------------------------" << endl;
    {
        cout << " write array ..." << endl;

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        const char *objs_head[][2] = {
            {"proto_version", "v0.1"    },
            {"status",        "1"       },
            {"ukey",          "uonneoiu"},
            {"session",       "JDOIJGOI"},
            {"method",        "0102"    },
            {"ts",            "2017-1-7"}
        };

        string gw     = "11233332";
        string name   = "hello--";
        string status = "online";
        string method = "0304";

#if 0
        string input;

        cin >> input;

        gw += input;
#endif

        const char *objs_body[][2] = {
            {"gateway",       gw.c_str()    },
            {"name",          name.c_str()  },
            {"status",        status.c_str()},
            {"method",        method.c_str()}
        };

        cout << "sizeof(objs_head) : " << sizeof(objs_head) << endl;
        cout << "sizeof(objs_head[0]) : " << sizeof(objs_head[0]) << endl;

        writer.StartObject();{
            /* head */
            writer.String("head");{
                writer.StartObject();{
                    for(size_t i=0; i<sizeof(objs_head)/sizeof(objs_head[0]); i++){
                        writer.String(objs_head[i][0]);
                        writer.String(objs_head[i][1]);
                    }
                } writer.EndObject();
            }
            /* body */
            writer.String("body");{
                writer.StartObject();{
                    writer.String("session"); writer.String("xxxxx");
                    writer.String("gateways");
                    writer.StartArray();{
                        for(int i=0; i<4; i++){
                            writer.StartObject();{
                                for(size_t j=0; j<sizeof(objs_body)/sizeof(objs_body[0]); j++){
                                    writer.String(objs_body[j][0]);
                                    writer.String(objs_body[j][1]);
                                }
                            } writer.EndObject();
                        }
                    } writer.EndArray();
                } writer.EndObject();
            }
        }writer.EndObject();

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        char buf[20] = {0, };

        sprintf(buf, "%d", 1);

        writer.StartObject();{
            writer.String("status");
            writer.String(buf);
            writer.String("status");
            writer.Int(1);
        }writer.EndObject();

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        /*                        tuple< 0    1     2   > > */
        typedef map<const char *, tuple<int, int, string> > devUnit_t;
        vector<devUnit_t> vdev_unit;
        /*                        tuple< 0    1     2         3      > > */
        typedef map<const char *, tuple<int, int, string, vector<devUnit_t> *> > BodyUnit_t;
        vector<BodyUnit_t> objs_body;

        unordered_map<int, vector<devUnit_t> > map_vdevunit;

        {
            for(int i=0; i<5; i++){
                devUnit_t dev_unit;

                dev_unit.insert(make_pair("id",       make_tuple(1, 1 + i, "")));
                dev_unit.insert(make_pair("gateway",  make_tuple(2, 0, "gateway ...")));
                dev_unit.insert(make_pair("type",     make_tuple(1, 105 + i, "")));
                dev_unit.insert(make_pair("zonetype", make_tuple(1, 444 + i, "")));
                dev_unit.insert(make_pair("clusterid",make_tuple(2, 0, "clusterid json ...")));

                vdev_unit.push_back(dev_unit);
            }

            map_vdevunit.insert(make_pair(1, vdev_unit));

            BodyUnit_t body_unit;

            body_unit.insert(make_pair("id",      make_tuple(1, 200, "", nullptr)));
            body_unit.insert(make_pair("name",    make_tuple(2, 0, "group1", nullptr)));
            body_unit.insert(make_pair("status",  make_tuple(1, 1, "", nullptr)));
            body_unit.insert(make_pair("devices", make_tuple(3, 0, "", &map_vdevunit[1])));

            objs_body.push_back(body_unit);
        }

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
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

        #if 0
        for(auto &u_map : objs_body){
            writer.String(u_map.first);
            switch(std::get<0>(u_map.second)){
                case 1: writer.Int(std::get<1>(u_map.second));              break;
                case 2: writer.String(std::get<2>(u_map.second).c_str());   break;
            }
        }
        #endif

        cout << "buffer.GetString() : " << buffer.GetString() << endl;

    }
    cout << "---------------------------" << endl;
    {
        /*                        tuple< 0    1     2   > > */
        typedef map<const char *, tuple<int, int, string> > devUnit_t;
        vector<devUnit_t> objs_body;

        {
            for(int i=0; i<5; i++){
                devUnit_t dev_unit;

                dev_unit.insert(make_pair("id",       make_tuple(1, 1 + i, "")));
                dev_unit.insert(make_pair("gateway",  make_tuple(2, 0, "gateway ...")));
                dev_unit.insert(make_pair("type",     make_tuple(1, 105 + i, "")));
                dev_unit.insert(make_pair("zonetype", make_tuple(1, 444 + i, "")));
                dev_unit.insert(make_pair("clusterid",make_tuple(2, 0, "clusterid json ...")));

                objs_body.push_back(dev_unit);
            }
        }

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
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

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        /*                        tuple< 0    1     2   > > */
        typedef map<const char *, tuple<int, int, string> > devUnit_t;
        vector<devUnit_t> objs_body;

        {
            for(int i=0; i<5; i++){
                devUnit_t dev_unit;

                dev_unit.insert(make_pair("id",       make_tuple(1, 1 + i, "")));
                dev_unit.insert(make_pair("gateway",  make_tuple(2, 0, "gateway ...")));

                objs_body.push_back(dev_unit);
            }
        }

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
            /* body */
            writer.String("body");{
            writer.StartObject();{
                writer.String("name");
                writer.String("bind-group - 01");
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

        cout << "buffer.GetString() : " << buffer.GetString() << endl;

        const char *json = buffer.GetString();
        cout << " ---------- parser ----------" << endl;
        {
            typedef map<string , list<tuple<int, string> > > BindDeviceSet_t;

            BindDeviceSet_t     binddev_set;

            Document doc;
            doc.Parse(json);

            cout << "json : " << json << endl;

            if(doc.HasMember("body") && doc["body"].IsObject()){ // if - 1
                string name;
                list<tuple<int, string> > binddev_list;

                Value &body = doc["body"];

                if(body.HasMember("name") && body["name"].IsString()){
                    name = body["name"].GetString();
                    cout << "name : " << name << endl;

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

                cout << "binddev_list.size() : " << binddev_list.size() << endl;

                binddev_set[name] = binddev_list;

                cout << "binddev_set.size() : " << binddev_set.size() << endl;
            } // end if - 1

            //-------------------------

            cout << "binddev_set.size() : " << binddev_set.size() << endl;

            string bind_name;
            for(auto itr = binddev_set.begin();
                     itr!= binddev_set.end(); itr++){
                bind_name = itr->first;
                cout << "itr->first : " << itr->first << endl;
                cout << "itr->second.size() : " << itr->second.size() << endl;

                for(auto &dev : itr->second){
                    cout << "gateway - id : " << std::get<0>(dev) << " - " << std::get<1>(dev) << endl;
                }
            }
            cout << endl;

            cout << "bind_name : " << bind_name << endl;

            const char *pn = "bind-group - 01";
            list<tuple<int, string> > &devices = binddev_set[pn];
            cout << "binddev_set[bind_name.c_str()].size() : " << devices.size() << endl;
            cout << "binddev_set[bind_name].size() : " << binddev_set[bind_name].size() << endl;
        }
    }
    cout << "---------------------------" << endl;
    {
        //"command":{"onoff":1}
        /*                        tuple< 0    1     2   > > */
        typedef map<const char *, tuple<int, int, string> > devUnit_t;
        devUnit_t objs_body;

        {
            for(int i=0; i<5; i++){
                devUnit_t dev_unit;

                dev_unit.insert(make_pair("id",       make_tuple(1, 1 + i, "")));
                dev_unit.insert(make_pair("gateway",  make_tuple(2, 0, "gateway ...")));

                objs_body = dev_unit;
            }
        }

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
            /* body */
            writer.String("body");{
            writer.StartObject();{
                writer.String("device");
                writer.StartObject();{
                    for(auto &u : objs_body){
                        writer.String(u.first);
                        switch(std::get<0>(u.second)){
                        case 1: writer.Int(std::get<1>(u.second));            break;
                        case 2: writer.String(std::get<2>(u.second).c_str()); break;
                        }
                    }
                } writer.EndObject();
            } writer.EndObject();
            }
        }writer.EndObject();

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        map<const char *, int> mi;

        mi.insert(make_pair("cmd", 1));
        mi.insert(make_pair("hello", 2));

        cout << "mi : " << endl;
        for(auto &u : mi){
            cout << "u : " << u.first << " - " << u.second << endl;
        }
        cout << endl;

        cout << "mi[cmd] : " << mi["cmd"] << endl;

        map<const char *, tuple<int, string> > mii;
        mii.insert(make_pair("cmd", make_tuple(1, "nice")));
        mii.insert(make_pair("hello", make_tuple(2, "go")));

        cout << "mii.size() : " << mii.size() << endl;
        for(auto &u : mii){
            cout << "u : " << u.first << " - " << std::get<0>(u.second) << " - " << std::get<1>(u.second) << endl;
        }
        cout << endl;

        cout << "get<0>(mii[cmd]) : " << std::get<0>(mii["cmd"]) << endl;
    }
    cout << "---------------------------" << endl;
    {
        //"command":{"onoff":1}
        /*                        tuple< 0    1     2   > > */
        typedef map<const char *, tuple<int, int, string> > devUnit_t;
        devUnit_t objs_body;

        {
            for(int i=0; i<5; i++){
                devUnit_t dev_unit;

                dev_unit.insert(make_pair("id",       make_tuple(1, 1 + i, "")));
                dev_unit.insert(make_pair("gateway",  make_tuple(2, 0, "gateway ...")));
                dev_unit.insert(make_pair("command",  make_tuple(2, 0, "on")));

                objs_body = dev_unit;
            }
        }

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
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

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;
    {
        string Info = "{\"Info\":{\"url\":\"aaaa.ipa\",\"platform\":\"ios\",\"onoff\":1}}";

        cout << "Info : " << Info << endl;

        Document doc;
        doc.Parse(Info.c_str());

        if(doc.HasMember("Info") & doc["Info"].IsObject()) cout << " HasMember(Info) : true " << endl;

        Value &info  = doc["Info"];
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        info.Accept(writer);
        string info_obj = buffer.GetString();

        cout << "info_obj : " << info_obj << endl;

        string info_s = "{\"url\":\"aaaa.ipa\",\"platform\":\"ios\",\"onoff\":1}";
        cout << "info_s : " << info_s << endl;

        cout << "Line : " << __LINE__ << endl;
    }
    cout << "---------------------------" << endl;
    {
        int gid    = 1;
        int status = 0;

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        writer.StartObject();{
            /* body */
            writer.String("body");{
            writer.StartObject();{
                writer.String("gid");
                writer.Int(gid);
                writer.String("status");
                writer.Int(status);
            } writer.EndObject();
            }
        }writer.EndObject();

        cout << "buffer.GetString() : " << buffer.GetString() << endl;
    }
    cout << "---------------------------" << endl;

    return ret;
}

/* 
 * 逆序执行的宏
 * */
#define reverse_exec(statement02, statement01) \
    do {                                       \
        statement01;                           \
        statement02;                           \
    }while(0);

int  mJson::rapidjson_advanced(void)
{
    int ret = 0;
    {
        #define     INT     1
        #define     STR     2
        #define     OBJ     3

        /* 
         * { int / string / obj }union
         * */
        typedef union{
            int         data_i;
            char       *data_c;
            const char *data_cc;
            void       *data_o;
        }iso_u;

        typedef struct{
            int     type;
            iso_u   data;
            //void   *pd;
        }Second_t;

        typedef map<string, tuple<int, iso_u> > devUnit_t;

        cout << "sizeof(iso_u) : " << sizeof(iso_u) << endl;

        iso_u iso = {10};
        cout << "iso.data_i : " << iso.data_i << endl;


        //Second_t s = {10, .data = {.data_i = 10}};

        map<int, iso_u> mii;

        iso = {.data_i = 10}; mii.insert(make_pair(1, iso));

        vector<devUnit_t> objs_body;
        {
            for(int i=0; i<5; i++){
                iso_u iso;
                devUnit_t dev_unit;

                #if 0
                iso.data_i  = 10 + i ;              dev_unit.insert(make_pair("id",       make_tuple(INT, iso)));
                iso.data_cc = "gateway ...";        dev_unit.insert(make_pair("gateway",  make_tuple(STR, iso)));
                iso.data_i  = 105 + i;              dev_unit.insert(make_pair("type",     make_tuple(INT, iso)));
                iso.data_i  = 444 + i;              dev_unit.insert(make_pair("zonetype", make_tuple(INT, iso)));
                iso.data_cc = "clusterid json ..."; dev_unit.insert(make_pair("clusterid",make_tuple(STR, iso)));
                #else
                /* 
                 * 使用逆序执行宏后，先执行 ios 赋值，再执行 dev_unit.insert()
                 * */
                reverse_exec(dev_unit.insert(make_pair("id",       make_tuple(INT, iso))), iso.data_i  = 10 + i);
                reverse_exec(dev_unit.insert(make_pair("gateway",  make_tuple(STR, iso))), iso.data_cc = "gateway ...");
                reverse_exec(dev_unit.insert(make_pair("type",     make_tuple(INT, iso))), iso.data_i  = 105 + i);
                reverse_exec(dev_unit.insert(make_pair("zonetype", make_tuple(INT, iso))), iso.data_i  = 444 + i);
                reverse_exec(dev_unit.insert(make_pair("clusterid",make_tuple(STR, iso))), iso.data_cc = "clusterid json ...");
                #endif

                objs_body.push_back(dev_unit);
            }
        }

        /*
         * printf objs_body
         * */
        for(auto &dev : objs_body){
            for(auto &u : dev){
                int    i_data = 0;
                string s_data;

                printf("%10s", u.first.c_str());

                switch(std::get<0>(u.second)){
                    case INT: 
                        i_data = std::get<1>(u.second).data_i;
                        cout << " | i_data = " << i_data << endl;
                        break;
                    case STR: 
                        s_data = std::get<1>(u.second).data_cc;
                        cout << " | s_data = " << s_data << endl;
                        break;
                }
            }
        }
    }
    cout << "---------------------------" << endl;
    {
        cout << "Test For macro reverse_exec()" << endl;
        reverse_exec(printf("2"), printf("1"));
        cout << endl;

        int a = 10;
        int b = 20;

        /*
         * 逆序执行后，b = 10; a = b + 10 = 20
         * */
        reverse_exec(a = b + 10, b = a);

        cout << "a = " << a << " b = " << b << endl;
    }
    cout << "---------------------------" << endl;

    return ret;
}

