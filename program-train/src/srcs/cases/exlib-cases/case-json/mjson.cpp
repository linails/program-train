/*
 * Progarm Name: mjson.cpp
 * Created Time: 2016-12-22 09:00:56
 * Last modified: 2017-01-14 17:51:22
 * @author: minphone.linails linails@foxmail.com 
 */

#include "mjson.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>

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
    }

    return ret;
}

