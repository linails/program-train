/*
 * Progarm Name: cases.cpp
 * Created Time: 2016-12-15 22:15:06
 * Last modified: 2017-08-09 22:02:52
 * @author: minphone.linails linails@foxmail.com 
 */

#include "cases.hpp"
#include <iostream>
#include "test_main.h"
#include "dic-parser.hpp"
#include "exlibCases.hpp"
#include <cassert>
#include "key-bind-main.hpp"
#include "bit.hpp"
#include "tester-case001.hpp"
#include "ts-parser-main.hpp"
#include "case-other.hpp"
#include "code-formatter.hpp"

using std::cout;
using std::endl;

Cases::Cases()
{
}

Cases::~Cases()
{
}

int  Cases::cases_main(int argc, char **argv)
{
    int ret = 0;

    this->m_xml_cfg = Manager::get_instance()->get_xml_cfg();
    if(nullptr == this->m_xml_cfg){
        return -1;
    }

    /* 
     * exlib-cases
     * */
    {
        #if COMPILE_FLAG_exlibCases
        exlibCases exlibcases;

        ret = exlibcases.exlibcases_main(argc, argv); assert(-1 != ret);
        #endif
    }

    /* 
     * cases 001, 002 ,,,
     * */
    {
        #if COMPILE_FLAG_case001
        /*
         * case001 entry
         * */
        TesterCase001 infinite_loops;

        ret = infinite_loops.main(argc, argv); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case002
        /* 
         * case002
         * */
        DicParser *pdp = new DicParser();
        DicParser::get_instance(pdp);

        if(nullptr != pdp){
            ret = pdp->dicparser_main(argc, argv); assert(-1 != ret);
            delete pdp;
        }
        #endif
    }
    {
        #if COMPILE_FLAG_case003
        /* 
         * case003
         * */
        KeyBind kbind;

        ret = kbind.keybind_main(argc, argv); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case004
        /* 
         * case004
         * */
        Bit bit;

        ret = bit.bit_main(argc, argv); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case005
        /*
         * case005 : Ts Parser
         * */
        TsParserMain ts_parser;

        ret = ts_parser.main(); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case006
        ret = case_for_code_formatter(); assert(-1 != ret);
        #endif
    }
    {
        #if COMPILE_FLAG_case_other
        CaseOther co;
        ret = co.main(argc, argv); assert(-1 != ret);
        #endif
    }

    return ret;
}

int  Cases::case_for_code_formatter(void)
{
    cout << "case CodeFormatter" << endl;

    int ret = 0;
    string cfg;
    string dir_src;
    string dir_inc;

    this->m_xml_cfg->register_RootChild("code-formatter", "cfg");
    this->m_xml_cfg->getRoot_child(cfg, "code-formatter", "cfg");

    cout << "dir-src ret = " << this->m_xml_cfg->register_RootChild("code-formatter", "dir-src") << endl;
    cout << "dir-src ret = " << this->m_xml_cfg->getRoot_child(dir_src, "code-formatter", "dir-src") << endl;

    this->m_xml_cfg->register_RootChild("code-formatter", "dir-inc");
    this->m_xml_cfg->getRoot_child(dir_inc, "code-formatter", "dir-inc");

    if(true == cfg.empty()){
        ret = -1;
        cout << "code-formatter cfg is null !" << endl;
    }
    cout << "cfg : " << cfg << endl;
    cout << "dir-src : " << dir_src << endl;
    cout << "dir-inc : " << dir_inc << endl;

    CodeFormatter cf(cfg, dir_src);

    cout << "-----------------------------------------" << endl;
    return ret;
}

