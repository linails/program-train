/*
 * Progarm Name: manager.cpp
 * Created Time: 2017-03-15 14:55:36
 * Last modified: 2017-03-16 09:19:43
 * @author: minphone.linails linails@foxmail.com 
 */

#include "manager.hpp"
#include <iostream>

using std::cout;
using std::endl;

Manager *Manager::instance = nullptr;

Manager *Manager::get_instance(Manager *ptr)
{
    if(nullptr != ptr) instance = ptr; return instance;
}

Manager::Manager(string path)
{
    if(false == path.empty()){

        this->m_cfg_path = path;

        this->m_xml_cfg = new CfgLoader(path);
        if(nullptr == this->m_xml_cfg){
            cout << "[Error] new CfgLoader failed !" << endl;
        }
    }else{
        this->m_xml_cfg = new CfgLoader();
        if(nullptr == this->m_xml_cfg){
            cout << "[Error] new CfgLoader failed !" << endl;
        }
    }
}

Manager::~Manager()
{
    if(nullptr != this->m_xml_cfg){
        this->m_xml_cfg->kill_thread();

        delete this->m_xml_cfg;
        this->m_xml_cfg = nullptr;
    }

    #if COMPILE_FLAG_Primer
    if(nullptr != this->m_primer){
        delete this->m_primer;
        this->m_primer = nullptr;
    }
    #endif

    #if COMPILE_FLAG_Advanced
    if(nullptr != this->m_advanced){
        delete this->m_advanced;
        this->m_advanced = nullptr;
    }
    #endif

    #if COMPILE_FLAG_Container
    if(nullptr != this->m_container){
        delete this->m_container;
        this->m_container = nullptr;
    }
    #endif

    #if COMPILE_FLAG_dbCaller
    if(nullptr != this->m_dbcaller){
        delete this->m_dbcaller;
        this->m_dbcaller = nullptr;
    }
    #endif

    #if COMPILE_FLAG_mLinux
    if(nullptr != this->m_mlinux){
        delete this->m_mlinux;
        this->m_mlinux = nullptr;
    }
    #endif

    #if COMPILE_FLAG_Cases
    if(nullptr != this->m_cases){
        delete this->m_cases;
        this->m_cases = nullptr;
    }
    #endif

    #if COMPILE_FLAG_mAlgorithm
    if(nullptr != this->m_malgo){
        delete this->m_malgo;
        this->m_malgo = nullptr;
    }
    #endif
}

int  Manager::main(int argc, char **argv)
{
    int ret = 0;

    {
        #if COMPILE_FLAG_Primer
        this->m_primer = new Primer();
        if(nullptr != this->m_primer){
            ret = this->m_primer->primer_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new Primer() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_Advanced
        this->m_advanced = new Advanced();
        if(nullptr != this->m_advanced){
            ret = this->m_advanced->advanced_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new Advanced() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_Container
        this->m_container = new Container();
        if(nullptr != this->m_container){
            ret = this->m_container->container_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new Container() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_dbCaller
        this->m_dbcaller = new dbCaller();
        if(nullptr != this->m_dbcaller){
            ret = this->m_dbcaller->dbcaller_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new dbCaller() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_mLinux
        this->m_mlinux = new mLinux();
        if(nullptr != this->m_mlinux){
            ret = this->m_mlinux->mlinux_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new mLinux() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_Cases
        this->m_cases = new Cases();
        if(nullptr != this->m_cases){
            ret = this->m_cases->cases_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new Cases() failed !" << endl;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_mAlgorithm
        this->m_malgo = new mAlgorithm();
        if(nullptr != this->m_malgo){
            ret = this->m_malgo->malgo_main(argc, argv); assert(-1 != ret);
        }else{
            cout << "[Error] new mAlgorithm() failed !" << endl;
        }
        #endif
    }

    return ret;
}

CfgLoader *Manager::get_xml_cfg(void){ return this->m_xml_cfg; }

