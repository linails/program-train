/*
 * Progarm Name: manager.hpp
 * Created Time: 2017-03-15 14:55:40
 * Last modified: 2017-06-10 08:47:22
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

#include "primer.hpp"
#include "db-caller.hpp"
#include "cases.hpp"
#include "malgorithm.hpp"
#include <cassert>
#include "container.hpp"
#include "mlinux.hpp"
#include "advanced.hpp"
#include <string>
#include <vector>
#include "cfg-loader.hpp"

using std::string;
using std::vector;

#define COMPILE_FLAG_Primer         0
#define COMPILE_FLAG_Advanced       0
#define COMPILE_FLAG_Container      0
#define COMPILE_FLAG_dbCaller       0
#define COMPILE_FLAG_mLinux         0
#define COMPILE_FLAG_Cases          0
#define COMPILE_FLAG_mAlgorithm     1
#define COMPILE_FLAG_gTest          0

class Manager{
public:
    Manager(string path = "");
    ~Manager();
    int  main(int argc, char **argv);
public:
    static Manager *get_instance(Manager *ptr = nullptr);
    CfgLoader      *get_xml_cfg(void);
private:
    static Manager *instance;
    string      m_cfg_path;
    CfgLoader  *m_xml_cfg   = nullptr;
    #if COMPILE_FLAG_Primer
    Primer     *m_primer    = nullptr;
    #endif
    #if COMPILE_FLAG_Advanced
    Advanced   *m_advanced  = nullptr;
    #endif
    #if COMPILE_FLAG_Container
    Container  *m_container = nullptr;
    #endif
    #if COMPILE_FLAG_dbCaller
    dbCaller   *m_dbcaller  = nullptr;
    #endif
    #if COMPILE_FLAG_mLinux
    mLinux     *m_mlinux    = nullptr;
    #endif
    #if COMPILE_FLAG_Cases
    Cases      *m_cases     = nullptr;
    #endif
    #if COMPILE_FLAG_mAlgorithm
    mAlgorithm *m_malgo     = nullptr;
    #endif
};

#endif //_MANAGER_HPP_

