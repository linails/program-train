/*
 * Progarm Name: xml-parser.hpp
 * Created Time: 2017-03-08 14:23:03
 * Last modified: 2017-03-08 15:53:15
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _XML_PARSER_HPP_
#define _XML_PARSER_HPP_

#include <string>
#include <vector>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

using std::string;
using std::vector;

typedef struct {
    string mqtt_server;
    string mqtt_port;
    string ssl_key_path;
    string plugin_msg_path;
    string plugin_msg_keepalive;
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
}xmlPlugin_t;

class xmlParser{
public:
    xmlParser();
    ~xmlParser();
    int  main(int argc, char **argv);
private:
    int  tinyxml_reader(void);
private:
    string      m_file;
    xmlMaster_t m_xml_master;
    xmlPlugin_t m_xml_plugin;
};

#endif //_XML_PARSER_HPP_

