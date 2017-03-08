/*
 * Progarm Name: xml-parser.cpp
 * Created Time: 2017-03-08 14:22:59
 * Last modified: 2017-03-08 18:06:14
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

using std::cout;
using std::endl;

xmlParser::xmlParser()
{
    this->m_check_loop = new thread(&xmlParser::config_file_check, this);
    if(nullptr == this->m_check_loop){
        cout << "[Error] new failed in xmlParser !" << endl;
    }
}

xmlParser::~xmlParser()
{
}

int  xmlParser::main(int argc, char **argv)
{
    int ret = 0;

    cout << "xml-parser main" << endl;

    if(1 != argc){
        cout << "argv[1] : " << argv[1] << endl;
        this->m_file = argv[1];
    }

    cout << "this->m_file : " << this->m_file << endl;

    ret = this->tinyxml_reader(); assert(-1 != ret);

    while(1);
    return ret;
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
                        dst = cnode->GetText();
                    } else {
                        TiXmlHandle h_cnode(cnode);
                        TiXmlElement *ccnode = h_cnode.FirstChild(root_or_child.c_str()).Element();
                        if( NULL != ccnode ){ dst = ccnode->GetText(); }
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
            element(this->m_xml_master.plugin_msg_keepalive,master, "plugin_msg_keepalive", "root");
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

            element(this->m_xml_plugin.log_path,        plugin, "log_path",      "root");
            element(this->m_xml_plugin.log_level,       plugin, "log_level",     "root");
            element(this->m_xml_plugin.redis_addr,      plugin, "redis_addr",    "root");
            element(this->m_xml_plugin.redis_password,  plugin, "redis_password","root");
            element(this->m_xml_plugin.jpush_addr,      plugin, "jpush_addr",    "root");
            element(this->m_xml_plugin.msg_addr,        plugin, "msg_addr",      "root");
            element(this->m_xml_plugin.msg_account,     plugin, "msg_account",   "root");
            element(this->m_xml_plugin.msg_password,    plugin, "msg_password",  "root");
            element(this->m_xml_plugin.msg_content,     plugin, "msg_content",   "root");
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
        cout << "plugin_msg_keepalive = " << this->m_xml_master.plugin_msg_keepalive << endl;
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
        std::this_thread::sleep_for(std::chrono::seconds(3));
        cout << "sleep ... " << endl;

        stat(this->m_file.c_str(), &file_stat);

        if(this->m_st_mtime != file_stat.st_mtime){
            cout << "sec : " << file_stat.st_mtime << endl;

            this->tinyxml_reader();

            this->m_st_mtime = file_stat.st_mtime;
        }
    }
}

