/*
 * Progarm Name: mjson.cpp
 * Created Time: 2016-12-22 09:00:56
 * Last modified: 2016-12-22 14:33:03
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mjson.hpp"
#include <iostream>
#include <cstdio>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using std::cout;
using std::endl;
using std::string;

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

    return ret;
}

int  mJson::json_cppjson(void)
{
    int ret = 0;

    return ret;
}

