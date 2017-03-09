/*
 * Progarm Name: xml-parser.hpp
 * Created Time: 2017-03-08 14:23:03
 * Last modified: 2017-03-09 17:43:56
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _XML_PARSER_HPP_
#define _XML_PARSER_HPP_

#include <string>
#include <vector>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include <thread>
#include <sys/stat.h>
#include <time.h>

using std::string;
using std::vector;
using std::thread;

typedef struct {
    string mqtt_server;
    string mqtt_port;
    string ssl_key_path;
    string plugin_msg_path;
    string mqtt_topic;
}xmlMaster_t;

typedef struct {
    string appkey;
    string master_secret;
    string access_id;
    string access_key;
    string secret_key;
}xmlAppClient_t;

typedef struct {
    string log_path;
    string log_level;
    string postgresql_connection;
    string redis_addr;
    string redis_password;
    string jpush_addr;
    xmlAppClient_t  android; // jpush_config
    xmlAppClient_t  ios;     // jpush_config
    string msg_addr;
    string msg_account;
    string msg_password;
    string msg_content;
    string avatar_upload;
    string avatar_download;
    string phonehead_3;
    string phonehead_4;
}xmlPlugin_t;

class xmlParser{
public:
    xmlParser(string path = "");
    ~xmlParser();
    int  test(void);
    int  getMaster_server_port(string &ip, int &port);
    int  getMaster_ssl_key_path(string &path);
    int  getMaster_plugin_path(string &path);
    int  getMaster_topic(string &topic);
    int  getPlugin_log_path(string &path);
    int  getPlugin_log_level(int &level);
    int  getPlugin_postgresql_connection(string &conn);
    int  getPlugin_redis_addr(string &ip, int &port);
    int  getPlugin_redis_password(string &pwd);
    int  getPlugin_jpush_addr(string &addr);
    int  getPlugin_msg_addr(string &addr);
    int  getPlugin_msg_account(string &account);
    int  getPlugin_msg_password(string &pwd);
    int  getPlugin_msg_contents(vector<string> &contents);
    int  getPlugin_avatar_upload(string &addr);
    int  getPlugin_avatar_download(string &addr);
    int  getPlugin_phonehead_3(string &head);
    int  getPlugin_phonehead_4(string &head);
    int  getPlugin_android_appkey(string &appkey);
    int  getPlugin_android_master_secret(string &master_secret);
    int  getPlugin_android_access_id(string &access_id);
    int  getPlugin_android_access_key(string &access_key);
    int  getPlugin_android_secret_key(string &secret_key);
    int  getPlugin_ios_appkey(string &appkey);
    int  getPlugin_ios_master_secret(string &master_secret);
    int  getPlugin_ios_access_id(string &access_id);
    int  getPlugin_ios_access_key(string &access_key);
    int  getPlugin_ios_secret_key(string &secret_key);
public:
private:
    int  tinyxml_reader(void);
    void config_file_check(void);
private:
    string           m_file       = "/etc/server-config.xml";
    thread          *m_check_loop = nullptr;
    time_t           m_st_mtime   = 0;
    xmlMaster_t      m_xml_master;
    xmlPlugin_t      m_xml_plugin;
};

#endif //_XML_PARSER_HPP_

