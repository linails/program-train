/*
 * Progarm Name: ts-parser-main.cpp
 * Created Time: 2017-06-21 15:22:22
 * Last modified: 2017-06-22 13:33:31
 * @author: minphone.linails linails@foxmail.com 
 */

#include "ts-parser-main.hpp"
#include <iostream>
#include "cfg-loader.hpp"
#include "manager.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ts-parser.hpp"

using std::cout;
using std::endl;

TsParserMain::TsParserMain()
{
}

TsParserMain::~TsParserMain()
{
}

int  TsParserMain::main(void)
{
    cout << "TsParserMain::main ..." << endl;

    /* 
     * init for load cfg etc.
     * */
    this->init();

    this->parser();

    cout << "-----------------------------------" << endl;

    return 0;
}

int  TsParserMain::init(void)
{
    int ret = 0;

    this->m_mgr = Manager::get_instance();
    if(nullptr != this->m_mgr){

        this->m_xml_cfg = this->m_mgr->get_xml_cfg();
        if(nullptr != this->m_xml_cfg){
            cout << "xml_cfg load successed !" << endl;

            this->m_xml_cfg->register_RootChild("master", "ts-path");
            this->m_xml_cfg->getRoot_child(this->m_ts_path, "master", "ts-path");

            /* 
             * update this->m_ts_path
             * eg. ~/xxx => /home/minphone/xxx
             * */
            {
                string home = getenv("HOME");

                int pos = -1;
                if((int)string::npos != (pos = this->m_ts_path.find("~"))){
                    string tail(this->m_ts_path, pos + strlen("~"), string::npos);
                    this->m_ts_path= home + tail;
                }
            }

            cout << "ts_path = " << this->m_ts_path << endl;

        }else{
            ret = -1;
        }
    }else{
        ret = -1;
    }

    return ret;
}

int  TsParserMain::parser(void)
{
    TsParser parser(this->m_ts_path);

    return 0;
}

