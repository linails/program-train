/*
 * Progarm Name: xml-parser.cpp
 * Created Time: 2017-03-08 14:22:59
 * Last modified: 2017-03-27 17:14:20
 * @author: minphone.linails linails@foxmail.com 
 */

#include "xml-parser.hpp"
#include <iostream>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <typeinfo>
#include <chrono>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using std::cout;
using std::endl;

using namespace rapidjson;

xmlParser::xmlParser(string path)
{
    if(false == path.empty()){
        this->m_file = path;
    }

    this->m_check_loop = new thread(&xmlParser::config_file_check, this);
    if(nullptr == this->m_check_loop){
        cout << "[Error] new failed in xmlParser !" << endl;
    }
}

xmlParser::~xmlParser()
{
    cout << "~xmlParser() ... " << endl;

    this->m_check_loop->join();
    delete this->m_check_loop;
    this->m_check_loop = nullptr;
}

int  xmlParser::tinyxml_reader(void)
{
    int ret = 0;

    /* 
     * load xml file
     * */
    TiXmlDocument doc(this->m_file.c_str());
    if(!doc.LoadFile()){
        cout << "xml file load failed !" << endl;
        ret = -1;
    }else{
        cout << "xml file load successed !" << endl;
    }

    /* hdoc 是 doc 指向的对象 */
    TiXmlHandle hDoc(&doc);

    /* 指向元素的指针 */
    TiXmlElement *pElem = hDoc.FirstChildElement().Element(); // 指向根节点

    TiXmlHandle hRoot(pElem);

    /* 
     * read elements
     * */
    {

        auto element = [](
                        string &dst,
                        TiXmlElement *node,
                        string element_name,
                        string root_or_child){
            if( NULL != node ){
                TiXmlHandle h_root(node);

                TiXmlElement *cnode = h_root.FirstChild(element_name.c_str()).Element();
                if( NULL != cnode ){
                    if("root" == root_or_child){
                        const char *p_txt = cnode->GetText();
                        if(NULL != p_txt) dst = p_txt;
                    } else {
                        TiXmlHandle h_cnode(cnode);
                        TiXmlElement *ccnode = h_cnode.FirstChild(root_or_child.c_str()).Element();
                        if( NULL != ccnode ){
                            const char *p_txt = ccnode->GetText();
                            if(NULL != p_txt) dst = p_txt;
                        }
                    }
                }
                return 0;
            }else
                return -1;
        };

        /* 
         * read master Element 
         * */
        {
            TiXmlElement *master = hRoot.FirstChild("master").Element();
            if(NULL != master){
                cout << "find Element <master>" << endl;
            }else{
                cout << "[Error] no element <master>" << endl;
            }

            element(this->m_xml_master.mqtt_server,         master, "mqtt_server",          "root");
            element(this->m_xml_master.mqtt_port,           master, "mqtt_port",            "root");
            element(this->m_xml_master.ssl_key_path,        master, "ssl_key_path",         "root");
            element(this->m_xml_master.plugin_msg_path,     master, "plugin_msg_path",      "root");
            element(this->m_xml_master.mqtt_topic,          master, "mqtt_topic",           "root");

        }


        /* 
         * read plugin Element 
         * */
        {
            TiXmlElement *plugin = hRoot.FirstChild("msg_plugin").Element();
            if(NULL != plugin){
                cout << "find Element <plugin>" << endl;
            }else{
                cout << "[Error] no element <plugin>" << endl;
            }

            element(this->m_xml_plugin.log_path,        plugin, "log_path",       "root");
            element(this->m_xml_plugin.log_level,       plugin, "log_level",      "root");
            element(this->m_xml_plugin.redis_addr,      plugin, "redis_addr",     "root");
            element(this->m_xml_plugin.redis_password,  plugin, "redis_password", "root");
            element(this->m_xml_plugin.jpush_addr,      plugin, "jpush_addr",     "root");
            element(this->m_xml_plugin.msg_addr,        plugin, "msg_addr",       "root");
            element(this->m_xml_plugin.msg_account,     plugin, "msg_account",    "root");
            element(this->m_xml_plugin.msg_password,    plugin, "msg_password",   "root");
            element(this->m_xml_plugin.msg_content,     plugin, "msg_content",    "root");
            element(this->m_xml_plugin.avatar_upload,   plugin, "avatar_upload","root");
            element(this->m_xml_plugin.avatar_download, plugin, "avatar_download","root");
            element(this->m_xml_plugin.phonehead_3,     plugin, "phonenum_3heads","root");
            element(this->m_xml_plugin.phonehead_4,     plugin, "phonenum_4heads","root");
            element(this->m_xml_plugin.postgresql_connection, plugin, "postgresql_connection", "root");

            TiXmlElement *client = hRoot.FirstChild("msg_plugin").FirstChild("jpush_config").Element();
            if(NULL != client){
                cout << "find Element <jpush_config>" << endl;
            }else{
                cout << "[Error] no element <jpush_config>" << endl;
            }
            element(this->m_xml_plugin.android.appkey,          client, "android",      "appkey");
            element(this->m_xml_plugin.android.master_secret,   client, "android",      "master_secret");
            element(this->m_xml_plugin.android.access_id,       client, "android",      "access_id");
            element(this->m_xml_plugin.android.access_key,      client, "android",      "access_key");
            element(this->m_xml_plugin.android.secret_key,      client, "android",      "secret_key");
            element(this->m_xml_plugin.ios.appkey,              client, "ios",          "appkey");
            element(this->m_xml_plugin.ios.master_secret,       client, "ios",          "master_secret");
            element(this->m_xml_plugin.ios.access_id,           client, "ios",          "access_id");
            element(this->m_xml_plugin.ios.access_key,          client, "ios",          "access_key");
            element(this->m_xml_plugin.ios.secret_key,          client, "ios",          "secret_key");
        }
    }

    /*
     * print info
     * */
    {
        cout << "mqtt_server = " << this->m_xml_master.mqtt_server << endl;
        cout << "mqtt_port = " << this->m_xml_master.mqtt_port << endl;
        cout << "ssl_key_path = " << this->m_xml_master.ssl_key_path << endl;
        cout << "plugin_msg_path = " << this->m_xml_master.plugin_msg_path << endl;
        cout << "mqtt_topic = " << this->m_xml_master.mqtt_topic << endl;
    }
    {
        cout << "log_path = " << this->m_xml_plugin.log_path << endl;
        cout << "log_level = " << this->m_xml_plugin.log_level << endl;
        cout << "postgresql_connection = " << this->m_xml_plugin.postgresql_connection << endl;
        cout << "redis_addr = " << this->m_xml_plugin.redis_addr << endl;
        cout << "redis_password = " << this->m_xml_plugin.redis_password << endl;
        cout << "jpush_addr = " << this->m_xml_plugin.jpush_addr << endl;
        cout << "msg_addr = " << this->m_xml_plugin.msg_addr << endl;
        cout << "msg_account = " << this->m_xml_plugin.msg_account << endl;
        cout << "msg_password = " << this->m_xml_plugin.msg_password << endl;
        cout << "msg_content = " << this->m_xml_plugin.msg_content << endl;
        cout << "avatar_upload = " << this->m_xml_plugin.avatar_upload<< endl;
        cout << "avatar_download = " << this->m_xml_plugin.avatar_download<< endl;
        cout << "phonehead_3 = " << this->m_xml_plugin.phonehead_3 << endl;
        cout << "phonehead_4 = " << this->m_xml_plugin.phonehead_4 << endl;

        cout << "appkey = " << this->m_xml_plugin.android.appkey << endl;
        cout << "master_secret = " << this->m_xml_plugin.android.master_secret << endl;
        cout << "access_id = " << this->m_xml_plugin.android.access_id << endl;
        cout << "access_key = " << this->m_xml_plugin.android.access_key << endl;
        cout << "secret_key = " << this->m_xml_plugin.android.secret_key << endl;

        cout << "appkey = " << this->m_xml_plugin.ios.appkey << endl;
        cout << "master_secret = " << this->m_xml_plugin.ios.master_secret << endl;
        cout << "access_id = " << this->m_xml_plugin.ios.access_id << endl;
        cout << "access_key = " << this->m_xml_plugin.ios.access_key << endl;
        cout << "secret_key = " << this->m_xml_plugin.ios.secret_key << endl;
    }

    return ret;
}

void xmlParser::config_file_check(void)
{
    struct stat file_stat;

    while(1){

        stat(this->m_file.c_str(), &file_stat);

        if(this->m_st_mtime != file_stat.st_mtime){
            cout << "Time : " << file_stat.st_mtime << endl;

            this->tinyxml_reader();

            this->m_st_mtime = file_stat.st_mtime;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
        cout << "[xmlParser check config-file stat thread] sleep ... " << endl;
    }
}

int  xmlParser::test(void)
{
    cout << endl;
    cout << "---------------------------" << endl;
    cout << endl;
    {
        string  ip;
        int     port = 0;
        this->getMaster_server_port(ip, port);
        printf("getMaster_server_port( %s : %d )\n", ip.c_str(), port);
    }
    {
        string path;
        this->getMaster_ssl_key_path(path);
        printf("getMaster_ssl_key_path( %s )\n", path.c_str());
    }
    {
        string path;
        this->getMaster_plugin_path(path);
        printf("getMaster_plugin_path( %s )\n", path.c_str());
    }
    {
        string topic;
        this->getMaster_topic(topic);
        printf("getMaster_topic( %s )\n", topic.c_str());
    }
    {
        string path;
        this->getPlugin_log_path(path);
        printf("getPlugin_log_path( %s )\n", path.c_str());
    }
    {
        int level = 0;
        this->getPlugin_log_level(level);
        printf("getPlugin_log_level( %d )\n", level);
    }
    {
        string conn;
        this->getPlugin_postgresql_connection(conn);
        printf("getPlugin_postgresql_connection( %s )\n", conn.c_str());
    }
    {
        string  ip;
        int     port = 0;
        this->getPlugin_redis_addr(ip, port);
        printf("getPlugin_redis_addr( %s : %d )\n", ip.c_str(), port);
    }
    {
        string pwd;
        this->getPlugin_redis_password(pwd);
        printf("getPlugin_redis_password( %s )\n", pwd.c_str());
    }
    {
        string addr;
        this->getPlugin_jpush_addr(addr);
        printf("getPlugin_jpush_addr( %s )\n", addr.c_str());
    }
    {
        string addr;
        this->getPlugin_msg_addr(addr);
        printf("getPlugin_msg_addr( %s )\n", addr.c_str());
    }
    {
        string account;
        this->getPlugin_msg_account(account);
        printf("getPlugin_msg_account( %s )\n", account.c_str());
    }
    {
        string pwd;
        this->getPlugin_msg_password(pwd);
        printf("getPlugin_msg_password( %s )\n", pwd.c_str());
    }
    {
        vector<string> contents;
        this->getPlugin_msg_contents(contents);
        for(auto u : contents){
            printf("getPlugin_msg_contents( %s )\n", u.c_str());
        }
    }
    {
        string addr;
        this->getPlugin_avatar_upload(addr);
        printf("getPlugin_avatar_upload( %s )\n", addr.c_str());
    }
    {
        string addr;
        this->getPlugin_avatar_download(addr);
        printf("getPlugin_avatar_download( %s )\n", addr.c_str());
    }
    {
        string head;
        this->getPlugin_phonehead_3(head);
        printf("getPlugin_phonehead_3( %s )\n", head.c_str());
    }
    {
        string head;
        this->getPlugin_phonehead_4(head);
        printf("getPlugin_phonehead_4( %s )\n", head.c_str());
    }
    {
        string appkey;
        this->getPlugin_android_appkey(appkey);
        printf("getPlugin_android_appkey( %s )\n", appkey.c_str());
    }
    {
        string master_secret;
        this->getPlugin_android_master_secret(master_secret);
        printf("getPlugin_android_master_secret( %s )\n", master_secret.c_str());
    }
    {
        string access_id;
        this->getPlugin_android_access_id(access_id);
        printf("getPlugin_android_access_id( %s )\n", access_id.c_str());
    }
    {
        string access_key;
        this->getPlugin_android_access_key(access_key);
        printf("getPlugin_android_access_key( %s )\n", access_key.c_str());
    }
    {
        string secret_key;
        this->getPlugin_android_secret_key(secret_key);
        printf("getPlugin_android_secret_key( %s )\n", secret_key.c_str());
    }
    {
        string appkey;
        this->getPlugin_ios_appkey(appkey);
        printf("getPlugin_ios_appkey( %s )\n", appkey.c_str());
    }
    {
        string master_secret;
        this->getPlugin_ios_master_secret(master_secret);
        printf("getPlugin_ios_master_secret( %s )\n", master_secret.c_str());
    }
    {
        string access_id;
        this->getPlugin_ios_access_id(access_id);
        printf("getPlugin_ios_access_id( %s )\n", access_id.c_str());
    }
    {
        string access_key;
        this->getPlugin_ios_access_key(access_key);
        printf("getPlugin_ios_access_key( %s )\n", access_key.c_str());
    }
    {
        string secret_key;
        this->getPlugin_ios_secret_key(secret_key);
        printf("getPlugin_ios_secret_key( %s )\n", secret_key.c_str());
    }

    cout << endl;
    cout << "---------------------------" << endl;
    cout << endl;
    return 0;
}

int  xmlParser::getMaster_server_port(string &ip, int &port)
{
    ip   = this->m_xml_master.mqtt_server;
    if(false == this->m_xml_master.mqtt_port.empty())
        port = atoi(this->m_xml_master.mqtt_port.c_str());
    else
        port = 0;
    return 0;
}

int  xmlParser::getPlugin_log_level(int &level)
{
    if(false == this->m_xml_plugin.log_level.empty())
        level = atoi(this->m_xml_plugin.log_level.c_str());
    else
        level = 0;
    return 0;
}

int  xmlParser::getPlugin_postgresql_connection(string &conn)
{
    conn = this->m_xml_plugin.postgresql_connection;
    return 0;
}

int  xmlParser::getPlugin_redis_addr(string &ip, int &port)
{
    int pos = 0;
    if((int)string::npos != (pos = this->m_xml_plugin.redis_addr.find(":"))){
        string head(this->m_xml_plugin.redis_addr, 0, pos);
        string tail(this->m_xml_plugin.redis_addr, pos+1, string::npos);

        ip   = head;
        if(false == tail.empty()){
            port = atoi(tail.c_str());
        }
    }else{
        ip   = "";
        port = 0;
    }
    return 0;
}

int  xmlParser::getPlugin_msg_contents(vector<string> &contents)
{
    Document doc;
    doc.Parse(this->m_xml_plugin.msg_content.c_str());

    if(doc.HasMember("contents") && doc["contents"].IsArray()){ // if - 1
        Value &jcontents = doc["contents"];
        for(auto &jcontent : jcontents.GetArray()){
            if(jcontent.HasMember("content") && jcontent["content"].IsString()){
                contents.push_back(jcontent["content"].GetString());
            }
        }
    } // end if - 1

    return 0;
}

int  xmlParser::getPlugin_android_appkey(string &appkey)
{
    appkey = this->m_xml_plugin.android.appkey;
    return 0;
}

int  xmlParser::getPlugin_android_master_secret(string &master_secret)
{
    master_secret = this->m_xml_plugin.android.master_secret;
    return 0;
}

int  xmlParser::getPlugin_android_access_id(string &access_id)
{
    access_id = this->m_xml_plugin.android.access_id;
    return 0;
}

int  xmlParser::getPlugin_android_access_key(string &access_key)
{
    access_key = this->m_xml_plugin.android.access_key;
    return 0;
}

int  xmlParser::getPlugin_android_secret_key(string &secret_key)
{
    secret_key = this->m_xml_plugin.android.secret_key;
    return 0;
}

int  xmlParser::getPlugin_ios_appkey(string &appkey)
{
    appkey = this->m_xml_plugin.ios.appkey;
    return 0;
}

int  xmlParser::getPlugin_ios_master_secret(string &master_secret)
{
    master_secret = this->m_xml_plugin.ios.master_secret;
    return 0;
}

int  xmlParser::getPlugin_ios_access_id(string &access_id)
{
    access_id = this->m_xml_plugin.ios.access_id;
    return 0;
}

int  xmlParser::getPlugin_ios_access_key(string &access_key)
{
    access_key = this->m_xml_plugin.ios.access_key;
    return 0;
}

int  xmlParser::getPlugin_ios_secret_key(string &secret_key)
{
    secret_key = this->m_xml_plugin.ios.secret_key;
    return 0;
}

int  xmlParser::getMaster_ssl_key_path(string &path)  { path = this->m_xml_master.ssl_key_path; return 0; }
int  xmlParser::getMaster_plugin_path(string &path)   { path = this->m_xml_master.plugin_msg_path; return 0; }
int  xmlParser::getMaster_topic(string &topic)        { topic = this->m_xml_master.mqtt_topic; return 0; }
int  xmlParser::getPlugin_log_path(string &path)      { path = this->m_xml_plugin.log_path; return 0; }
int  xmlParser::getPlugin_redis_password(string &pwd) { pwd = this->m_xml_plugin.redis_password; return 0; }
int  xmlParser::getPlugin_jpush_addr(string &addr)    { addr = this->m_xml_plugin.jpush_addr; return 0; }
int  xmlParser::getPlugin_msg_addr(string &addr)      { addr = this->m_xml_plugin.msg_addr; return 0; }
int  xmlParser::getPlugin_msg_account(string &account){ account = this->m_xml_plugin.msg_account; return 0; }
int  xmlParser::getPlugin_msg_password(string &pwd)   { pwd = this->m_xml_plugin.msg_password; return 0; }
int  xmlParser::getPlugin_avatar_upload(string &addr) { addr = this->m_xml_plugin.avatar_upload; return 0; }
int  xmlParser::getPlugin_avatar_download(string &addr){addr = this->m_xml_plugin.avatar_download; return 0; }
int  xmlParser::getPlugin_phonehead_3(string &head)   { head = this->m_xml_plugin.phonehead_3; return 0; }
int  xmlParser::getPlugin_phonehead_4(string &head)   { head = this->m_xml_plugin.phonehead_4; return 0; }


